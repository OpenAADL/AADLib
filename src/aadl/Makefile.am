# Retrieve all source files

AADL_SOURCES = ${shell find $(srcdir) -name '*.aadl'}

OCARINA_FLAGS=-I$(top_srcdir)/src/aadl -I$(top_srcdir)/src/aadl/buses	\
-I$(top_srcdir)/src/aadl/devices -I$(top_srcdir)/src/aadl/drivers	\
-I$(top_srcdir)/src/aadl/drivers/uart					\
-I$(top_srcdir)/src/property_set

debug:
	@echo $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 $(OCARINA_FLAGS) $${FILE};\
	done

clean-local:
	-rm *~

install-data-local:
	$(INSTALL) -d $(DESTDIR)$(datadir)/ocarina/AADLv2
	for file in $(AADL_SOURCES); do \
	 $(INSTALL_DATA) $$file $(DESTDIR)$(datadir)/ocarina/AADLv2 || exit 1; \
	done

uninstall-local:
	for file in $(AADL_SOURCES); do \
	rm -rf  $(DESTDIR)$(datadir)/ocarina/AADLv2/$$file ; \
	done

EXTRA_DIST= $(AADL_SOURCES)
