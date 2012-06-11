topsrcdir=..

include ../make.defs

ifeq ($(CLASS),bgp)

INCPATH += -I. -I../Teton -I../Install/python2.5 \
      -I../cmg2Kull/sources -I../CMG_CLEAN/src -I$(CWD)/../part
# Our locally built libs that need to be linked in
LIBS += -L$(PPCFLOOR)/gnu-linux/lib/python2.5/config -lpython2.5

else
INCPATH += -I. -I../cmg2Kull/sources -I../CMG_CLEAN/src
endif

# Our locally built libs that need to be linked in
ifeq ($(CLASS),bgp)

ifeq ($(STATIC_LINK),on)
LIBPATH =
EXE_LIBS += $(PLATFORM_EXE_EXTRAS) -lInfrastructure -lTetonUtils -lc2k -lcmgp $(FLIBS) $(LIBS) 
else
LIBPATH += -L$(CWD)/../Teton/geom/CMI \
	-L$(CWD)/../Teton/transport/TetonInterface \
	-L$(CWD)/../Teton/transport/Teton \
	-L$(CWD)/../cmg2Kull/sources -Wl,-rpath $(CWD)/../cmg2Kull/sources\
	-L$(CWD)/../CMG_CLEAN/src -Wl,-rpath $(CWD)/../CMG_CLEAN/src\
	-L$(CWD)/../Teton/geom/Field \
	-L$(CWD)/../Teton/geom/Region \
	-L$(CWD)/../Teton/communication \
	-L$(CWD)/../Teton/part \
	-L$(CWD)/../Teton -Wl,-rpath $(CWD)/../Teton\
	-L$(PPCFLOOR)/runtime/SPI \
	-L$(PPCFLOOR)/comm/lib \
	-L/opt/ibmcmp/lib/bg/bglib -L/opt/ibmcmp/vacpp/bg/9.0/bglib

LIBS    += -lSPI.cna -lInfrastructure -lc2k -lTetonUtils -lm -lcmgp -ldl $(FLIBS) -ldcmfcoll.cnk -ldcmf.cnk -lpthread -lrt -lc -libmc++
CXXLDFLAGS = $(LDFLAGS)
EXE_LIBS += $(PLATFORM_EXE_EXTRAS) -lInfrastructure -lTetonUtils -lc2k -lcmgp $(FLIBS) $(LIBS) 

LINKFLAGS = -qnostaticlink -qpic=large $(GPROF_FLAGS) -g
endif

else
EXE_LIBS += $(PLATFORM_EXE_EXTRAS) -lInfrastructure -lTetonUtils -lc2k -lcmgp $(FLIBS) $(LIBS) 

LIBPATH += $(PLATFORM_LIBPATH_EXTRAS)
endif

UTILS_SOURCES = TetonUtils.cc
UTILS_OBJECTS = $(UTILS_SOURCES:.cc=.o)

