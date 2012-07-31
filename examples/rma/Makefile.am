AADL_SOURCES = $(srcdir)/rma.aadl
AADL_ROOT    = rma.impl

OTHER_FILES =					\
	$(srcdir)/hello.c

CLEANDIRS = rma_impl
CLEANFILES = rma_impl_aadl_xml.xml

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real cheddar mast aadl_xml build_ada build_c

pouet:
	ocarina -y -g real_theorem -aadlv2 -I../../src/property_set -I../../src/aadl -real_lib $(top_srcdir)/src/real/rma_theorems.real -real_theorem rma -r rma.impl $(AADL_SOURCES)
