

      subroutine rdinput( NRuns )
C----------------------------------------------------------------------
C  The input deck is read by MPI task=0 as a derived datatype.  It
C  is then sent to all other MPI tasks.  This replaces the original 
C  routine, which redirected stdin to every task, for portability
C  reasons.  BMB 4/12/2001
C----------------------------------------------------------------------
      include 'params.inc'
      include 'geomz.inc'
      include 'globals.inc'
      include 'mpif.h'

      character*24 dt
      character*127 mach
      INTEGER MPIid, ierr, InputFileType, basetypes(2), offsets(2),
     +        blockcounts(2), extent, numMPItasks,
     +        stat(MPI_STATUS_SIZE),
     +        Nruns, matb1, mate1, matb2, mate2, i, filler20

C.....Define the structure InputFile and declare a variable of that
C.....type. These will be used to create an MPI derived data type
C.....so that the input file can be sent to each task from task=0.
C.....Note that the i20 variable exists only for data alignment and
C.....is not used elsewhere.
      TYPE InputFile
      SEQUENCE
      INTEGER i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,
     +        i14,i15,i16,i17,i18,i19,i20 
      DOUBLE PRECISION d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,
     +        d12,d13,d14
      END TYPE InputFile

      TYPE (InputFile) Infile

      INTEGER nout

      parameter (nout=10)


C.....Now create the MPI derived data type to hold the input file
      CALL MPI_TYPE_EXTENT(MPI_INTEGER, extent, ierr)
      offsets(1) = 0
      basetypes(1) = MPI_INTEGER
      blockcounts(1) = 20
      offsets(2) = 20 * extent
      basetypes(2) = MPI_DOUBLE_PRECISION
      blockcounts(2) = 14
      CALL MPI_TYPE_STRUCT(2, blockcounts, offsets, basetypes,
     +  InputFileType, ierr)
      CALL MPI_TYPE_COMMIT(InputFileType, ierr)
    
      CALL MPI_COMM_RANK( MPI_COMM_WORLD, MPIid, ierr )
      CALL MPI_COMM_SIZE( MPI_COMM_WORLD, numMPItasks, ierr )


