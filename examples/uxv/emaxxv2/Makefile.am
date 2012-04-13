AADL_SOURCES = $(srcdir)/emaxxv2_system.aadl
AADL_ROOT    = 

AADL_LIB = -I$(srcdir)/../common

include $(srcdir)/../../Makefile.common

AVAILABLE_TARGETS= parse-aadl 

OTHER_FILES = $(srcdir)/emaxxv2_sw.aadl

real2:
	$(OCARINA) $(OCARINA_FLAGS) -g real_theorem \
		-real_lib $(srcdir)/../lib.real \
		$(AADL_SOURCES)
