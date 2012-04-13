AADL_SOURCES = $(srcdir)/rma.aadl
AADL_ROOT    = rma.impl

OTHER_FILES =					\
	$(srcdir)/hello.c

CLEANDIRS = rma_impl

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real cheddar build_ada build_c

pouet:
	ocarina -y -g real_theorem -aadlv2 -real_lib $(top_srcdir)/src/real/ravenscar_theorems.real -real_theorem check_pcp -r rma.impl $(AADL_SOURCES)