C*******************************************************************
C  BEGINNING OF MPI TASK=0 WORK
C*******************************************************************
      IF (MPIid .EQ. 0) THEN
      OPEN (4, FILE="input.dat")

        open(nout,FILE='out_setup.txt',STATUS='UNKNOWN',
     |            ACCESS='SEQUENTIAL',FORM='FORMATTED')


        read(4,*) Nruns

        read  (4,100) title
 100    format(20a4)
        write (nout,200) title
 200    format(////1x,20a4)
        write(nout,13)
 13     format(/1x,'     SPHOT')

        read  (4,626) ilib, illib
 626    format(2i10)
        write (nout,627) ilib, illib
 627    format(/
     |     /'ilib ', 8x,i2,3x,'library (0=binary, 1=formatted)',
     |     /        18x,      'for ixopec=2, put ilib=1'
     |     /'illib', 8x,i2,3x,'0=use old bin.lib,1=form new bin.lib')

        read  (4,101) npart, igroup, ixopec, isorst, irr, ithom, icross
 101    format(7i10)
        write (nout,201) npart, igroup, ixopec, isorst,
     |  irr, ithom, icross
 201    format(
     |  /'npart ',i9,3x,'# of particles (different if plankian used)'
     |  /'igroup',i9,3x,'energy bins (0=12, 1-12=1, 13=ross.mean)'
     |  /'ixopec',i9,3x,'opacity (0=library, 1=input,2=data)'
     |  /'isorst',i9,3x,'source (1=uniform in sphere, 2=plankian)'
     |  /'irr   ',i9,3x,'r-roulette/split (0=none, 1=impt, 2=size)'
     |  /'ithom ',i9,3x,'thomson scattering (0=not used, 1=used)'
     |  /'icross',i9,3x,'print cross sections (0= no, 1= yes)')

        read  (4,102) naxl, nradl, nreg
 102    format(3i10)
        write (nout,202) naxl, nradl, nreg
 202    format('naxl ',i10,3x,'number of axial meshes'
     |  /'nradl',i10,3x,'number of radial meshes'
     |  /'nreg ',i10,3x,'number of material regions')

        read  (4,103) dtol, wcut, tcen, xmult
 103    format(4e10.2)
        write (nout,203) dtol, wcut, tcen, xmult
 203    format(
     |  /'dtol =',2x,e10.3,3x,'tolerance to cell boundaries (cm)'
     |  /'wcut =',2x,e10.3,3x,'low weight cutoff'
     |  /'tcen =',2x,e10.3,3x,'time to census (sec)'
     |  /'xmult=',2x,e10.3,3x,'weight mult. for russian roulette')

        read  (4,103) axl, radl, opec, bwgt
        write (nout,204) axl, radl, opec, bwgt
 204    format(
     |  /'axl  =',2x,e10.3,3x,'portion of sphere analyzed (degrees)'
     |  /'radl =',2x,e10.3,3x,'sphere radius (cm)'
     |  /'opec =',2x,e10.3,3x,'input opacity (1/cm)'
     |  /'bwgt =',2x,e10.3,3x,'bundle weight (kev)')

C.......For the purposes of the ASCI Purple Benchmark, it is mandatory
C.......that nreg = 2.  This is hardcoded into the derived datatype
C.......and replaces the code below which permits an arbitrary number
C.......of regions.
C       do 151 i = 1,nreg
C         read (4,104) matb, mate
C104      format(2i10)
C         do 151 j = matb,mate
C            ng_mid(j) = i
C151      continue

         nreg = 2
         read (4,104) matb1, mate1
         read (4,104) matb2, mate2
 104     format(2i10)
         do 151 j = matb1, mate1
           ng_mid(j) = 1
 151     continue
         do 152 j = matb2, mate2
           ng_mid(j) = 2
 152     continue

         read (4,105) (mtl(i), atrat(i), dns(i), tmp(i), i=1,nreg)
 105     format(i10,3e10.3)
         write (nout,205)
 205     format(//' region',5x,'material',5x,'atomic ratio',5x,
     |   'density(g/cc)',5x,'temperature(ev)'/)
         write (nout,206) (i,mtl(i), atrat(i), dns(i),
     |   tmp(i), i=1,nreg)
 206     format(i5,10x,i1,9x,e10.3,8x,e10.3,10x,e10.3)

         read  (4,400) print_flag
 400     format(i10)
         write (nout,401) print_flag
 401     format(//'print_flag    ',i10)



C........Be sure to close unit as it will be used in rdopac routine
         CLOSE (4)

C........Transfer data to derived data type variable
         Infile = InputFile (Nruns, ilib, illib, npart, igroup,
     +            ixopec, isorst, irr, ithom, icross, naxl,
     +            nradl, nreg, matb1, mate1, matb2, mate2,
     +            mtl(1), mtl(2), filler20,
     +            dtol, wcut, tcen, xmult, axl, radl, opec, bwgt,
     +            atrat(1), atrat(2), dns(1), dns(2), tmp(1),
     +            tmp(2) )

C........Send input file to all other MPI tasks
         DO 300 i=1, numMPItasks-1
           CALL MPI_SEND(Infile, 1, InputFileType, i, 222,
     +        MPI_COMM_WORLD, ierr)
 300     CONTINUE

         close(nout)

C.....MPI task=0 only work is done
      ENDIF

c
c     broadcast the print flag to others 
c
      call MPI_BCAST(print_flag,1,MPI_INTEGER,0,MPI_COMM_WORLD, ierr)

C*******************************************************************
C  BEGINNING OF WORK FOR ALL OTHER TASKS
C*******************************************************************
      IF (MPIid .GT. 0) THEN

C.......Receive input file and read into program global variables
        CALL MPI_RECV(Infile, 1, InputFileType, 0, 222, 
     +      MPI_COMM_WORLD, stat, ierr)

        Nruns = Infile%i1
        ilib = Infile%i2
        illib = Infile%i3
        npart = Infile%i4
        igroup = Infile%i5
        ixopec = Infile%i6
        isorst = Infile%i7
        irr = Infile%i8
        ithom = Infile%i9
        icross = Infile%i10
        naxl = Infile%i11
        nradl = Infile%i12
        nreg = Infile%i13
        matb1 = Infile%i14
        mate1 = Infile%i15
        matb2 = Infile%i16
        mate2 = Infile%i17
        mtl(1) = Infile%i18
        mtl(2) = Infile%i19

        dtol = Infile%d1
        wcut = Infile%d2
        tcen = Infile%d3
        xmult = Infile%d4
        axl = Infile%d5
        radl = Infile%d6
        opec = Infile%d7
        bwgt = Infile%d8
        atrat(1) = Infile%d9
        atrat(2) = Infile%d10
        dns(1)  = Infile%d11
        dns(2) = Infile%d12
        tmp(1) = Infile%d13
        tmp(2) = Infile%d14

        nreg = 2
        do 351 j = matb1, mate1
          ng_mid(j) = 1
 351    continue
        do 352 j = matb2, mate2
          ng_mid(j) = 2
 352    continue


C.....End of work for all other MPI tasks
      ENDIF


C.....ALL TASKS DO THIS
C.....Read in LLNL library opacities.  The original IF condition
C.....has been commented out for the purposes of the ASCI Purple
C.....benchmark which MUST use the opacity library.
C     if (ixopec .eq. 0) then
C        CALL rdopac (ilib,illib)
C     endif

      ixopec = 0
      CALL rdopac (ilib, illib)


      return
      end
