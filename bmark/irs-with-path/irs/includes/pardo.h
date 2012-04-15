#ifdef OPENMP

#ifdef OMP2COMPILER     /* Directives for OpenMP2 compilers */

#pragma omp parallel for if (ifthreads == 1) schedule (static)

#endif                  /* end OMP2COMPILER */ 

#endif                  /* end OPENMP */


/*------------------------------------------------------------------------
- END
-------------------------------------------------------------------------*/