INFRASTRUCTURE_OBJECTS=communication/DomainNeighborMapInst.o communication/CommAgent.o \
	geom/Region/RegionInst.o geom/Field/FieldInst.o geom/CMI/MeshBase.o geom/CMI/ZoneBase.o \
	geom/CMI/CornerBase.o geom/CMI/FaceBase.o geom/CMI/SideBase.o part/OpacityBase.o part/PartInst.o \
	transport/TetonInterface/TetonNT.o transport/TetonInterface/TetonInst.o \
	transport/Teton/mods/Communicator_mod.o transport/Teton/mods/Editor_mod.o transport/Teton/mods/Geometry_mod.o \
	transport/Teton/mods/Material_mod.o transport/Teton/mods/ProfileList_mod.o \
	transport/Teton/mods/Profile_mod.o transport/Teton/mods/QuadratureList_mod.o \
	transport/Teton/mods/Quadrature_mod.o transport/Teton/mods/Size_mod.o \
	transport/Teton/mods/TimeStepControls_mod.o transport/Teton/mods/constant_mod.o \
	transport/Teton/mods/io_mod.o transport/Teton/mods/iter_control_list_mod.o \
	transport/Teton/mods/iter_control_mod.o transport/Teton/mods/kind_mod.o \
	transport/Teton/mods/radconstant_mod.o transport/Teton/misc/assert.o \
	transport/Teton/misc/f90advise.o transport/Teton/misc/f90fatal.o \
	transport/Teton/misc/mpi_param_mod.o transport/Teton/misc/mpif90_mod.o \
	transport/Teton/aux/ConstructDtControls.o transport/Teton/aux/ConstructEditor.o \
	transport/Teton/aux/ConstructGeometry.o transport/Teton/aux/ConstructIterControls.o \
	transport/Teton/aux/ConstructMaterial.o transport/Teton/aux/ConstructProfile.o \
	transport/Teton/aux/ConstructQuadrature.o transport/Teton/aux/ConstructSize.o \
	transport/Teton/aux/ReConstructPsi.o transport/Teton/aux/ResetSize.o \
	transport/Teton/aux/addProfile.o transport/Teton/aux/getEdits.o \
	transport/Teton/aux/getRunStats.o transport/Teton/aux/setGeometry.o \
	transport/Teton/aux/setMaterialModule.o transport/Teton/aux/setSnOrder.o \
	transport/Teton/aux/setTimeStep.o transport/Teton/control/RadMoments.o \
	transport/Teton/control/advanceRT.o transport/Teton/control/assert_mesh.o \
	transport/Teton/control/dtnew.o transport/Teton/control/newenergy.o \
	transport/Teton/control/profint.o transport/Teton/control/radtr.o \
	transport/Teton/control/rtbatch.o transport/Teton/control/rtbdry.o \
	transport/Teton/control/rtedit.o transport/Teton/control/rtinit.o \
	transport/Teton/control/rtvsrc.o transport/Teton/rt/AngleCoef1D.o \
	transport/Teton/rt/AngleCoef2D.o transport/Teton/rt/FluxFixUp.o \
	transport/Teton/rt/InitExchange.o transport/Teton/rt/SweepScheduler.o \
	transport/Teton/rt/UpdateTemperature.o transport/Teton/rt/bdyedt.o \
	transport/Teton/rt/exchange.o transport/Teton/rt/face_coords.o \
	transport/Teton/rt/findexit.o transport/Teton/rt/getAbsorptionRate.o \
	transport/Teton/rt/initcomm.o transport/Teton/rt/quadLobatto.o \
	transport/Teton/rt/quadProduct.o transport/Teton/rt/quadcy.o \
	transport/Teton/rt/quadfilter.o transport/Teton/rt/quadrz.o \
	transport/Teton/rt/quadslab.o transport/Teton/rt/quadsp.o \
	transport/Teton/rt/quadxyz.o transport/Teton/rt/rswp1d.o \
	transport/Teton/rt/rswpmd.o transport/Teton/rt/rtave.o \
	transport/Teton/rt/rtcompton.o transport/Teton/rt/rtconi.o \
	transport/Teton/rt/rtconv.o transport/Teton/rt/rtgeom1.o \
	transport/Teton/rt/rtgeom2.o transport/Teton/rt/rtgeom3.o \
	transport/Teton/rt/rtgsrc.o transport/Teton/rt/rtmainsn.o \
	transport/Teton/rt/rtmatc.o transport/Teton/rt/rtnete.o \
	transport/Teton/rt/rtorder.o transport/Teton/rt/rtplnk.o \
	transport/Teton/rt/rtquad.o transport/Teton/rt/rtscal.o \
	transport/Teton/rt/rtstartdir.o transport/Teton/rt/rtstrtsn.o \
	transport/Teton/rt/rtswpsc.o transport/Teton/rt/rtswpslb.o \
	transport/Teton/rt/rtti.o transport/Teton/rt/setbdy.o \
	transport/Teton/rt/zone_coords.o transport/Teton/snac/GaussLegendreLobattoWgts.o \
	transport/Teton/snac/Jacobi.o transport/Teton/snac/JacobiLobattoPts.o \
	transport/Teton/snac/assoc_legendre.o transport/Teton/snac/cyclebreaker.o \
	transport/Teton/snac/factorial.o transport/Teton/snac/findseeds.o \
	transport/Teton/snac/fixcycles.o transport/Teton/snac/harmonics.o \
	transport/Teton/snac/harmonics_1d.o transport/Teton/snac/harmonics_2d.o \
	transport/Teton/snac/harmonics_3d.o transport/Teton/snac/kronecker.o \
	transport/Teton/snac/sccsearch.o transport/Teton/snac/setsig.o \
	transport/Teton/snac/snbsets.o transport/Teton/snac/snflwxyz.o \
	transport/Teton/snac/snmoments.o transport/Teton/snac/snmref.o \
	transport/Teton/snac/snneed.o transport/Teton/snac/snnext.o \
	transport/Teton/snac/snpnmset.o transport/Teton/snac/snqq.o \
	transport/Teton/snac/snreflect.o transport/Teton/snac/snrzammh.o \
	transport/Teton/snac/snswp2d.o transport/Teton/snac/snswp3d.o transport/Teton/snac/snynmset.o


all: subdirs libInfrastructure.$(LIB_EXT) libTetonUtils.$(LIB_EXT) TetonTest.o

ifeq ($(STATIC_LINK),on)
libInfrastructure.$(LIB_EXT):$(INFRASTRUCTURE_OBJECTS)
	$(LD) $(LDFLAGS) $@ $^ $(LIBPATH) $(PLATFORM_Infrastructure_EXTRAS)

libTetonUtils.$(LIB_EXT):$(UTILS_OBJECTS)
	$(LD) $(LDFLAGS) $@ $^ $(LIBPATH) $(PLATFORM_TetonUtils_EXTRAS)

else # shared lib link rule

libInfrastructure.$(LIB_EXT):$(INFRASTRUCTURE_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBPATH) $(PLATFORM_Infrastructure_EXTRAS)

libTetonUtils.$(LIB_EXT):$(UTILS_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBPATH) $(PLATFORM_TetonUtils_EXTRAS)

endif # end of static/shared lib switch

# SuOlsonTest target only for internal testing purposes
SuOlsonTest:SuOlsonTest.o libTetonUtils.$(LIB_EXT) transport part communication
	$(LINK) $(LINKFLAGS) $< -o $@ $(LIBPATH) $(EXE_LIBS)

SUBDIRS = geom communication part transport

deps: TetonTest.d SuOlsonTest.d


.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

communication: geom
part: geom
transport: geom

-include TetonTest.d
-include SuOlsonTest.d

clean:
	@for i in ${SUBDIRS} ; do (cd $$i; $(MAKE) clean); done
	rm -f *.o  *.pdb *.inst.* TetonTest SuOlsonTest libInfrastructure.* libTetonUtils.*

veryclean: clean
	@for i in ${SUBDIRS} ; do (cd $$i; $(MAKE) veryclean); done
	rm -f *.d
