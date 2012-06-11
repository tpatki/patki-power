include make.defs

ifeq ($(STATIC_LINK),on)
SUBDIRS = CMG_CLEAN cmg2Kull Teton
else
SUBDIRS = CMG_CLEAN cmg2Kull Teton python
endif

.PHONY: subdirs $(SUBDIRS) clean

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

# specify compile order dependency
cmg2Kull: CMG_CLEAN
Teton : cmg2Kull
python : Teton

clean:
	@for i in ${SUBDIRS} ; do (cd $$i; $(MAKE) clean); done

veryclean:
	@for i in ${SUBDIRS} ; do (cd $$i; $(MAKE) veryclean); done
