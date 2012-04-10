c NPROCS = 2048 CLASS = D
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        character class
        parameter (class ='D')
        integer m, npm
        parameter (m=34, npm=2048)
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
