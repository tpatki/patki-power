# ------------------------------------------------------------------------- 
#  Copyright 2006.  The Regents of the University of California. 
#  All rights reserved. 
# ------------------------------------------------------------------------- 
#  This work was produced at the University of California, Lawrence 
#  Livermore National Laboratory (UC LLNL) under contract no. 
#  W-7405-ENG-48 (Contract 48) between the U.S. Department of Energy 
#  (DOE) and the Regents of the University of California (University) 
#  for the operation of UC LLNL.  The rights of the Federal Government are 
#  reserved under Contract 48 subject to the restrictions agreed upon by 
#  the DOE and University as allowed under DOE Acquisition Letter 97-1. 
# ------------------------------------------------------------------------- 
def largestDivisor( number ,exponent):
    from math import ceil,pow
    
    largest = 1
    n=1
    theMax = ceil( pow(number,exponent) ) 
    
    while n <= theMax:
        if number % n == 0:
            largest = n
        n=n+1
    return largest


def writeGridFile( nx, ny, nz, Px, Py, Pz, nProcs):
    import mpi

    if nProcs == 0:
        nProcs = mpi.procs
    
    # case when Px Py and Pz are not specified, we compute reasonable, consistent values
    if Px == 0:
        # compute the block sizes Px, Py, Pz
        Px = largestDivisor(nProcs,  1.0/3.0)
        Py = largestDivisor(nProcs/Px, 1.0/2.0)
        Pz = nProcs/(Px*Py)
        if nProcs != Px*Py*Pz :
            print "FACTORIZATION FAILURE for ",nProcs,"  Px=",Px,"  Py=",Py,"  Pz=",Pz
    
    fileName = 'grid_%i_%ix%ix%i.cmg' % ( nProcs, nx, ny, nz)
    
    if mpi.rank == 0:
        fileWriter( fileName, nx, ny, nz, Px, Py, Pz)
    
    mpi.barrier()

    return fileName


def fileWriter( fileName, nx, ny, nz, Px, Py, Pz):
    import os

    if os.path.exists(fileName):  
        os.remove(fileName)

    outFile = open(fileName, "w")

    print "writing grid file: ", fileName
    
    outFile.write('#processor block decomposition\n')
    line = 'sms(%i,%i,%i)\n' % (Px,Py,Pz)
    outFile.write( line )
    
    outFile.write('#Always specify blocks in block base numbering\n')
    line = 'blk(on,0:%i,0:%i,0:%i)\n' % (Px-1,Py-1,Pz-1)
    outFile.write( line )
    
    outFile.write('#number of zones per cpu\n')
    line = 'numzones(%i,%i,%i)\n' % (nx,ny,nz)
    outFile.write( line )
    
    outFile.write('#boundary tag information\n')
    line = 'tag("xMinFaces",face,(0:0,0:%i,0:%i))\n'   % (Py,Pz)
    outFile.write( line )
    line = 'tag("xMaxFaces",face,(%i:%i,0:%i,0:%i))\n' % (Px,Px,Py,Pz)
    outFile.write( line )
    line = 'tag("yMinFaces",face,(0:%i,0:0,0:%i))\n'   % (Px,Pz)
    outFile.write( line )
    line = 'tag("yMaxFaces",face,(0:%i,%i:%i,0:%i))\n' % (Px,Py,Py,Pz)
    outFile.write( line )
    line = 'tag("zMinFaces",face,(0:%i,0:%i,0:0))\n'   % (Px,Py)
    outFile.write( line )
    line = 'tag("zMaxFaces",face,(0:%i,0:%i,%i:%i))\n' % (Px,Py,Pz,Pz)
    outFile.write( line )
    
    outFile.write('#Hex subdivisions\n')
    line = 'sub(%s,0:%i, 0:%i, 0:%i,(7,0,0,0)) #7 hex\n' % ("10%",Px-1,Py-1,Pz-1)
    outFile.write( line )
    
    outFile.write('seed(10)\n')
    
    outFile.close()

