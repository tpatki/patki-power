topsrcdir=..

include ../make.defs

all: _TetonTest.so

ifeq ($(CLASS),bgp)

INCPATH += -I. -I../Teton -I../Install/python2.5 \
      -I../cmg2Kull/sources -I../CMG_CLEAN/src -I$(CWD)/../part
# Our locally built libs that need to be linked in
LIBS += -L$(PPCFLOOR)/gnu-linux/lib/python2.5/config -lpython2.5

else

INCPATH += -I. -I../Teton -I../Install/include/python2.6 $(MPI_INC_PATH) \
	-I../cmg2Kull/sources -I../CMG_CLEAN/src -I$(CWD)/../part
# Our locally built libs that need to be linked in
LIBS += -lInfrastructure -lc2k -lTetonUtils -lcmgp -lpython2.6

endif

LIBPATH += $(PLATFORM_LIBPATH_EXTRAS)
LIBS += $(PLATFORM_TetonTest_EXTRAS)

# swig wrapper rule only needed for developer build
ifeq ($(CLASS),linux)

TetonTest_wrap.cc: TetonTest.sw
	swig -c++ -python -I../Teton $(INCPATH) -o $@ $^

endif

_TetonTest.so: TetonTest_wrap.o ../Teton/TetonTest.o 
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBPATH) $(LIBS)

ifeq ($(CLASS),bgp)
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

TetonTest_wrap.cc: TetonTest.sw
	swig -c++ -python -I../Teton $(INCPATH) -o $@ $^

_TetonTest.so: TetonTest_wrap.o ../Teton/TetonTest.o 
	$(CXX) $(CXXFLAGS) $(CXXLDFLAGS) -o $@ $^ $(LIBPATH) $(LIBS)
endif

clean:
	rm -f *.so *.o

veryclean: clean

swigclean: clean
	rm -f TetonTest_wrap.cc TetonTest.py

