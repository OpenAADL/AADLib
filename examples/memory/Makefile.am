AADL_SOURCES = $(srcdir)/prodcons.aadl
AADL_ROOT    = vxworks.impl

OTHER_FILES =							\
	$(srcdir)/arinc653_extended.aadl			\
	$(srcdir)/memory_segment_properties.aadl		\
	$(srcdir)/prodcons.aadl					\
	$(srcdir)/producer_consummer_software.aadl		\
	$(srcdir)/vxworks_platform.aadl				\
	$(srcdir)/mem3.real					\
	$(srcdir)/soft.real					\
	$(srcdir)/vxworks.real				

CLEANDIRS = vxworks_impl

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real  #build_c

# Note: we overwrite the "real" target to match this project specific
# constraints.

real:
	-$(OCARINA) $(OCARINA_FLAGS) -g real_theorem \
		-real_lib $(srcdir)/mem3.real \
		-real_lib $(srcdir)/soft.real \
		-real_lib $(srcdir)/vxworks.real \
		-r $(AADL_ROOT) \
		$(AADL_SOURCES)
