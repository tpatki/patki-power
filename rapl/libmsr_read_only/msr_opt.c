#include <unistd.h>	//getopt
#include <getopt.h>
#include <stdlib.h>	//strtoll
#include <stdint.h>
#include "msr_rapl.h"
#include "msr_core.h"
#include "msr_opt.h"

static char *
msr2str( uint64_t msr ){
	switch(msr){
		case MSR_PKG_POWER_LIMIT:	return "MSR_PKG_POWER_LIMIT";	break;	
		case MSR_PP0_POWER_LIMIT:	return "MSR_PP0_POWER_LIMIT";	break;
#ifdef ARCH_062D
		case MSR_DRAM_POWER_LIMIT:	return "MSR_DRAM_POWER_LIMIT";	break;
#endif
		default:			return "WTF?";			break;
	}
}

void
parse_opts( int argc, char **argv ){
	int cpu;
	uint64_t msr_pkg_power_limit=-1, msr_pp0_power_limit=-1; 
#ifdef ARCH_062D
	uint64_t msr_dram_power_limit=-1;
#endif
	char *env;

	// TODO:  write a command-line interface.
	argc=argc;
	argv=argv;

	// First, check the environment variables.
	env = getenv("MSR_PKG_POWER_LIMIT");
	if(env){
		msr_pkg_power_limit = strtoll( env, NULL, 0 );
	}

	env = getenv("MSR_PP0_POWER_LIMIT");
	if(env){
		msr_pp0_power_limit = strtoll( env, NULL, 0 );
	}
#ifdef ARCH_062D
	env = getenv("MSR_DRAM_POWER_LIMIT");
	if(env){
		msr_dram_power_limit = strtoll( env, NULL, 0 );
	}
#endif

	// Now write the MSRs.  Zero is a valid value
	for( cpu=0; cpu<NUM_PACKAGES; cpu++ ){
		if( msr_pkg_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_PKG_POWER_LIMIT), msr_pkg_power_limit, cpu);
			write_msr( cpu, MSR_PKG_POWER_LIMIT, msr_pkg_power_limit );
		}
		if( msr_pp0_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_PP0_POWER_LIMIT), msr_pp0_power_limit, cpu);
			write_msr( cpu, MSR_PP0_POWER_LIMIT, msr_pp0_power_limit );
		}
#ifdef ARCH_062D
		if( msr_dram_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_DRAM_POWER_LIMIT), msr_dram_power_limit, cpu);
			write_msr( cpu, MSR_DRAM_POWER_LIMIT, msr_dram_power_limit );
		}
#endif
	}
}


