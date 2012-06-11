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
from TetonTest import *
import mpi
import os.path
import sys
from optparse import OptionParser

# ----------------------------------------------------------------------
# Quadrature order and number of energy groups are input parameters
# which have reasonable default settings.
# ----------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-x", "--numberOfXzones", type="int",dest="nx",default=13,
                  help="Number of zones in x-direction (per MPI task).  Default=13.")
parser.add_option("-y", "--numberOfYzones", type="int",dest="ny",default=13,
                  help="Number of zones in y-direction (per MPI task).  Default=13.")
parser.add_option("-z", "--numberOfZzones", type="int",dest="nz",default=13,
                  help="Number of zones in z-direction (per MPI task).  Default=13.")
parser.add_option("--Px",type="int",dest="Px",default=0,
                  help="Number of mpi tasks in x-direction.  If set to 0, compute on the fly.  Default=0")
parser.add_option("--Py",type="int",dest="Py",default=0,
                  help="Number of mpi tasks in y-direction.  If set to 0, compute on the fly.  Default=0")
parser.add_option("--Pz",type="int",dest="Pz",default=0,
                  help="Number of mpi tasks in z-direction.  If set to 0, compute on the fly.  Default=0")
parser.add_option("-o", "--order", type="int",dest="SNorder",default=12,
                  help="SN quadrature order.  Default=12.")
parser.add_option("-g", "--groups",type="int",dest="numberOfGroups",default=16,
                  help="Number of Energy Groups.  Default=16.")
parser.add_option("-t", "--goaltime",type="float",dest="goaltime",default=0.000334,
                  help="goal time.  Exact solution known for 0.000334, 0.001055, 0.003336.  Default=0.000334")

(options, args) = parser.parse_args()

nx = options.nx
ny = options.ny
nz = options.nz
Px = options.Px
Py = options.Py
Pz = options.Pz
Order = options.SNorder
numgp = options.numberOfGroups
goalTime = options.goaltime

from writeGridFile import *
problem = writeGridFile( nx, ny, nz, Px, Py, Pz, mpi.procs )

if not os.path.isfile(problem) :
   if mpi.rank == 0:
      print "mesh file ",problem,"not found!"
   sys.exit()

# Benchmark Version Number
versionNumber = "1.0"

#  Quadrature Types 
LevelSym = 1
Product  = 2
Lobatto  = 3
#  Quadrature Parameters
Npolar = 4
Nazimu = 3
PolarAxis = 1
#  Teton parameters
igeom = "xyz     "
iaccel = "off     " #gda = acceleration, off = none
GTAorder = 2
dtrad = 3.0e-6
noutmx = 20
ninmx = 1
ngdamx = 7
epsgda = 1.00e-07
epstmp = 1.00e-06
epsinr = 1.00e-06
deltr = 0.40
delte = 0.40
dtrmn = 0.00006
dtrmx = 0.1
tfloor = 2.5e-5
tmin   = 5.0e-3
#-----------------------------------------------------------------------

# Build mesh
if mpi.rank == 0:
   print "Constructing mesh."
mesh = MeshBase(problem)
if mpi.rank == 0:
   print "Mesh construction complete, next building region, opacity, material, etc."

# Build region, opacity, material
region = Region_MeshBase(mesh)
opacity = OpacityBase()
material = Material(opacity)

T0 = pow( 10.0, -2.5 )
#T0 = 0.0
density0 = 1.0
# Build part list
part = Part_MeshBase(region, material, MARSHAK, density0, T0)
partList = PartList_MeshBase(mesh)
partList.addPart(part)

# Build teton
teton = Teton_MeshBase()
teton.igeom = igeom
teton.iaccel = iaccel
teton.ngr = numgp
teton.GTAorder = GTAorder
teton.dtrad = dtrad
teton.noutmx = noutmx
teton.ninmx = ninmx
teton.ngdamx = ngdamx
teton.epsgda = epsgda
teton.epstmp = epstmp
teton.epsinr = epsinr
teton.deltr = deltr
teton.delte = delte
teton.dtrmn = dtrmn
teton.dtrx = dtrmx
teton.tfloor = tfloor
teton.tmin = tmin

tetonBoundaries = TetonBoundaryVector()

PXlookup = IntVector(mesh.getNumberOfOwnedNodes(), -1)

# Build teton frequencies
tetonFreqs = TetonFreqVector(numgp)

