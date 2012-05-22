c NPROCS = 2048 CLASS = D
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  

c number of nodes for which this version is compiled
        integer nnodes_compiled
        parameter (nnodes_compiled = 2048)

c full problem size
        integer isiz01, isiz02, isiz03
        parameter (isiz01=408, isiz02=408, isiz03=408)

c sub-domain array size
        integer isiz1, isiz2, isiz3
        parameter (isiz1=7, isiz2=13, isiz3=isiz03)

c number of iterations and how often to print the norm
        integer itmax_default, inorm_default
        parameter (itmax_default=400, inorm_default=400)
        double precision dt_default
        parameter (dt_default = 1.0d0)
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='21 May 2012')
        character*3 npbversion
        parameter (npbversion='3.3')
        character*6 cs1
        parameter (cs1='mpif77')
        character*9 cs2
        parameter (cs2='$(MPIF77)')
        character*46 cs3
        parameter (cs3='-Xlinker -rpath=$(HOME)/local/src/power/rap...')
        character*6 cs4
        parameter (cs4='(none)')
        character*9 cs5
        parameter (cs5='-O3 -fPIC')
        character*30 cs6
        parameter (cs6='-O3 -fPIC  -Wl,--build-id=none')
        character*6 cs7
        parameter (cs7='randi8')
