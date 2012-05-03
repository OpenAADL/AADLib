AADL_SOURCES = $(srcdir)/car.aadl
AADL_ROOT    = car.impl

OTHER_FILES =		

CLEANDIRS = 

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real cheddar mast aadl_xml 

pouet:
	ocarina -y -g real_theorem -aadlv2 -real_lib $(top_srcdir)/src/real/ravenscar_theorems.real -real_theorem check_pcp -r rma.impl $(AADL_SOURCES)
