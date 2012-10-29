AADL_SOURCES = $(srcdir)/producer_consumer.aadl
AADL_ROOT    = pc_simple.native

OTHER_FILES =
CLEANDIRS =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real petri #build_ada

# Note: we overwrite the "real" target to match this project specific
# constraints.

real:
	-$(OCARINA) $(OCARINA_FLAGS) -g real_theorem \
		-real_lib $(srcdir)/lib.real \
		-r $(AADL_ROOT) \
		$(AADL_SOURCES)

dump:
	-$(OCARINA) $(OCARINA_FLAGS) -i \
		-d  \
		-r $(AADL_ROOT) \
		$(AADL_SOURCES)
