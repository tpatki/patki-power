topsrcdir = ../..

include $(topsrcdir)/make.defs

INCPATH += -I.

all: libcmgp.$(LIB_EXT)

LIB_SOURCES := lex.yy.c cmgparse.tab.c meshAndInputData.c CMGDomainQuery.c \
CMGIO.c CMGGenerator.c CMGMeshQuery.c CMGGlobalMeshQuery.c CMGTagQuery.c \
CMGMeshTopology.c dataTypes.c fortranUtilities.c subdivision.c 

LIB_OBJECTS :=$(LIB_SOURCES:.c=.o)

ifeq ($(CLASS),aix)
lex.yy.c: cmgparse.lex cmgparse.tab.c
	/g/g10/bmiller/aix_5_64_fed/bin/flex cmgparse.lex

cmgparse.tab.c: cmgparse.y
	/g/g10/bmiller/aix_5_64_fed/bin/bison -d $^

ifeq ($(STATIC_LINK),on)
libcmgp.$(LIB_EXT): $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $@ $^
else
libcmgp.$(LIB_EXT): $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(CLIBPATH) -lxlopt $(MPI_LIB_PATH) $(MPI_LIBS) $(TAU_LIBS) $(PYTHON_LIB)
endif

else
#lex.yy.c: cmgparse.lex cmgparse.tab.c
lex.yy.c: cmgparse.tab.c
	flex cmgparse.lex

#cmgparse.tab.c: cmgparse.y
cmgparse.tab.c:
	bison -d cmgparse.y

ifeq ($(STATIC_LINK),on)
libcmgp.$(LIB_EXT): $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $@ $^
else
libcmgp.$(LIB_EXT): $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
endif

endif

clean:
	rm -f *.o libcmgp.* *.pdb *.inst.*

ifeq ($(CLASS),aix)
veryclean: clean   # don't remove generated files on AIX for now
else
veryclean: clean
	rm -f cmgparse.tab.c cmgparse.tab.h lex.yy.c
endif
