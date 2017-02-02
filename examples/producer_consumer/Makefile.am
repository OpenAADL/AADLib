AADL_SOURCES = $(srcdir)/producer_consumer.aadl
AADL_ROOT    = pc_simple.native

OTHER_FILES = $(srcdir)/producer_consumer.adb	\
	  $(srcdir)/producer_consumer.ads

CLEANDIRS = pc_simple_native

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real petri build_ada lnt

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
