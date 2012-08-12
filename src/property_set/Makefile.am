# Retrieve all source files

BRUTE_AADL=${shell find . $(srcdir) -name '*.aadl' | grep -v 'b~' 2> /dev/null}
AADL_SOURCES = ${sort $(srcdir) $(BRUTE_AADL)}

EXTRA_DIST= $(AADL_SOURCES)

check-local:
	for FILE in ${AADL_SOURCES}; do \
		ocarina -y -aadlv2 -I$(top_srcdir)/src/property_set $${FILE};\
	done

clean-local:
	-rm *~
