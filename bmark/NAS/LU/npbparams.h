c NPROCS = 128 CLASS = C
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  

c number of nodes for which this version is compiled
        integer nnodes_compiled
        parameter (nnodes_compiled = 128)

c full problem size
        integer isiz01, isiz02, isiz03
        parameter (isiz01=162, isiz02=162, isiz03=162)

c sub-domain array size
        integer isiz1, isiz2, isiz3
        parameter (isiz1=11, isiz2=21, isiz3=isiz03)

c number of iterations and how often to print the norm
        integer itmax_default, inorm_default
        parameter (itmax_default=300, inorm_default=300)
        double precision dt_default
        parameter (dt_default = 2.0d0)
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='09 Apr 2012')
        character*3 npbversion
        parameter (npbversion='3.3')
        character*6 cs1
        parameter (cs1='mpif77')
        character*9 cs2
        parameter (cs2='$(MPIF77)')
        character*46 cs3
        parameter (cs3='-Xlinker -rpath=/home/tpatki/tapasya/patki-...')
        character*6 cs4
        parameter (cs4='(none)')
        character*9 cs5
        parameter (cs5='-O3 -fPIC')
        character*10 cs6
        parameter (cs6='-O3 -fPIC ')
        character*6 cs7
        parameter (cs7='randi8')
