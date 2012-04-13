AADL_SOURCES = $(srcdir)/asl.aadl
AADL_ROOT    = a_system.impl

OTHER_FILES = $(srcdir)/constraints.real

CLEANDIRS =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real

# Note: we overwrite the "real" target to match this project specific
# constraints.

real:
	-$(OCARINA) $(OCARINA_FLAGS) -g real_theorem \
		-real_lib $(srcdir)/constraints.real \
		-r $(AADL_ROOT) \
		$(AADL_SOURCES)
