# Retrieve all source files

AADL_SOURCES = ${shell find $(srcdir) -name '*.aadl'}

EXTRA_DIST= $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/property_set $${FILE};\
	done

install-data-local:
	mkdir -p $(DESTDIR)$(datadir)/ocarina/AADLv2
	for file in $(AADL_SOURCES); do \
	 $(INSTALL_DATA) $$file $(DESTDIR)$(datadir)/ocarina/AADLv2 || exit 1; \
	done

uninstall-local:
	for file in $(AADL_SOURCES); do \
	rm -rf $(DESTDIR)$(datadir)/ocarina/AADLv2/$$file; \
	done


clean-local:
	-rm *~