tetonFreqs[0] = (TetonFreq(0.0001, 200, LevelSym, Order, Npolar, Nazimu, PolarAxis))

if numgp > 1:
      tetonFreqs[0] = (TetonFreq(0.0001, 0.01, LevelSym, Order, Npolar, Nazimu, PolarAxis))
      tetonFreqs[1] = (TetonFreq(0.01  , 0.05, LevelSym, Order, Npolar, Nazimu, PolarAxis))
      for i in range(2,numgp):
         tetonFreqs[i] = (TetonFreq(.05*(i-1), 0.05*i, LevelSym, Order, Npolar, Nazimu, PolarAxis))

#  Apply a temperature source over z <= 0.5
iso_source_zone_list = IntVector()
getZoneIDs('z', 0.5, mesh, iso_source_zone_list)

srcTemp = 1.0

timeTemps = TimeTempsVector([0.0, srcTemp, 10.0, srcTemp, 10.01, 0.0, 150.0, 0.0])

isotropic_source = TetonVolumeSource(iso_source_zone_list, "Source  ", "temp    ", "iso     ", 1.0, timeTemps)

radVSs1 = TetonVolumeSourceVector(1)
radVSs1[0] = isotropic_source

bdryFaceTags = StringVector(6)
bcNames      = StringVector(6)
srcNames     = StringVector(6)

bdryFaceTags[0] = "xMinFaces"
bdryFaceTags[1] = "xMaxFaces"
bdryFaceTags[2] = "yMinFaces"
bdryFaceTags[3] = "yMaxFaces"
bdryFaceTags[4] = "zMinFaces"
bdryFaceTags[5] = "zMaxFaces"

bcNames[0] = "Refl    "
srcNames[0] = "refl    "
bcNames[1] = "Refl    "
srcNames[1] = "refl    "
bcNames[2] = "Refl    "
srcNames[2] = "refl    "
bcNames[3] = "Refl    "
srcNames[3] = "refl    "
bcNames[4] = "Refl    "
srcNames[4] = "refl    "
bcNames[5] = "Vac     "
srcNames[5] = "vac     "

totWorkTime = 0.0
totIters = 0

myNumZones = mesh.getNumberOfOwnedZones()

if mpi.rank == 0:
   print "mesh and data setup complete, building Teton object."

setBoundary(mesh, tetonBoundaries, bdryFaceTags, bcNames, srcNames)
teton.linkKull(mesh, tetonFreqs, tetonBoundaries, radVSs1, PXlookup)
teton.CInitMaterial(partList)
teton.CsetControls()


##goalTime = 0.000334   # corresponds to tau=0.10000 in Su-Olson paper
##goalTime = 0.001055   # corresponds to tau=0.31623 in Su-Olson paper
##goalTime = 0.003336   # corresponds to tau=1.00000 in Su-Olson paper
time  = 0.0

mpi.barrier()

if mpi.rank == 0:
   print "Setup complete, beginning time steps."

cycle=0
while time < goalTime:
   dt = newDT(teton)

   if time + dt >= goalTime:
      dt = goalTime-time
      teton.dtrmn = dt

   teton.dtrad = dt
   
   cycleTime = advance(mesh, teton, partList)
   totWorkTime= totWorkTime + cycleTime
   totIters = totIters + teton.ninrt
   time = time + dt
   cycle = cycle + 1


mpi.barrier()
totMeshZones = mpi.reduce(myNumZones,mpi.SUM)

checkAnalyticAnswer(goalTime, mesh, partList)

if mpi.rank == 0:
   numUnknowns = teton.ngr * teton.nangsn * totMeshZones * 8
   dumpLineout(mesh, teton,"final.out")
   totWorkTime/=1.0e6
   print "proc 0 num zones =",myNumZones,"  Total mesh zones = ",totMeshZones
   print "SuOlson test version ",versionNumber," completed at time=",time,"   goalTime=",goalTime
   print "Cumulative Iteration Count: ",totIters
   print "Cumulative Cycle Advance Time: ",totWorkTime," s."
   print "Cumulative Angle Loop Time:    ",teton.angleLoopTime, " s."
   print "numUnknowns = ",numUnknowns
   grindTime = totWorkTime /( numUnknowns * totIters * mpi.size)
   print " grind time = ",grindTime
   print " Figure of merit = ",numUnknowns/totWorkTime * totIters
   
