# Retrieve all source files

AADL_SOURCES = ${shell find $(srcdir) -name '*.aadl'}

debug:
	@echo $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/aadl -I$(top_srcdir)/src/property_set $${FILE};\
	done

clean-local:
	-rm *~

install-data-local:
	for file in $(AADL_SOURCES); do \
	 $(INSTALL_DATA) $$file $(DESTDIR)$(datadir)/ocarina/AADLv2 || exit 1; \
	done

EXTRA_DIST= $(AADL_SOURCES)
