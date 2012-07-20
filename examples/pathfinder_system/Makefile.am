AADL_SOURCES = $(srcdir)/mars_pathfinder.aadl

AADL_ROOT    = sys_mars_pathfinder.impl

OTHER_FILES = $(srcdir)/pathfinder_hardware.aadl	\
	$(srcdir)/pathfinder_software.aadl

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real

pouet:
	ocarina -y -g real_theorem -aadlv2 -real_lib $(top_srcdir)/src/real/test.real -real_theorem per_thread -r $(AADL_ROOT) $(AADL_SOURCES)
