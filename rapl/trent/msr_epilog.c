/* Run this in the SLURM epilog in order to reset MSRs to known good values.
 *
 * At the moment, this enables turbo and sets the package power limit to the
 * default value provided by Appro.
 *
 * Assumes 2 packages per node and 8 cores per package.
 *
 * Note that changing turbo state requires read-modify-write sequence.
 */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>  // off_t
#include <unistd.h>

#define NUM_PACKAGES 2
#define NUM_CORES_PER_PACKAGE 8

#define IA32_PERF_CTL		0x199 // setting bit 32 high DISABLES turbo mode.
#define MSR_PKG_POWER_LIMIT	0x610 // Section 14.7.3 "Package RAPL Domain"
#define MSR_PP0_POWER_LIMIT	0x638 // Section 14.7.4 "PP0/PP1 RAPL Domains"
#define MSR_DRAM_POWER_LIMIT	0x618  

#define APPRO_DEFAULT_PKG_POWER_LIMIT 0x6845000148398

static int core_fd[NUM_PACKAGES][NUM_CORES_PER_PACKAGE];

static void
init_msr(){
        int i,j;
        char filename[1025];
        static int initialized = 0;
        if( initialized ){
                return;
        }
        for (i=0; i<NUM_PACKAGES; i++){
                for (j=0; j<NUM_CORES_PER_PACKAGE; j++){
                        // Open the rest of the cores for core-level msrs.  
                        snprintf(filename, 1024, "/dev/cpu/%d/msr", i*NUM_CORES_PER_PACKAGE+j);
                        core_fd[i][j] = open( filename, O_RDWR );
	                       if(core_fd[i][j] == -1){
                               snprintf(	filename, 
					       	1024, 
					       	"%s::%d  Error opening /dev/cpu/%d/msr\n", __FILE__, __LINE__, 
					       	i*NUM_CORES_PER_PACKAGE+j);
                               perror(filename);
                        }

                }

        }
        initialized = 1;
}

static void
finalize_msr(){
        int i, j, rc;
        char filename[1025];
        for( i=0; i<NUM_PACKAGES; i++){
                for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
                        if(core_fd[i][j]){
                                rc = close(core_fd[i][j]);
                                if( rc != 0 ){
                                    snprintf(	filename, 
						1024, 
						"%s::%d  Error closing file /dev/cpu/%d/msr\n",__FILE__, __LINE__, 
						i*NUM_CORES_PER_PACKAGE+j);
                                        perror(filename);
                                }
                        }else{
                                core_fd[i][j] = 0;
                        }
                }
        }
}

static void
write_msr_single_core(int cpu, int core, off_t msr, uint64_t val){
        int rc, core_fd_idx;
        char error_msg[1025];
        core_fd_idx = cpu*NUM_CORES_PER_PACKAGE+core;
        rc = pwrite(core_fd[cpu][core], &val, (size_t)sizeof(uint64_t), msr );
        if( rc != sizeof(uint64_t) ){
                snprintf( 	error_msg, 
				1024, 
				"%s::%d  pwrite returned %d.  core_fd[%d][%d]=%d, cpu=%d, core=%d cpu+core=%d msr=%ld (0x%lx).  errno=%d\n",
                                __FILE__, __LINE__, rc, cpu, core, core_fd[cpu][core], cpu, core, core_fd_idx, msr, msr, errno );
                perror(error_msg);
        }
}

static void
write_msr_all_cores_v(int cpu, off_t msr, uint64_t *val){        int j;
        for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
                write_msr_single_core( cpu, j, msr, val[j] );
        }
}



static void
write_msr(int cpu, off_t msr, uint64_t val){
        write_msr_single_core( cpu, 0, msr, val );
}


static void
read_msr_single_core(int cpu, int core, off_t msr, uint64_t *val){        
	int rc, core_fd_idx;
	char error_msg[1025];        
	core_fd_idx = cpu*NUM_CORES_PER_PACKAGE+core;
	rc = pread( core_fd[cpu][core], (void*)val, (size_t)sizeof(uint64_t),msr );
   	if( rc != sizeof(uint64_t) ){
                snprintf( 	error_msg, 
				1024, 
				"%s::%d  pread returned %d. core_fd[%d][%d]=%d, cpu=%d, core=%d cpu+core=%d msr=%ld (0x%lx).  errno=%d\n", 
				__FILE__, __LINE__, rc, cpu, core,core_fd[cpu][core], cpu, core, core_fd_idx, msr, msr, errno );

                perror(error_msg);
        }
}

static void
read_msr_all_cores_v(int cpu, off_t msr, uint64_t *val){
        int j;
        for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
                read_msr_single_core(cpu, 0, msr, &val[j]);
        }
}


static void
enable_turbo(int package){
        int j;
        uint64_t val[NUM_CORES_PER_PACKAGE];

        // Set bit 32 "IDA/Turbo DISENGAGE" of IA32_PERF_CTL to 0.
        read_msr_all_cores_v( package, IA32_PERF_CTL, &val[0] );
        for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
                val[j] &= ((uint64_t)-1) ^ ((uint64_t)1) << 32;
        }
        write_msr_all_cores_v( package, IA32_PERF_CTL, &val[0] );

}

/* At the moment, the default is to leave turbo enabled.  Use this
 * instead if the default changes.  --blr.
static void
disable_turbo(int package){
        int j;
        uint64_t val[NUM_CORES_PER_PACKAGE];

        // Set bit 32 "IDA/Turbo DISENGAGE" of IA32_PERF_CTL to 1.
        read_msr_all_cores_v( package, IA32_PERF_CTL, &val[0] );
        for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
                val[j] |= ((uint64_t)1) << 32;
        }

        write_msr_all_cores_v( package, IA32_PERF_CTL, &val[0] );

}
*/


int 
main()
{
	int package;
	init_msr();
        for(package=0; package<NUM_PACKAGES; package++){
             write_msr( package, MSR_PKG_POWER_LIMIT, APPRO_DEFAULT_PKG_POWER_LIMIT );
             enable_turbo(package);
        }
	finalize_msr();
	return 0;
}
