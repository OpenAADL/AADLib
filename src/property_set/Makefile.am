# Retrieve all source files

AADL_SOURCES = ${shell find $(srcdir) -name '*.aadl'}

EXTRA_DIST= $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/property_set $${FILE};\
	done

clean-local:
	-rm *~
