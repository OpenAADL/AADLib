AADL_SOURCES = $(srcdir)/perseus.aadl
AADL_ROOT    = perseus_rocket.impl1

OTHER_FILES = $(srcdir)/lib.real

CLEANDIRS =
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real

real:
	ocarina -y -g real_theorem -aadlv2 -I$(top_srcdir)/src/property_set -real_lib $(srcdir)/lib.real -real_theorem check_perseus -r $(AADL_ROOT) $(AADL_SOURCES)
