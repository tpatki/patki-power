
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _EXTERN_C_
#ifdef __cplusplus
#define _EXTERN_C_ extern "C"
#else /* __cplusplus */
#define _EXTERN_C_
#endif /* __cplusplus */
#endif /* _EXTERN_C_ */

#ifdef MPICH_HAS_C2F
_EXTERN_C_ void *MPIR_ToPointer(int);
#endif // MPICH_HAS_C2F

#ifdef PIC
/* For shared libraries, declare these weak and figure out which one was linked
   based on which init wrapper was called.  See mpi_init wrappers.  */
#pragma weak pmpi_init
#pragma weak PMPI_INIT
#pragma weak pmpi_init_
#pragma weak pmpi_init__
#endif /* PIC */

_EXTERN_C_ void pmpi_init(MPI_Fint *ierr);
_EXTERN_C_ void PMPI_INIT(MPI_Fint *ierr);
_EXTERN_C_ void pmpi_init_(MPI_Fint *ierr);
_EXTERN_C_ void pmpi_init__(MPI_Fint *ierr);

static int in_wrapper = 0;
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include "msr_core.h"
#include "msr_rapl.h"
#include "msr_opt.h"
#include "blr_util.h"
#include "cpuid.h"

static int rank;
static char hostname[1025];
extern int msr_debug;
static FILE* f;
struct rapl_state_s s;

static int msr_rank_mod=1;

static int fortran_init = 0;
/* ================== C Wrappers for MPI_Init ================== */
_EXTERN_C_ int PMPI_Init(int *argc, char ***argv);
_EXTERN_C_ int MPI_Init(int *argc, char ***argv) { 
    int _wrap_py_return_val = 0;
    if (in_wrapper) return PMPI_Init(argc, argv);
    in_wrapper = 1;

     parse_proc_cpuinfo();
	    if (fortran_init) {
#ifdef PIC
        if (!PMPI_INIT && !pmpi_init && !pmpi_init_ && !pmpi_init__) {
            fprintf(stderr, "ERROR: Couldn't find fortran pmpi_init function.  Link against static library instead.\n");
            exit(1);
        }        switch (fortran_init) {
        case 1: PMPI_INIT(&_wrap_py_return_val);   break;
        case 2: pmpi_init(&_wrap_py_return_val);   break;
        case 3: pmpi_init_(&_wrap_py_return_val);  break;
        case 4: pmpi_init__(&_wrap_py_return_val); break;
        default:
            fprintf(stderr, "NO SUITABLE FORTRAN MPI_INIT BINDING\n");
            break;
        }
#else /* !PIC */
        pmpi_init_(&_wrap_py_return_val);
#endif /* !PIC */
    } else {
        _wrap_py_return_val = PMPI_Init(argc, argv);
    }

	rank = -1;
	PMPI_Comm_rank( MPI_COMM_WORLD, &rank );
	get_env_int("MSR_RANK_MOD", &msr_rank_mod, 1);
	if(rank%msr_rank_mod == 0){
		gethostname( hostname, 1024 );
		f = safe_mkstemp(hostname, "rapl", rank);
		init_msr();
		int socket;
		for(socket = 0; socket < config.sockets; socket++)
		  disable_turbo(socket);
		rapl_init(&s, f ,1);
	}
    in_wrapper = 0;
    return _wrap_py_return_val;
}

/* =============== Fortran Wrappers for MPI_Init =============== */
static void MPI_Init_fortran_wrapper(MPI_Fint *ierr) { 
    int argc = 0;
    char ** argv = NULL;
    int _wrap_py_return_val = 0;
    _wrap_py_return_val = MPI_Init(&argc, &argv);
    *ierr = _wrap_py_return_val;
}

_EXTERN_C_ void MPI_INIT(MPI_Fint *ierr) { 
    fortran_init = 1;
    MPI_Init_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_init(MPI_Fint *ierr) { 
    fortran_init = 2;
    MPI_Init_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_init_(MPI_Fint *ierr) { 
    fortran_init = 3;
    MPI_Init_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_init__(MPI_Fint *ierr) { 
    fortran_init = 4;
    MPI_Init_fortran_wrapper(ierr);
}

/* ================= End Wrappers for MPI_Init ================= */




/* ================== C Wrappers for MPI_Finalize ================== */
_EXTERN_C_ int PMPI_Finalize();
_EXTERN_C_ int MPI_Finalize() { 
    int _wrap_py_return_val = 0;
    if (in_wrapper) return PMPI_Finalize();
    in_wrapper = 1;

	double elapsed;
	if(rank%msr_rank_mod == 0){
		rapl_finalize(&s, 1);
	}
	_wrap_py_return_val = PMPI_Finalize();
    in_wrapper = 0;
    return _wrap_py_return_val;
}

/* =============== Fortran Wrappers for MPI_Finalize =============== */
static void MPI_Finalize_fortran_wrapper(MPI_Fint *ierr) { 
    int _wrap_py_return_val = 0;
    _wrap_py_return_val = MPI_Finalize();
    *ierr = _wrap_py_return_val;
}

_EXTERN_C_ void MPI_FINALIZE(MPI_Fint *ierr) { 
    MPI_Finalize_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_finalize(MPI_Fint *ierr) { 
    MPI_Finalize_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_finalize_(MPI_Fint *ierr) { 
    MPI_Finalize_fortran_wrapper(ierr);
}

_EXTERN_C_ void mpi_finalize__(MPI_Fint *ierr) { 
    MPI_Finalize_fortran_wrapper(ierr);
}

/* ================= End Wrappers for MPI_Finalize ================= */



