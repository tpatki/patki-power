#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include "msr_core.h"
#include "msr_rapl.h"
#include "msr_opt.h"
#include "blr_util.h"

static int rank;
static char hostname[1025];
extern int msr_debug;
//static FILE* f;
struct rapl_state *s;

static int msr_rank_mod=1;
char *env;
uint64_t msr_pkg_power_limit=-1, msr_pp0_power_limit=-1, msr_dram_power_limit=-1;

{{fn foo MPI_Init}}
	{{callfn}}
	rank = -1;
	FILE *f;
	PMPI_Comm_rank( MPI_COMM_WORLD, &rank );
	get_env_int("MSR_RANK_MOD", &msr_rank_mod);
	
	/*PATKI: Borrowed from msr_opt.c, for debugging purposes only*/

        // First, check the environment variables.
        env = getenv("MSR_PKG_POWER_LIMIT");
        if(env){
                msr_pkg_power_limit = strtoll( env, NULL, 0 );
        }

        env = getenv("MSR_PP0_POWER_LIMIT");
        if(env){
                msr_pp0_power_limit = strtoll( env, NULL, 0 );
        }

        env = getenv("MSR_DRAM_POWER_LIMIT");
        if(env){
                msr_dram_power_limit = strtoll( env, NULL, 0 );
        }

	printf("MSR_RANK_MOD is %d\n", msr_rank_mod);
	printf("MSR_PKG_POWER_LIMIT is %llu\n", msr_pkg_power_limit);
	printf("MSR_PP0_POWER_LIMIT is %llu\n", msr_pp0_power_limit);
	printf("MSR_DRAM_POWER_LIMIT is %llu\n", msr_dram_power_limit);

/*	if(rank%msr_rank_mod == 0){
		gethostname( hostname, 1024 );
		f = safe_mkstemp(hostname, "rapl", rank);
		init_msr();
		disable_turbo(0);
		disable_turbo(1);
		//s=rapl_init( *{{0}}, *{{1}}, NULL );
		s=rapl_init( *{{0}}, *{{1}}, f);
	}
*/

{{endfn}}

{{fn foo MPI_Finalize}}
/*	double elapsed;
	if(rank%msr_rank_mod == 0){
		rapl_finalize(s);
	}
*/
	{{callfn}}
{{endfn}}
