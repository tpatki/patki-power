
################################################################################
#
# Makefile for irs library tdiff
#

all:
	@ echo " "
	@ echo "Error:"
	@ echo "This Makefile must be called by the driving Makefile."
	@ echo " "

################################################################################

# Must use the bourne shell
#---------------------------
SHELL = /bin/sh

# Harmless suffix rule:
#----------------------
.SUFFIXES : .U

# library relative path name
#----------------------------
B = ../$(LIB_DIR)/libtdiff.a
BI = ../$(LIB_DIR)/libtdiff_inst.a

# Relative path to the directory of sources for the debugger
#-----------------------------------------------------------
DB  = ../../debug

# Relative path to the instrumented source directory from the source directory
#-----------------------------------------------------------------------------
PREDIR = ../../mccabe/pre
INSTDIR = ../../mccabe/inst

# Relative path to the instrumented source directory from the debug directory
#-----------------------------------------------------------------------------
INSTDIR_D = ../mccabe/inst

# Relative path to the source directory from the debug directory
#----------------------------------------------------------------
SRCDIR = ../sources/tdiff

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libtdiff:$(B)(ChemPotCalc.o) $(B)(ConductionCoef.o) $(B)(DiffCoef.o)              \
	  $(B)(DivgradDriver.o) $(B)(FemDivgrad3.o) $(B)(FemGrad3d.o)             \
	  $(B)(FluxLimiter2d.o) $(B)(FluxLimiter3d.o) $(B)(FluxLimiterDriver.o)   \
	  $(B)(GefaGedi.o) $(B)(KpAnalytic.o) $(B)(KrAnalytic.o)                  \
	  $(B)(MatrixSolve.o) $(B)(MatterConduction.o) $(B)(MatterDiagonal.o)     \
	  $(B)(MatterWainwright.o) $(B)(RadiationMemory.o)                        \
	  $(B)(RadiationSourceBC.o) $(B)(RegionTable.o)                           \
	  $(B)(SetFaceTemperature.o) $(B)(bound_free.o) $(B)(cblkbc.o)            \
	  $(B)(cblkbc2.o) $(B)(cblkbc3.o) $(B)(diagonal.o) $(B)(diff1g.o)         \
	  $(B)(divgrad2.o) $(B)(divgrad3.o) $(B)(divgradpert2d.o)                 \
	  $(B)(divgradpert3d.o) $(B)(geteicouple.o) $(B)(gettfzstar.o)            \
	  $(B)(getzabar0.o) $(B)(gtkappabnd.o) $(B)(kapmlt.o) $(B)(newMatrix.o)   \
	  $(B)(norml2.o) $(B)(opac2t.o) $(B)(opaclmt.o) $(B)(planck_opacity.o)    \
	  $(B)(radfree.o) $(B)(radinit.o) $(B)(rdiff.o) $(B)(rdiffbc.o)           \
	  $(B)(rdiffbc2.o) $(B)(rdiffbc3.o) $(B)(rdiffset.o) $(B)(rdiffsrc.o)     \
	  $(B)(reicouple.o) $(B)(retransfer.o) $(B)(rmatmult.o) $(B)(rmatmult2.o) \
	  $(B)(rmatmult3.o) $(B)(rsrcbc.o) $(B)(rsrcbc2.o) $(B)(rsrcbc3.o)        \
	  $(B)(setpz1.o) $(B)(setpz2.o) $(B)(tblkinit.o) $(B)(tdiff.o)            \
	  $(B)(teicouple.o) $(B)(zstarcal.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'tdiff library current'

# creation deps
#---------------
$(B)(ChemPotCalc.o):ChemPotCalc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ChemPotCalc.c $(DB)/ChemPotCalc.c 

$(B)(ConductionCoef.o):ConductionCoef.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ConductionCoef.c $(DB)/ConductionCoef.c 

../../includes/DiffusionData.hh:../../includes/DiffusionData.h
	cp ../../includes/DiffusionData.h ../../includes/DiffusionData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/DiffusionData.hh
	irs_hhinit ../../includes/DiffusionData.hh

$(B)(DiffCoef.o):../../includes/DiffusionData.hh

$(B)(DiffCoef.o):DiffCoef.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DiffCoef.c $(DB)/DiffCoef.c 

$(B)(DivgradDriver.o):DivgradDriver.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DivgradDriver.c $(DB)/DivgradDriver.c 

$(B)(FemDivgrad3.o):FemDivgrad3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FemDivgrad3.c $(DB)/FemDivgrad3.c 

$(B)(FemGrad3d.o):FemGrad3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FemGrad3d.c $(DB)/FemGrad3d.c 

$(B)(FluxLimiter2d.o):FluxLimiter2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiter2d.c $(DB)/FluxLimiter2d.c 

$(B)(FluxLimiter3d.o):FluxLimiter3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiter3d.c $(DB)/FluxLimiter3d.c 

$(B)(FluxLimiterDriver.o):FluxLimiterDriver.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiterDriver.c $(DB)/FluxLimiterDriver.c 

$(B)(GefaGedi.o):GefaGedi.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/GefaGedi.c $(DB)/GefaGedi.c 

$(B)(KpAnalytic.o):KpAnalytic.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/KpAnalytic.c $(DB)/KpAnalytic.c 

$(B)(KrAnalytic.o):KrAnalytic.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/KrAnalytic.c $(DB)/KrAnalytic.c 

$(B)(MatrixSolve.o):MatrixSolve.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatrixSolve.c $(DB)/MatrixSolve.c 

$(B)(MatterConduction.o):MatterConduction.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterConduction.c $(DB)/MatterConduction.c 

$(B)(MatterDiagonal.o):MatterDiagonal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterDiagonal.c $(DB)/MatterDiagonal.c 

$(B)(MatterWainwright.o):MatterWainwright.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterWainwright.c $(DB)/MatterWainwright.c 

../../includes/RadiationData.hh:../../includes/RadiationData.h
	cp ../../includes/RadiationData.h ../../includes/RadiationData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/RadiationData.hh
	irs_hhinit ../../includes/RadiationData.hh

$(B)(RadiationMemory.o):../../includes/RadiationData.hh

$(B)(RadiationMemory.o):RadiationMemory.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RadiationMemory.c $(DB)/RadiationMemory.c 

$(B)(RadiationSourceBC.o):RadiationSourceBC.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RadiationSourceBC.c $(DB)/RadiationSourceBC.c 

$(B)(RegionTable.o):RegionTable.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RegionTable.c $(DB)/RegionTable.c 

$(B)(SetFaceTemperature.o):SetFaceTemperature.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/SetFaceTemperature.c $(DB)/SetFaceTemperature.c 

$(B)(bound_free.o):bound_free.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bound_free.c $(DB)/bound_free.c 

$(B)(cblkbc.o):cblkbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc.c $(DB)/cblkbc.c 

$(B)(cblkbc2.o):cblkbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc2.c $(DB)/cblkbc2.c 

$(B)(cblkbc3.o):cblkbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc3.c $(DB)/cblkbc3.c 

$(B)(diagonal.o):diagonal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/diagonal.c $(DB)/diagonal.c 

$(B)(diff1g.o):diff1g.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/diff1g.c $(DB)/diff1g.c 

$(B)(divgrad2.o):divgrad2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgrad2.c $(DB)/divgrad2.c 

$(B)(divgrad3.o):divgrad3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgrad3.c $(DB)/divgrad3.c 

$(B)(divgradpert2d.o):divgradpert2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgradpert2d.c $(DB)/divgradpert2d.c 

$(B)(divgradpert3d.o):divgradpert3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgradpert3d.c $(DB)/divgradpert3d.c 

$(B)(geteicouple.o):geteicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geteicouple.c $(DB)/geteicouple.c 

$(B)(gettfzstar.o):gettfzstar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gettfzstar.c $(DB)/gettfzstar.c 

$(B)(getzabar0.o):getzabar0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getzabar0.c $(DB)/getzabar0.c 

$(B)(gtkappabnd.o):gtkappabnd.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gtkappabnd.c $(DB)/gtkappabnd.c 

$(B)(kapmlt.o):kapmlt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/kapmlt.c $(DB)/kapmlt.c 

$(B)(newMatrix.o):newMatrix.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/newMatrix.c $(DB)/newMatrix.c 

$(B)(norml2.o):norml2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/norml2.c $(DB)/norml2.c 

$(B)(opac2t.o):opac2t.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/opac2t.c $(DB)/opac2t.c 

$(B)(opaclmt.o):opaclmt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/opaclmt.c $(DB)/opaclmt.c 

$(B)(planck_opacity.o):planck_opacity.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/planck_opacity.c $(DB)/planck_opacity.c 

$(B)(radfree.o):radfree.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/radfree.c $(DB)/radfree.c 

$(B)(radinit.o):radinit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/radinit.c $(DB)/radinit.c 

$(B)(rdiff.o):rdiff.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiff.c $(DB)/rdiff.c 

$(B)(rdiffbc.o):rdiffbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc.c $(DB)/rdiffbc.c 

$(B)(rdiffbc2.o):rdiffbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc2.c $(DB)/rdiffbc2.c 

$(B)(rdiffbc3.o):rdiffbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc3.c $(DB)/rdiffbc3.c 

$(B)(rdiffset.o):rdiffset.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffset.c $(DB)/rdiffset.c 

$(B)(rdiffsrc.o):rdiffsrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffsrc.c $(DB)/rdiffsrc.c 

$(B)(reicouple.o):reicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/reicouple.c $(DB)/reicouple.c 

$(B)(retransfer.o):retransfer.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/retransfer.c $(DB)/retransfer.c 

$(B)(rmatmult.o):rmatmult.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult.c $(DB)/rmatmult.c 

$(B)(rmatmult2.o):rmatmult2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult2.c $(DB)/rmatmult2.c 

$(B)(rmatmult3.o):rmatmult3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult3.c $(DB)/rmatmult3.c 

$(B)(rsrcbc.o):rsrcbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc.c $(DB)/rsrcbc.c 

$(B)(rsrcbc2.o):rsrcbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc2.c $(DB)/rsrcbc2.c 

$(B)(rsrcbc3.o):rsrcbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc3.c $(DB)/rsrcbc3.c 

$(B)(setpz1.o):setpz1.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setpz1.c $(DB)/setpz1.c 

$(B)(setpz2.o):setpz2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setpz2.c $(DB)/setpz2.c 

$(B)(tblkinit.o):tblkinit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tblkinit.c $(DB)/tblkinit.c 

$(B)(tdiff.o):tdiff.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tdiff.c $(DB)/tdiff.c 

$(B)(teicouple.o):teicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/teicouple.c $(DB)/teicouple.c 

$(B)(zstarcal.o):zstarcal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/zstarcal.c $(DB)/zstarcal.c 

#---------------------
# lint pass one target 
#---------------------
lint:ChemPotCalc.ln ConductionCoef.ln DiffCoef.ln DivgradDriver.ln FemDivgrad3.ln \
	  FemGrad3d.ln FluxLimiter2d.ln FluxLimiter3d.ln FluxLimiterDriver.ln     \
	  GefaGedi.ln KpAnalytic.ln KrAnalytic.ln MatrixSolve.ln                  \
	  MatterConduction.ln MatterDiagonal.ln MatterWainwright.ln               \
	  RadiationMemory.ln RadiationSourceBC.ln RegionTable.ln                  \
	  SetFaceTemperature.ln bound_free.ln cblkbc.ln cblkbc2.ln cblkbc3.ln     \
	  diagonal.ln diff1g.ln divgrad2.ln divgrad3.ln divgradpert2d.ln          \
	  divgradpert3d.ln geteicouple.ln gettfzstar.ln getzabar0.ln              \
	  gtkappabnd.ln kapmlt.ln newMatrix.ln norml2.ln opac2t.ln opaclmt.ln     \
	  planck_opacity.ln radfree.ln radinit.ln rdiff.ln rdiffbc.ln rdiffbc2.ln \
	  rdiffbc3.ln rdiffset.ln rdiffsrc.ln reicouple.ln retransfer.ln          \
	  rmatmult.ln rmatmult2.ln rmatmult3.ln rsrcbc.ln rsrcbc2.ln rsrcbc3.ln   \
	  setpz1.ln setpz2.ln tblkinit.ln tdiff.ln teicouple.ln zstarcal.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
ChemPotCalc.ln:ChemPotCalc.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ChemPotCalc.c ***' >> $(LO)
	$$irs_lint ChemPotCalc.c 2>&1 | tee -a $(LO)

ConductionCoef.ln:ConductionCoef.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irsdefs.h ../../includes/irstdiff.h                      \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ConductionCoef.c ***' >> $(LO)
	$$irs_lint ConductionCoef.c 2>&1 | tee -a $(LO)

DiffCoef.ln:DiffCoef.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/irsdefs.h                      \
	  ../../includes/DiffusionData.hh ../../includes/FunctionTimer.h          \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DiffCoef.c ***' >> $(LO)
	$$irs_lint DiffCoef.c 2>&1 | tee -a $(LO)

DivgradDriver.ln:DivgradDriver.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/irsgen.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DivgradDriver.c ***' >> $(LO)
	$$irs_lint DivgradDriver.c 2>&1 | tee -a $(LO)

FemDivgrad3.ln:FemDivgrad3.c ../../includes/irs.h ../../includes/irstdiff.h       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FemDivgrad3.c ***' >> $(LO)
	$$irs_lint FemDivgrad3.c 2>&1 | tee -a $(LO)

FemGrad3d.ln:FemGrad3d.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FemGrad3d.c ***' >> $(LO)
	$$irs_lint FemGrad3d.c 2>&1 | tee -a $(LO)

FluxLimiter2d.ln:FluxLimiter2d.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiter2d.c ***' >> $(LO)
	$$irs_lint FluxLimiter2d.c 2>&1 | tee -a $(LO)

FluxLimiter3d.ln:FluxLimiter3d.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiter3d.c ***' >> $(LO)
	$$irs_lint FluxLimiter3d.c 2>&1 | tee -a $(LO)

FluxLimiterDriver.ln:FluxLimiterDriver.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiterDriver.c ***' >> $(LO)
	$$irs_lint FluxLimiterDriver.c 2>&1 | tee -a $(LO)

GefaGedi.ln:GefaGedi.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON GefaGedi.c ***' >> $(LO)
	$$irs_lint GefaGedi.c 2>&1 | tee -a $(LO)

KpAnalytic.ln:KpAnalytic.c ../../includes/irsdefs.h ../../includes/irs.h          \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON KpAnalytic.c ***' >> $(LO)
	$$irs_lint KpAnalytic.c 2>&1 | tee -a $(LO)

KrAnalytic.ln:KrAnalytic.c ../../includes/irsdefs.h ../../includes/irs.h          \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON KrAnalytic.c ***' >> $(LO)
	$$irs_lint KrAnalytic.c 2>&1 | tee -a $(LO)

MatrixSolve.ln:MatrixSolve.c ../../includes/irs.h ../../includes/irssys.h         \
	  ../../includes/irscom.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/TimeStepControl.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatrixSolve.c ***' >> $(LO)
	$$irs_lint MatrixSolve.c 2>&1 | tee -a $(LO)

MatterConduction.ln:MatterConduction.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterConduction.c ***' >> $(LO)
	$$irs_lint MatterConduction.c 2>&1 | tee -a $(LO)

MatterDiagonal.ln:MatterDiagonal.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/irs.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterDiagonal.c ***' >> $(LO)
	$$irs_lint MatterDiagonal.c 2>&1 | tee -a $(LO)

MatterWainwright.ln:MatterWainwright.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterWainwright.c ***' >> $(LO)
	$$irs_lint MatterWainwright.c 2>&1 | tee -a $(LO)

RadiationMemory.ln:RadiationMemory.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/DiffusionData.h ../../includes/ProblemArray.h            \
	  ../../includes/RadiationData.hh ../../includes/pardo.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RadiationMemory.c ***' >> $(LO)
	$$irs_lint RadiationMemory.c 2>&1 | tee -a $(LO)

RadiationSourceBC.ln:RadiationSourceBC.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/irsrgst.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/Rgst.h ../../includes/RadiationData.h                    \
	  ../../includes/Source.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RadiationSourceBC.c ***' >> $(LO)
	$$irs_lint RadiationSourceBC.c 2>&1 | tee -a $(LO)

RegionTable.ln:RegionTable.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irstdiff.h ../../includes/irs.h ../../includes/Domain.h  \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RegionTable.c ***' >> $(LO)
	$$irs_lint RegionTable.c 2>&1 | tee -a $(LO)

SetFaceTemperature.ln:SetFaceTemperature.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON SetFaceTemperature.c ***' >> $(LO)
	$$irs_lint SetFaceTemperature.c 2>&1 | tee -a $(LO)

bound_free.ln:bound_free.c ../../includes/irs.h ../../includes/irstdiff.h         \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bound_free.c ***' >> $(LO)
	$$irs_lint bound_free.c 2>&1 | tee -a $(LO)

cblkbc.ln:cblkbc.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc.c ***' >> $(LO)
	$$irs_lint cblkbc.c 2>&1 | tee -a $(LO)

cblkbc2.ln:cblkbc2.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc2.c ***' >> $(LO)
	$$irs_lint cblkbc2.c 2>&1 | tee -a $(LO)

cblkbc3.ln:cblkbc3.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc3.c ***' >> $(LO)
	$$irs_lint cblkbc3.c 2>&1 | tee -a $(LO)

diagonal.ln:diagonal.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON diagonal.c ***' >> $(LO)
	$$irs_lint diagonal.c 2>&1 | tee -a $(LO)

diff1g.ln:diff1g.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON diff1g.c ***' >> $(LO)
	$$irs_lint diff1g.c 2>&1 | tee -a $(LO)

divgrad2.ln:divgrad2.c ../../includes/irsdefs.h ../../includes/irs.h              \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgrad2.c ***' >> $(LO)
	$$irs_lint divgrad2.c 2>&1 | tee -a $(LO)

divgrad3.ln:divgrad3.c ../../includes/irsdefs.h ../../includes/irs.h              \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgrad3.c ***' >> $(LO)
	$$irs_lint divgrad3.c 2>&1 | tee -a $(LO)

divgradpert2d.ln:divgradpert2d.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgradpert2d.c ***' >> $(LO)
	$$irs_lint divgradpert2d.c 2>&1 | tee -a $(LO)

divgradpert3d.ln:divgradpert3d.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgradpert3d.c ***' >> $(LO)
	$$irs_lint divgradpert3d.c 2>&1 | tee -a $(LO)

geteicouple.ln:geteicouple.c ../../includes/irsdefs.h ../../includes/irs.h        \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geteicouple.c ***' >> $(LO)
	$$irs_lint geteicouple.c 2>&1 | tee -a $(LO)

gettfzstar.ln:gettfzstar.c ../../includes/irs.h ../../includes/irstdiff.h         \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gettfzstar.c ***' >> $(LO)
	$$irs_lint gettfzstar.c 2>&1 | tee -a $(LO)

getzabar0.ln:getzabar0.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getzabar0.c ***' >> $(LO)
	$$irs_lint getzabar0.c 2>&1 | tee -a $(LO)

gtkappabnd.ln:gtkappabnd.c ../../includes/irs.h ../../includes/irscom.h           \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gtkappabnd.c ***' >> $(LO)
	$$irs_lint gtkappabnd.c 2>&1 | tee -a $(LO)

kapmlt.ln:kapmlt.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON kapmlt.c ***' >> $(LO)
	$$irs_lint kapmlt.c 2>&1 | tee -a $(LO)

newMatrix.ln:newMatrix.c ../../includes/irsdefs.h ../../includes/irs.h            \
	  ../../includes/irstdiff.h ../../includes/irs.h                          \
	  ../../includes/RadiationData.h ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON newMatrix.c ***' >> $(LO)
	$$irs_lint newMatrix.c 2>&1 | tee -a $(LO)

norml2.ln:norml2.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON norml2.c ***' >> $(LO)
	$$irs_lint norml2.c 2>&1 | tee -a $(LO)

opac2t.ln:opac2t.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON opac2t.c ***' >> $(LO)
	$$irs_lint opac2t.c 2>&1 | tee -a $(LO)

opaclmt.ln:opaclmt.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON opaclmt.c ***' >> $(LO)
	$$irs_lint opaclmt.c 2>&1 | tee -a $(LO)

planck_opacity.ln:planck_opacity.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON planck_opacity.c ***' >> $(LO)
	$$irs_lint planck_opacity.c 2>&1 | tee -a $(LO)

radfree.ln:radfree.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/ProblemArray.h ../../includes/DiffusionData.h            \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON radfree.c ***' >> $(LO)
	$$irs_lint radfree.c 2>&1 | tee -a $(LO)

radinit.ln:radinit.c ../../includes/irs.h ../../includes/irsreg.h                 \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/DiffusionData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON radinit.c ***' >> $(LO)
	$$irs_lint radinit.c 2>&1 | tee -a $(LO)

rdiff.ln:rdiff.c ../../includes/irs.h ../../includes/irscom.h                     \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/Source.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiff.c ***' >> $(LO)
	$$irs_lint rdiff.c 2>&1 | tee -a $(LO)

rdiffbc.ln:rdiffbc.c ../../includes/irs.h ../../includes/irscom.h                 \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc.c ***' >> $(LO)
	$$irs_lint rdiffbc.c 2>&1 | tee -a $(LO)

rdiffbc2.ln:rdiffbc2.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc2.c ***' >> $(LO)
	$$irs_lint rdiffbc2.c 2>&1 | tee -a $(LO)

rdiffbc3.ln:rdiffbc3.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc3.c ***' >> $(LO)
	$$irs_lint rdiffbc3.c 2>&1 | tee -a $(LO)

rdiffset.ln:rdiffset.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffset.c ***' >> $(LO)
	$$irs_lint rdiffset.c 2>&1 | tee -a $(LO)

rdiffsrc.ln:rdiffsrc.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/irscom.h ../../includes/irssrc.h                         \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffsrc.c ***' >> $(LO)
	$$irs_lint rdiffsrc.c 2>&1 | tee -a $(LO)

reicouple.ln:reicouple.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON reicouple.c ***' >> $(LO)
	$$irs_lint reicouple.c 2>&1 | tee -a $(LO)

retransfer.ln:retransfer.c ../../includes/irs.h ../../includes/irsreg.h           \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/DiffusionData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON retransfer.c ***' >> $(LO)
	$$irs_lint retransfer.c 2>&1 | tee -a $(LO)

rmatmult.ln:rmatmult.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult.c ***' >> $(LO)
	$$irs_lint rmatmult.c 2>&1 | tee -a $(LO)

rmatmult2.ln:rmatmult2.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult2.c ***' >> $(LO)
	$$irs_lint rmatmult2.c 2>&1 | tee -a $(LO)

rmatmult3.ln:rmatmult3.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult3.c ***' >> $(LO)
	$$irs_lint rmatmult3.c 2>&1 | tee -a $(LO)

rsrcbc.ln:rsrcbc.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc.c ***' >> $(LO)
	$$irs_lint rsrcbc.c 2>&1 | tee -a $(LO)

rsrcbc2.ln:rsrcbc2.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc2.c ***' >> $(LO)
	$$irs_lint rsrcbc2.c 2>&1 | tee -a $(LO)

rsrcbc3.ln:rsrcbc3.c ../../includes/irs.h ../../includes/irssrc.h                 \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc3.c ***' >> $(LO)
	$$irs_lint rsrcbc3.c 2>&1 | tee -a $(LO)

setpz1.ln:setpz1.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setpz1.c ***' >> $(LO)
	$$irs_lint setpz1.c 2>&1 | tee -a $(LO)

setpz2.ln:setpz2.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setpz2.c ***' >> $(LO)
	$$irs_lint setpz2.c 2>&1 | tee -a $(LO)

tblkinit.ln:tblkinit.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/irscom.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tblkinit.c ***' >> $(LO)
	$$irs_lint tblkinit.c 2>&1 | tee -a $(LO)

tdiff.ln:tdiff.c ../../includes/irs.h ../../includes/irsgen.h                     \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/SpeciesFraction.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tdiff.c ***' >> $(LO)
	$$irs_lint tdiff.c 2>&1 | tee -a $(LO)

teicouple.ln:teicouple.c ../../includes/irs.h ../../includes/irsreg.h             \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON teicouple.c ***' >> $(LO)
	$$irs_lint teicouple.c 2>&1 | tee -a $(LO)

zstarcal.ln:zstarcal.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON zstarcal.c ***' >> $(LO)
	$$irs_lint zstarcal.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/ChemPotCalc.inst.i $(PREDIR)/ConductionCoef.inst.i           \
	  $(PREDIR)/DiffCoef.inst.i $(PREDIR)/DivgradDriver.inst.i                \
	  $(PREDIR)/FemDivgrad3.inst.i $(PREDIR)/FemGrad3d.inst.i                 \
	  $(PREDIR)/FluxLimiter2d.inst.i $(PREDIR)/FluxLimiter3d.inst.i           \
	  $(PREDIR)/FluxLimiterDriver.inst.i $(PREDIR)/GefaGedi.inst.i            \
	  $(PREDIR)/KpAnalytic.inst.i $(PREDIR)/KrAnalytic.inst.i                 \
	  $(PREDIR)/MatrixSolve.inst.i $(PREDIR)/MatterConduction.inst.i          \
	  $(PREDIR)/MatterDiagonal.inst.i $(PREDIR)/MatterWainwright.inst.i       \
	  $(PREDIR)/RadiationMemory.inst.i $(PREDIR)/RadiationSourceBC.inst.i     \
	  $(PREDIR)/RegionTable.inst.i $(PREDIR)/SetFaceTemperature.inst.i        \
	  $(PREDIR)/bound_free.inst.i $(PREDIR)/cblkbc.inst.i                     \
	  $(PREDIR)/cblkbc2.inst.i $(PREDIR)/cblkbc3.inst.i                       \
	  $(PREDIR)/diagonal.inst.i $(PREDIR)/diff1g.inst.i                       \
	  $(PREDIR)/divgrad2.inst.i $(PREDIR)/divgrad3.inst.i                     \
	  $(PREDIR)/divgradpert2d.inst.i $(PREDIR)/divgradpert3d.inst.i           \
	  $(PREDIR)/geteicouple.inst.i $(PREDIR)/gettfzstar.inst.i                \
	  $(PREDIR)/getzabar0.inst.i $(PREDIR)/gtkappabnd.inst.i                  \
	  $(PREDIR)/kapmlt.inst.i $(PREDIR)/newMatrix.inst.i                      \
	  $(PREDIR)/norml2.inst.i $(PREDIR)/opac2t.inst.i                         \
	  $(PREDIR)/opaclmt.inst.i $(PREDIR)/planck_opacity.inst.i                \
	  $(PREDIR)/radfree.inst.i $(PREDIR)/radinit.inst.i                       \
	  $(PREDIR)/rdiff.inst.i $(PREDIR)/rdiffbc.inst.i                         \
	  $(PREDIR)/rdiffbc2.inst.i $(PREDIR)/rdiffbc3.inst.i                     \
	  $(PREDIR)/rdiffset.inst.i $(PREDIR)/rdiffsrc.inst.i                     \
	  $(PREDIR)/reicouple.inst.i $(PREDIR)/retransfer.inst.i                  \
	  $(PREDIR)/rmatmult.inst.i $(PREDIR)/rmatmult2.inst.i                    \
	  $(PREDIR)/rmatmult3.inst.i $(PREDIR)/rsrcbc.inst.i                      \
	  $(PREDIR)/rsrcbc2.inst.i $(PREDIR)/rsrcbc3.inst.i                       \
	  $(PREDIR)/setpz1.inst.i $(PREDIR)/setpz2.inst.i                         \
	  $(PREDIR)/tblkinit.inst.i $(PREDIR)/tdiff.inst.i                        \
	  $(PREDIR)/teicouple.inst.i $(PREDIR)/zstarcal.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/ChemPotCalc.inst.i:ChemPotCalc.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f ChemPotCalc.i
	$$irs_pre ChemPotCalc.c >> ChemPotCalc.i
	@mv -f ChemPotCalc.i $(PREDIR)/ChemPotCalc.inst.i

$(PREDIR)/ConductionCoef.inst.i:ConductionCoef.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f ConductionCoef.i
	$$irs_pre ConductionCoef.c >> ConductionCoef.i
	@mv -f ConductionCoef.i $(PREDIR)/ConductionCoef.inst.i

$(PREDIR)/DiffCoef.inst.i:DiffCoef.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/irsdefs.h                      \
	  ../../includes/DiffusionData.hh ../../includes/FunctionTimer.h          \
	  ../../includes/RadiationData.h
	@rm -f DiffCoef.i
	$$irs_pre DiffCoef.c >> DiffCoef.i
	@mv -f DiffCoef.i $(PREDIR)/DiffCoef.inst.i

$(PREDIR)/DivgradDriver.inst.i:DivgradDriver.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f DivgradDriver.i
	$$irs_pre DivgradDriver.c >> DivgradDriver.i
	@mv -f DivgradDriver.i $(PREDIR)/DivgradDriver.inst.i

$(PREDIR)/FemDivgrad3.inst.i:FemDivgrad3.c ../../includes/irs.h                   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f FemDivgrad3.i
	$$irs_pre FemDivgrad3.c >> FemDivgrad3.i
	@mv -f FemDivgrad3.i $(PREDIR)/FemDivgrad3.inst.i

$(PREDIR)/FemGrad3d.inst.i:FemGrad3d.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h
	@rm -f FemGrad3d.i
	$$irs_pre FemGrad3d.c >> FemGrad3d.i
	@mv -f FemGrad3d.i $(PREDIR)/FemGrad3d.inst.i

$(PREDIR)/FluxLimiter2d.inst.i:FluxLimiter2d.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h
	@rm -f FluxLimiter2d.i
	$$irs_pre FluxLimiter2d.c >> FluxLimiter2d.i
	@mv -f FluxLimiter2d.i $(PREDIR)/FluxLimiter2d.inst.i

$(PREDIR)/FluxLimiter3d.inst.i:FluxLimiter3d.c ../../includes/irs.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f FluxLimiter3d.i
	$$irs_pre FluxLimiter3d.c >> FluxLimiter3d.i
	@mv -f FluxLimiter3d.i $(PREDIR)/FluxLimiter3d.inst.i

$(PREDIR)/FluxLimiterDriver.inst.i:FluxLimiterDriver.c ../../includes/irsdefs.h   \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h
	@rm -f FluxLimiterDriver.i
	$$irs_pre FluxLimiterDriver.c >> FluxLimiterDriver.i
	@mv -f FluxLimiterDriver.i $(PREDIR)/FluxLimiterDriver.inst.i

$(PREDIR)/GefaGedi.inst.i:GefaGedi.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h
	@rm -f GefaGedi.i
	$$irs_pre GefaGedi.c >> GefaGedi.i
	@mv -f GefaGedi.i $(PREDIR)/GefaGedi.inst.i

$(PREDIR)/KpAnalytic.inst.i:KpAnalytic.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irseos.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f KpAnalytic.i
	$$irs_pre KpAnalytic.c >> KpAnalytic.i
	@mv -f KpAnalytic.i $(PREDIR)/KpAnalytic.inst.i

$(PREDIR)/KrAnalytic.inst.i:KrAnalytic.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irseos.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f KrAnalytic.i
	$$irs_pre KrAnalytic.c >> KrAnalytic.i
	@mv -f KrAnalytic.i $(PREDIR)/KrAnalytic.inst.i

$(PREDIR)/MatrixSolve.inst.i:MatrixSolve.c ../../includes/irs.h                   \
	  ../../includes/irssys.h ../../includes/irscom.h                         \
	  ../../includes/irsdefs.h ../../includes/irstdiff.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/TimeStepControl.h         \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	@rm -f MatrixSolve.i
	$$irs_pre MatrixSolve.c >> MatrixSolve.i
	@mv -f MatrixSolve.i $(PREDIR)/MatrixSolve.inst.i

$(PREDIR)/MatterConduction.inst.i:MatterConduction.c ../../includes/irs.h         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f MatterConduction.i
	$$irs_pre MatterConduction.c >> MatterConduction.i
	@mv -f MatterConduction.i $(PREDIR)/MatterConduction.inst.i

$(PREDIR)/MatterDiagonal.inst.i:MatterDiagonal.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/irs.h                     \
	  ../../includes/irscom.h
	@rm -f MatterDiagonal.i
	$$irs_pre MatterDiagonal.c >> MatterDiagonal.i
	@mv -f MatterDiagonal.i $(PREDIR)/MatterDiagonal.inst.i

$(PREDIR)/MatterWainwright.inst.i:MatterWainwright.c ../../includes/irs.h         \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f MatterWainwright.i
	$$irs_pre MatterWainwright.c >> MatterWainwright.i
	@mv -f MatterWainwright.i $(PREDIR)/MatterWainwright.inst.i

$(PREDIR)/RadiationMemory.inst.i:RadiationMemory.c ../../includes/irsdefs.h       \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/DiffusionData.h ../../includes/ProblemArray.h            \
	  ../../includes/RadiationData.hh ../../includes/pardo.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	@rm -f RadiationMemory.i
	$$irs_pre RadiationMemory.c >> RadiationMemory.i
	@mv -f RadiationMemory.i $(PREDIR)/RadiationMemory.inst.i

$(PREDIR)/RadiationSourceBC.inst.i:RadiationSourceBC.c ../../includes/irs.h       \
	  ../../includes/irstdiff.h ../../includes/irsrgst.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/Rgst.h ../../includes/RadiationData.h                    \
	  ../../includes/Source.h
	@rm -f RadiationSourceBC.i
	$$irs_pre RadiationSourceBC.c >> RadiationSourceBC.i
	@mv -f RadiationSourceBC.i $(PREDIR)/RadiationSourceBC.inst.i

$(PREDIR)/RegionTable.inst.i:RegionTable.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h ../../includes/irs.h  \
	  ../../includes/Domain.h ../../includes/Region.h                         \
	  ../../includes/SpeciesFraction.h
	@rm -f RegionTable.i
	$$irs_pre RegionTable.c >> RegionTable.i
	@mv -f RegionTable.i $(PREDIR)/RegionTable.inst.i

$(PREDIR)/SetFaceTemperature.inst.i:SetFaceTemperature.c ../../includes/irs.h     \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f SetFaceTemperature.i
	$$irs_pre SetFaceTemperature.c >> SetFaceTemperature.i
	@mv -f SetFaceTemperature.i $(PREDIR)/SetFaceTemperature.inst.i

$(PREDIR)/bound_free.inst.i:bound_free.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f bound_free.i
	$$irs_pre bound_free.c >> bound_free.i
	@mv -f bound_free.i $(PREDIR)/bound_free.inst.i

$(PREDIR)/cblkbc.inst.i:cblkbc.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/RadiationData.h
	@rm -f cblkbc.i
	$$irs_pre cblkbc.c >> cblkbc.i
	@mv -f cblkbc.i $(PREDIR)/cblkbc.inst.i

$(PREDIR)/cblkbc2.inst.i:cblkbc2.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/RadiationData.h
	@rm -f cblkbc2.i
	$$irs_pre cblkbc2.c >> cblkbc2.i
	@mv -f cblkbc2.i $(PREDIR)/cblkbc2.inst.i

$(PREDIR)/cblkbc3.inst.i:cblkbc3.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/RadiationData.h
	@rm -f cblkbc3.i
	$$irs_pre cblkbc3.c >> cblkbc3.i
	@mv -f cblkbc3.i $(PREDIR)/cblkbc3.inst.i

$(PREDIR)/diagonal.inst.i:diagonal.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f diagonal.i
	$$irs_pre diagonal.c >> diagonal.i
	@mv -f diagonal.i $(PREDIR)/diagonal.inst.i

$(PREDIR)/diff1g.inst.i:diff1g.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f diff1g.i
	$$irs_pre diff1g.c >> diff1g.i
	@mv -f diff1g.i $(PREDIR)/diff1g.inst.i

$(PREDIR)/divgrad2.inst.i:divgrad2.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgrad2.i
	$$irs_pre divgrad2.c >> divgrad2.i
	@mv -f divgrad2.i $(PREDIR)/divgrad2.inst.i

$(PREDIR)/divgrad3.inst.i:divgrad3.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgrad3.i
	$$irs_pre divgrad3.c >> divgrad3.i
	@mv -f divgrad3.i $(PREDIR)/divgrad3.inst.i

$(PREDIR)/divgradpert2d.inst.i:divgradpert2d.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgradpert2d.i
	$$irs_pre divgradpert2d.c >> divgradpert2d.i
	@mv -f divgradpert2d.i $(PREDIR)/divgradpert2d.inst.i

$(PREDIR)/divgradpert3d.inst.i:divgradpert3d.c ../../includes/irs.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f divgradpert3d.i
	$$irs_pre divgradpert3d.c >> divgradpert3d.i
	@mv -f divgradpert3d.i $(PREDIR)/divgradpert3d.inst.i

$(PREDIR)/geteicouple.inst.i:geteicouple.c ../../includes/irsdefs.h               \
	  ../../includes/irs.h ../../includes/irsreg.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f geteicouple.i
	$$irs_pre geteicouple.c >> geteicouple.i
	@mv -f geteicouple.i $(PREDIR)/geteicouple.inst.i

$(PREDIR)/gettfzstar.inst.i:gettfzstar.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f gettfzstar.i
	$$irs_pre gettfzstar.c >> gettfzstar.i
	@mv -f gettfzstar.i $(PREDIR)/gettfzstar.inst.i

$(PREDIR)/getzabar0.inst.i:getzabar0.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f getzabar0.i
	$$irs_pre getzabar0.c >> getzabar0.i
	@mv -f getzabar0.i $(PREDIR)/getzabar0.inst.i

$(PREDIR)/gtkappabnd.inst.i:gtkappabnd.c ../../includes/irs.h                     \
	  ../../includes/irscom.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h
	@rm -f gtkappabnd.i
	$$irs_pre gtkappabnd.c >> gtkappabnd.i
	@mv -f gtkappabnd.i $(PREDIR)/gtkappabnd.inst.i

$(PREDIR)/kapmlt.inst.i:kapmlt.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h
	@rm -f kapmlt.i
	$$irs_pre kapmlt.c >> kapmlt.i
	@mv -f kapmlt.i $(PREDIR)/kapmlt.inst.i

$(PREDIR)/newMatrix.inst.i:newMatrix.c ../../includes/irsdefs.h                   \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irs.h     \
	  ../../includes/RadiationData.h ../../includes/irs.h
	@rm -f newMatrix.i
	$$irs_pre newMatrix.c >> newMatrix.i
	@mv -f newMatrix.i $(PREDIR)/newMatrix.inst.i

$(PREDIR)/norml2.inst.i:norml2.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f norml2.i
	$$irs_pre norml2.c >> norml2.i
	@mv -f norml2.i $(PREDIR)/norml2.inst.i

$(PREDIR)/opac2t.inst.i:opac2t.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f opac2t.i
	$$irs_pre opac2t.c >> opac2t.i
	@mv -f opac2t.i $(PREDIR)/opac2t.inst.i

$(PREDIR)/opaclmt.inst.i:opaclmt.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/FunctionTimer.h
	@rm -f opaclmt.i
	$$irs_pre opaclmt.c >> opaclmt.i
	@mv -f opaclmt.i $(PREDIR)/opaclmt.inst.i

$(PREDIR)/planck_opacity.inst.i:planck_opacity.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f planck_opacity.i
	$$irs_pre planck_opacity.c >> planck_opacity.i
	@mv -f planck_opacity.i $(PREDIR)/planck_opacity.inst.i

$(PREDIR)/radfree.inst.i:radfree.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/ProblemArray.h ../../includes/DiffusionData.h            \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f radfree.i
	$$irs_pre radfree.c >> radfree.i
	@mv -f radfree.i $(PREDIR)/radfree.inst.i

$(PREDIR)/radinit.inst.i:radinit.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/DiffusionData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h
	@rm -f radinit.i
	$$irs_pre radinit.c >> radinit.i
	@mv -f radinit.i $(PREDIR)/radinit.inst.i

$(PREDIR)/rdiff.inst.i:rdiff.c ../../includes/irs.h ../../includes/irscom.h       \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/Source.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f rdiff.i
	$$irs_pre rdiff.c >> rdiff.i
	@mv -f rdiff.i $(PREDIR)/rdiff.inst.i

$(PREDIR)/rdiffbc.inst.i:rdiffbc.c ../../includes/irs.h ../../includes/irscom.h   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc.i
	$$irs_pre rdiffbc.c >> rdiffbc.i
	@mv -f rdiffbc.i $(PREDIR)/rdiffbc.inst.i

$(PREDIR)/rdiffbc2.inst.i:rdiffbc2.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc2.i
	$$irs_pre rdiffbc2.c >> rdiffbc2.i
	@mv -f rdiffbc2.i $(PREDIR)/rdiffbc2.inst.i

$(PREDIR)/rdiffbc3.inst.i:rdiffbc3.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc3.i
	$$irs_pre rdiffbc3.c >> rdiffbc3.i
	@mv -f rdiffbc3.i $(PREDIR)/rdiffbc3.inst.i

$(PREDIR)/rdiffset.inst.i:rdiffset.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f rdiffset.i
	$$irs_pre rdiffset.c >> rdiffset.i
	@mv -f rdiffset.i $(PREDIR)/rdiffset.inst.i

$(PREDIR)/rdiffsrc.inst.i:rdiffsrc.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffsrc.i
	$$irs_pre rdiffsrc.c >> rdiffsrc.i
	@mv -f rdiffsrc.i $(PREDIR)/rdiffsrc.inst.i

$(PREDIR)/reicouple.inst.i:reicouple.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f reicouple.i
	$$irs_pre reicouple.c >> reicouple.i
	@mv -f reicouple.i $(PREDIR)/reicouple.inst.i

$(PREDIR)/retransfer.inst.i:retransfer.c ../../includes/irs.h                     \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/DiffusionData.h
	@rm -f retransfer.i
	$$irs_pre retransfer.c >> retransfer.i
	@mv -f retransfer.i $(PREDIR)/retransfer.inst.i

$(PREDIR)/rmatmult.inst.i:rmatmult.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rmatmult.i
	$$irs_pre rmatmult.c >> rmatmult.i
	@mv -f rmatmult.i $(PREDIR)/rmatmult.inst.i

$(PREDIR)/rmatmult2.inst.i:rmatmult2.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rmatmult2.i
	$$irs_pre rmatmult2.c >> rmatmult2.i
	@mv -f rmatmult2.i $(PREDIR)/rmatmult2.inst.i

$(PREDIR)/rmatmult3.inst.i:rmatmult3.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f rmatmult3.i
	$$irs_pre rmatmult3.c >> rmatmult3.i
	@mv -f rmatmult3.i $(PREDIR)/rmatmult3.inst.i

$(PREDIR)/rsrcbc.inst.i:rsrcbc.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rsrcbc.i
	$$irs_pre rsrcbc.c >> rsrcbc.i
	@mv -f rsrcbc.i $(PREDIR)/rsrcbc.inst.i

$(PREDIR)/rsrcbc2.inst.i:rsrcbc2.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/RadiationData.h
	@rm -f rsrcbc2.i
	$$irs_pre rsrcbc2.c >> rsrcbc2.i
	@mv -f rsrcbc2.i $(PREDIR)/rsrcbc2.inst.i

$(PREDIR)/rsrcbc3.inst.i:rsrcbc3.c ../../includes/irs.h ../../includes/irssrc.h   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rsrcbc3.i
	$$irs_pre rsrcbc3.c >> rsrcbc3.i
	@mv -f rsrcbc3.i $(PREDIR)/rsrcbc3.inst.i

$(PREDIR)/setpz1.inst.i:setpz1.c ../../includes/irs.h ../../includes/irstdiff.h
	@rm -f setpz1.i
	$$irs_pre setpz1.c >> setpz1.i
	@mv -f setpz1.i $(PREDIR)/setpz1.inst.i

$(PREDIR)/setpz2.inst.i:setpz2.c ../../includes/irs.h ../../includes/irstdiff.h
	@rm -f setpz2.i
	$$irs_pre setpz2.c >> setpz2.i
	@mv -f setpz2.i $(PREDIR)/setpz2.inst.i

$(PREDIR)/tblkinit.inst.i:tblkinit.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f tblkinit.i
	$$irs_pre tblkinit.c >> tblkinit.i
	@mv -f tblkinit.i $(PREDIR)/tblkinit.inst.i

$(PREDIR)/tdiff.inst.i:tdiff.c ../../includes/irs.h ../../includes/irsgen.h       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/SpeciesFraction.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f tdiff.i
	$$irs_pre tdiff.c >> tdiff.i
	@mv -f tdiff.i $(PREDIR)/tdiff.inst.i

$(PREDIR)/teicouple.inst.i:teicouple.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f teicouple.i
	$$irs_pre teicouple.c >> teicouple.i
	@mv -f teicouple.i $(PREDIR)/teicouple.inst.i

$(PREDIR)/zstarcal.inst.i:zstarcal.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f zstarcal.i
	$$irs_pre zstarcal.c >> zstarcal.i
	@mv -f zstarcal.i $(PREDIR)/zstarcal.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libtdiff_inst

libtdiff_inst:$(BI)(ChemPotCalc.inst.o) $(BI)(ConductionCoef.inst.o)              \
	  $(BI)(DiffCoef.inst.o) $(BI)(DivgradDriver.inst.o)                      \
	  $(BI)(FemDivgrad3.inst.o) $(BI)(FemGrad3d.inst.o)                       \
	  $(BI)(FluxLimiter2d.inst.o) $(BI)(FluxLimiter3d.inst.o)                 \
	  $(BI)(FluxLimiterDriver.inst.o) $(BI)(GefaGedi.inst.o)                  \
	  $(BI)(KpAnalytic.inst.o) $(BI)(KrAnalytic.inst.o)                       \
	  $(BI)(MatrixSolve.inst.o) $(BI)(MatterConduction.inst.o)                \
	  $(BI)(MatterDiagonal.inst.o) $(BI)(MatterWainwright.inst.o)             \
	  $(BI)(RadiationMemory.inst.o) $(BI)(RadiationSourceBC.inst.o)           \
	  $(BI)(RegionTable.inst.o) $(BI)(SetFaceTemperature.inst.o)              \
	  $(BI)(bound_free.inst.o) $(BI)(cblkbc.inst.o) $(BI)(cblkbc2.inst.o)     \
	  $(BI)(cblkbc3.inst.o) $(BI)(diagonal.inst.o) $(BI)(diff1g.inst.o)       \
	  $(BI)(divgrad2.inst.o) $(BI)(divgrad3.inst.o)                           \
	  $(BI)(divgradpert2d.inst.o) $(BI)(divgradpert3d.inst.o)                 \
	  $(BI)(geteicouple.inst.o) $(BI)(gettfzstar.inst.o)                      \
	  $(BI)(getzabar0.inst.o) $(BI)(gtkappabnd.inst.o) $(BI)(kapmlt.inst.o)   \
	  $(BI)(newMatrix.inst.o) $(BI)(norml2.inst.o) $(BI)(opac2t.inst.o)       \
	  $(BI)(opaclmt.inst.o) $(BI)(planck_opacity.inst.o)                      \
	  $(BI)(radfree.inst.o) $(BI)(radinit.inst.o) $(BI)(rdiff.inst.o)         \
	  $(BI)(rdiffbc.inst.o) $(BI)(rdiffbc2.inst.o) $(BI)(rdiffbc3.inst.o)     \
	  $(BI)(rdiffset.inst.o) $(BI)(rdiffsrc.inst.o) $(BI)(reicouple.inst.o)   \
	  $(BI)(retransfer.inst.o) $(BI)(rmatmult.inst.o) $(BI)(rmatmult2.inst.o) \
	  $(BI)(rmatmult3.inst.o) $(BI)(rsrcbc.inst.o) $(BI)(rsrcbc2.inst.o)      \
	  $(BI)(rsrcbc3.inst.o) $(BI)(setpz1.inst.o) $(BI)(setpz2.inst.o)         \
	  $(BI)(tblkinit.inst.o) $(BI)(tdiff.inst.o) $(BI)(teicouple.inst.o)      \
	  $(BI)(zstarcal.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libtdiff_inst.a $(B); \
		ln -sf libtdiff_inst.a $(B)); \
	  fi
	  @echo 'libtdiff_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(ChemPotCalc.inst.o):$(INSTDIR)/ChemPotCalc.inst.i
	$$irs_post $(INSTDIR)/ChemPotCalc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ChemPotCalc.inst.i $(DB)/ChemPotCalc.c 

$(BI)(ConductionCoef.inst.o):$(INSTDIR)/ConductionCoef.inst.i
	$$irs_post $(INSTDIR)/ConductionCoef.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ConductionCoef.inst.i $(DB)/ConductionCoef.c 

$(BI)(DiffCoef.inst.o):$(INSTDIR)/DiffCoef.inst.i
	$$irs_post $(INSTDIR)/DiffCoef.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DiffCoef.inst.i $(DB)/DiffCoef.c 

$(BI)(DivgradDriver.inst.o):$(INSTDIR)/DivgradDriver.inst.i
	$$irs_post $(INSTDIR)/DivgradDriver.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DivgradDriver.inst.i $(DB)/DivgradDriver.c 

$(BI)(FemDivgrad3.inst.o):$(INSTDIR)/FemDivgrad3.inst.i
	$$irs_post $(INSTDIR)/FemDivgrad3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FemDivgrad3.inst.i $(DB)/FemDivgrad3.c 

$(BI)(FemGrad3d.inst.o):$(INSTDIR)/FemGrad3d.inst.i
	$$irs_post $(INSTDIR)/FemGrad3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FemGrad3d.inst.i $(DB)/FemGrad3d.c 

$(BI)(FluxLimiter2d.inst.o):$(INSTDIR)/FluxLimiter2d.inst.i
	$$irs_post $(INSTDIR)/FluxLimiter2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiter2d.inst.i $(DB)/FluxLimiter2d.c 

$(BI)(FluxLimiter3d.inst.o):$(INSTDIR)/FluxLimiter3d.inst.i
	$$irs_post $(INSTDIR)/FluxLimiter3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiter3d.inst.i $(DB)/FluxLimiter3d.c 

$(BI)(FluxLimiterDriver.inst.o):$(INSTDIR)/FluxLimiterDriver.inst.i
	$$irs_post $(INSTDIR)/FluxLimiterDriver.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiterDriver.inst.i $(DB)/FluxLimiterDriver.c 

$(BI)(GefaGedi.inst.o):$(INSTDIR)/GefaGedi.inst.i
	$$irs_post $(INSTDIR)/GefaGedi.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/GefaGedi.inst.i $(DB)/GefaGedi.c 

$(BI)(KpAnalytic.inst.o):$(INSTDIR)/KpAnalytic.inst.i
	$$irs_post $(INSTDIR)/KpAnalytic.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/KpAnalytic.inst.i $(DB)/KpAnalytic.c 

$(BI)(KrAnalytic.inst.o):$(INSTDIR)/KrAnalytic.inst.i
	$$irs_post $(INSTDIR)/KrAnalytic.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/KrAnalytic.inst.i $(DB)/KrAnalytic.c 

$(BI)(MatrixSolve.inst.o):$(INSTDIR)/MatrixSolve.inst.i
	$$irs_post $(INSTDIR)/MatrixSolve.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatrixSolve.inst.i $(DB)/MatrixSolve.c 

$(BI)(MatterConduction.inst.o):$(INSTDIR)/MatterConduction.inst.i
	$$irs_post $(INSTDIR)/MatterConduction.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterConduction.inst.i $(DB)/MatterConduction.c 

$(BI)(MatterDiagonal.inst.o):$(INSTDIR)/MatterDiagonal.inst.i
	$$irs_post $(INSTDIR)/MatterDiagonal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterDiagonal.inst.i $(DB)/MatterDiagonal.c 

$(BI)(MatterWainwright.inst.o):$(INSTDIR)/MatterWainwright.inst.i
	$$irs_post $(INSTDIR)/MatterWainwright.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterWainwright.inst.i $(DB)/MatterWainwright.c 

$(BI)(RadiationMemory.inst.o):$(INSTDIR)/RadiationMemory.inst.i
	$$irs_post $(INSTDIR)/RadiationMemory.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RadiationMemory.inst.i $(DB)/RadiationMemory.c 

$(BI)(RadiationSourceBC.inst.o):$(INSTDIR)/RadiationSourceBC.inst.i
	$$irs_post $(INSTDIR)/RadiationSourceBC.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RadiationSourceBC.inst.i $(DB)/RadiationSourceBC.c 

$(BI)(RegionTable.inst.o):$(INSTDIR)/RegionTable.inst.i
	$$irs_post $(INSTDIR)/RegionTable.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RegionTable.inst.i $(DB)/RegionTable.c 

$(BI)(SetFaceTemperature.inst.o):$(INSTDIR)/SetFaceTemperature.inst.i
	$$irs_post $(INSTDIR)/SetFaceTemperature.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/SetFaceTemperature.inst.i $(DB)/SetFaceTemperature.c 

$(BI)(bound_free.inst.o):$(INSTDIR)/bound_free.inst.i
	$$irs_post $(INSTDIR)/bound_free.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bound_free.inst.i $(DB)/bound_free.c 

$(BI)(cblkbc.inst.o):$(INSTDIR)/cblkbc.inst.i
	$$irs_post $(INSTDIR)/cblkbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc.inst.i $(DB)/cblkbc.c 

$(BI)(cblkbc2.inst.o):$(INSTDIR)/cblkbc2.inst.i
	$$irs_post $(INSTDIR)/cblkbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc2.inst.i $(DB)/cblkbc2.c 

$(BI)(cblkbc3.inst.o):$(INSTDIR)/cblkbc3.inst.i
	$$irs_post $(INSTDIR)/cblkbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc3.inst.i $(DB)/cblkbc3.c 

$(BI)(diagonal.inst.o):$(INSTDIR)/diagonal.inst.i
	$$irs_post $(INSTDIR)/diagonal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/diagonal.inst.i $(DB)/diagonal.c 

$(BI)(diff1g.inst.o):$(INSTDIR)/diff1g.inst.i
	$$irs_post $(INSTDIR)/diff1g.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/diff1g.inst.i $(DB)/diff1g.c 

$(BI)(divgrad2.inst.o):$(INSTDIR)/divgrad2.inst.i
	$$irs_post $(INSTDIR)/divgrad2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgrad2.inst.i $(DB)/divgrad2.c 

$(BI)(divgrad3.inst.o):$(INSTDIR)/divgrad3.inst.i
	$$irs_post $(INSTDIR)/divgrad3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgrad3.inst.i $(DB)/divgrad3.c 

$(BI)(divgradpert2d.inst.o):$(INSTDIR)/divgradpert2d.inst.i
	$$irs_post $(INSTDIR)/divgradpert2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgradpert2d.inst.i $(DB)/divgradpert2d.c 

$(BI)(divgradpert3d.inst.o):$(INSTDIR)/divgradpert3d.inst.i
	$$irs_post $(INSTDIR)/divgradpert3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgradpert3d.inst.i $(DB)/divgradpert3d.c 

$(BI)(geteicouple.inst.o):$(INSTDIR)/geteicouple.inst.i
	$$irs_post $(INSTDIR)/geteicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geteicouple.inst.i $(DB)/geteicouple.c 

$(BI)(gettfzstar.inst.o):$(INSTDIR)/gettfzstar.inst.i
	$$irs_post $(INSTDIR)/gettfzstar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gettfzstar.inst.i $(DB)/gettfzstar.c 

$(BI)(getzabar0.inst.o):$(INSTDIR)/getzabar0.inst.i
	$$irs_post $(INSTDIR)/getzabar0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getzabar0.inst.i $(DB)/getzabar0.c 

$(BI)(gtkappabnd.inst.o):$(INSTDIR)/gtkappabnd.inst.i
	$$irs_post $(INSTDIR)/gtkappabnd.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gtkappabnd.inst.i $(DB)/gtkappabnd.c 

$(BI)(kapmlt.inst.o):$(INSTDIR)/kapmlt.inst.i
	$$irs_post $(INSTDIR)/kapmlt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/kapmlt.inst.i $(DB)/kapmlt.c 

$(BI)(newMatrix.inst.o):$(INSTDIR)/newMatrix.inst.i
	$$irs_post $(INSTDIR)/newMatrix.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/newMatrix.inst.i $(DB)/newMatrix.c 

$(BI)(norml2.inst.o):$(INSTDIR)/norml2.inst.i
	$$irs_post $(INSTDIR)/norml2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/norml2.inst.i $(DB)/norml2.c 

$(BI)(opac2t.inst.o):$(INSTDIR)/opac2t.inst.i
	$$irs_post $(INSTDIR)/opac2t.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/opac2t.inst.i $(DB)/opac2t.c 

$(BI)(opaclmt.inst.o):$(INSTDIR)/opaclmt.inst.i
	$$irs_post $(INSTDIR)/opaclmt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/opaclmt.inst.i $(DB)/opaclmt.c 

$(BI)(planck_opacity.inst.o):$(INSTDIR)/planck_opacity.inst.i
	$$irs_post $(INSTDIR)/planck_opacity.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/planck_opacity.inst.i $(DB)/planck_opacity.c 

$(BI)(radfree.inst.o):$(INSTDIR)/radfree.inst.i
	$$irs_post $(INSTDIR)/radfree.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/radfree.inst.i $(DB)/radfree.c 

$(BI)(radinit.inst.o):$(INSTDIR)/radinit.inst.i
	$$irs_post $(INSTDIR)/radinit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/radinit.inst.i $(DB)/radinit.c 

$(BI)(rdiff.inst.o):$(INSTDIR)/rdiff.inst.i
	$$irs_post $(INSTDIR)/rdiff.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiff.inst.i $(DB)/rdiff.c 

$(BI)(rdiffbc.inst.o):$(INSTDIR)/rdiffbc.inst.i
	$$irs_post $(INSTDIR)/rdiffbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc.inst.i $(DB)/rdiffbc.c 

$(BI)(rdiffbc2.inst.o):$(INSTDIR)/rdiffbc2.inst.i
	$$irs_post $(INSTDIR)/rdiffbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc2.inst.i $(DB)/rdiffbc2.c 

$(BI)(rdiffbc3.inst.o):$(INSTDIR)/rdiffbc3.inst.i
	$$irs_post $(INSTDIR)/rdiffbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc3.inst.i $(DB)/rdiffbc3.c 

$(BI)(rdiffset.inst.o):$(INSTDIR)/rdiffset.inst.i
	$$irs_post $(INSTDIR)/rdiffset.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffset.inst.i $(DB)/rdiffset.c 

$(BI)(rdiffsrc.inst.o):$(INSTDIR)/rdiffsrc.inst.i
	$$irs_post $(INSTDIR)/rdiffsrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffsrc.inst.i $(DB)/rdiffsrc.c 

$(BI)(reicouple.inst.o):$(INSTDIR)/reicouple.inst.i
	$$irs_post $(INSTDIR)/reicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/reicouple.inst.i $(DB)/reicouple.c 

$(BI)(retransfer.inst.o):$(INSTDIR)/retransfer.inst.i
	$$irs_post $(INSTDIR)/retransfer.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/retransfer.inst.i $(DB)/retransfer.c 

$(BI)(rmatmult.inst.o):$(INSTDIR)/rmatmult.inst.i
	$$irs_post $(INSTDIR)/rmatmult.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult.inst.i $(DB)/rmatmult.c 

$(BI)(rmatmult2.inst.o):$(INSTDIR)/rmatmult2.inst.i
	$$irs_post $(INSTDIR)/rmatmult2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult2.inst.i $(DB)/rmatmult2.c 

$(BI)(rmatmult3.inst.o):$(INSTDIR)/rmatmult3.inst.i
	$$irs_post $(INSTDIR)/rmatmult3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult3.inst.i $(DB)/rmatmult3.c 

$(BI)(rsrcbc.inst.o):$(INSTDIR)/rsrcbc.inst.i
	$$irs_post $(INSTDIR)/rsrcbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc.inst.i $(DB)/rsrcbc.c 

$(BI)(rsrcbc2.inst.o):$(INSTDIR)/rsrcbc2.inst.i
	$$irs_post $(INSTDIR)/rsrcbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc2.inst.i $(DB)/rsrcbc2.c 

$(BI)(rsrcbc3.inst.o):$(INSTDIR)/rsrcbc3.inst.i
	$$irs_post $(INSTDIR)/rsrcbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc3.inst.i $(DB)/rsrcbc3.c 

$(BI)(setpz1.inst.o):$(INSTDIR)/setpz1.inst.i
	$$irs_post $(INSTDIR)/setpz1.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setpz1.inst.i $(DB)/setpz1.c 

$(BI)(setpz2.inst.o):$(INSTDIR)/setpz2.inst.i
	$$irs_post $(INSTDIR)/setpz2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setpz2.inst.i $(DB)/setpz2.c 

$(BI)(tblkinit.inst.o):$(INSTDIR)/tblkinit.inst.i
	$$irs_post $(INSTDIR)/tblkinit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tblkinit.inst.i $(DB)/tblkinit.c 

$(BI)(tdiff.inst.o):$(INSTDIR)/tdiff.inst.i
	$$irs_post $(INSTDIR)/tdiff.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tdiff.inst.i $(DB)/tdiff.c 

$(BI)(teicouple.inst.o):$(INSTDIR)/teicouple.inst.i
	$$irs_post $(INSTDIR)/teicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/teicouple.inst.i $(DB)/teicouple.c 

$(BI)(zstarcal.inst.o):$(INSTDIR)/zstarcal.inst.i
	$$irs_post $(INSTDIR)/zstarcal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/zstarcal.inst.i $(DB)/zstarcal.c 

DEP_SRCS = \
	ChemPotCalc.c ConductionCoef.c DiffCoef.c DivgradDriver.c FemDivgrad3.c  \
	FemGrad3d.c FluxLimiter2d.c FluxLimiter3d.c FluxLimiterDriver.c GefaGedi.c  \
	KpAnalytic.c KrAnalytic.c MatrixSolve.c MatterConduction.c MatterDiagonal.c  \
	MatterWainwright.c RadiationMemory.c RadiationSourceBC.c RegionTable.c  \
	SetFaceTemperature.c bound_free.c cblkbc.c cblkbc2.c cblkbc3.c diagonal.c  \
	diff1g.c divgrad2.c divgrad3.c divgradpert2d.c divgradpert3d.c geteicouple.c  \
	gettfzstar.c getzabar0.c gtkappabnd.c kapmlt.c newMatrix.c norml2.c opac2t.c  \
	opaclmt.c planck_opacity.c radfree.c radinit.c rdiff.c rdiffbc.c rdiffbc2.c  \
	rdiffbc3.c rdiffset.c rdiffsrc.c reicouple.c retransfer.c rmatmult.c rmatmult2.c  \
	rmatmult3.c rsrcbc.c rsrcbc2.c rsrcbc3.c setpz1.c setpz2.c tblkinit.c  \
	tdiff.c teicouple.c zstarcal.c  

depend:
	@cp -f Makefile.tdiff Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

