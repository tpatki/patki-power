c NPROCS = 4 CLASS = A
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        integer maxcells, problem_size, niter_default
        parameter (maxcells=2, problem_size=64, niter_default=200)
        double precision dt_default
        parameter (dt_default = 0.0008d0)
        integer wr_default
        parameter (wr_default = 5)
        integer iotype
        parameter (iotype = 0)
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='10 Apr 2012')
        character*3 npbversion
        parameter (npbversion='3.3')
        character*44 cs1
        parameter (cs1='/home/tpatki/tapasya/test-mvapich/bin/mpif77')
        character*9 cs2
        parameter (cs2='$(MPIF77)')
        character*46 cs3
        parameter (cs3='-Xlinker -rpath=/home/tpatki/tapasya/patki-...')
        character*43 cs4
        parameter (cs4='-I/home/tpatki/tapasya/test-mvapich/include')
        character*4 cs5
        parameter (cs5='-O3 ')
        character*3 cs6
        parameter (cs6='-O3')
        character*6 cs7
        parameter (cs7='randi8')
