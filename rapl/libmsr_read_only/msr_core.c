/* msr_core.c
 *
 * Low-level msr interface.
 */

// Necessary for pread & pwrite.
#define _XOPEN_SOURCE 500

#include <stdio.h>	//   perror
#include <unistd.h>	//   pread, pwrite
//#include <sys/types.h>  // \ ....
#include <sys/stat.h> 	// | open
#include <fcntl.h>	// / ....
#include <stdint.h>	// uint64_t
#include <errno.h>
#include "msr_core.h"
#include "msr_common.h"

int msr_debug;
static int core_fd[NUM_PACKAGES][NUM_CORES_PER_PACKAGE];

void
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
				snprintf(filename, 1024, "%s::%d  Error opening /dev/cpu/%d/msr\n", __FILE__, __LINE__, i*NUM_CORES_PER_PACKAGE+j);
				perror(filename);
			}

		}
		
	}
	initialized = 1;
}

void 
finalize_msr(){
	int i, j, rc;
	char filename[1025];
	for( i=0; i<NUM_PACKAGES; i++){
		for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
			if(core_fd[i][j]){
				rc = close(core_fd[i][j]);
				if( rc != 0 ){
					snprintf(filename, 1024, "%s::%d  Error closing file /dev/cpu/%d/msr\n", 
							__FILE__, __LINE__, i*NUM_CORES_PER_PACKAGE+j);
					perror(filename);
				}
			}else{
				core_fd[i][j] = 0;
			}
		}
	}
}

void
write_msr(int cpu, off_t msr, uint64_t val){
	write_msr_single_core( cpu, 0, msr, val );
}

void
write_msr_all_cores(int cpu, off_t msr, uint64_t val){
	int j;
	for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
		write_msr_single_core( cpu, j, msr, val );
	}
}

void
write_msr_all_cores_v(int cpu, off_t msr, uint64_t *val){
	int j;
	for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
		write_msr_single_core( cpu, j, msr, val[j] );
	}
}

void
write_msr_single_core(int cpu, int core, off_t msr, uint64_t val){
	int rc, core_fd_idx;
	char error_msg[1025];
	core_fd_idx = cpu*NUM_CORES_PER_PACKAGE+core;
	rc = pwrite( core_fd[cpu][core], &val, (size_t)sizeof(uint64_t), msr );
	if( rc != sizeof(uint64_t) ){
		snprintf( error_msg, 1024, "%s::%d  pwrite returned %d.  core_fd[%d][%d]=%d, cpu=%d, core=%d cpu+core=%d msr=%ld (0x%lx).  errno=%d\n", 
				__FILE__, __LINE__, rc, cpu, core, core_fd[cpu][core], cpu, core, core_fd_idx, msr, msr, errno );
		perror(error_msg);
	}
}

void
read_msr(int cpu, off_t msr, uint64_t *val){
	read_msr_single_core(cpu, 0, msr, val);
}

void
read_msr_all_cores_v(int cpu, off_t msr, uint64_t *val){
	int j;
	for(j=0; j<NUM_CORES_PER_PACKAGE; j++){
		read_msr_single_core(cpu, 0, msr, &val[j]);
	}
}

void 
read_msr_single_core(int cpu, int core, off_t msr, uint64_t *val){
	int rc, core_fd_idx;
	char error_msg[1025];
	core_fd_idx = cpu*NUM_CORES_PER_PACKAGE+core;
	rc = pread( core_fd[cpu][core], (void*)val, (size_t)sizeof(uint64_t), msr );
	if( rc != sizeof(uint64_t) ){
		snprintf( error_msg, 1024, "%s::%d  pread returned %d.  core_fd[%d][%d]=%d, cpu=%d, core=%d cpu+core=%d msr=%ld (0x%lx).  errno=%d\n", 
				__FILE__, __LINE__, rc, cpu, core, core_fd[cpu][core], cpu, core, core_fd_idx, msr, msr, errno );
		perror(error_msg);
	}
}
