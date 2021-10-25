AADL_SOURCES = $(srcdir)/ping-local.aadl
AADL_ROOT    = ping.local

OTHER_FILES = $(srcdir)/msgs.adb $(srcdir)/msgs.ads		\
	$(srcdir)/ping.adb $(srcdir)/ping.ads $(srcdir)/pinged.adb	\
	$(srcdir)/pinged.ads $(srcdir)/software.aadl

CLEANDIRS = ping_local
CLEANFILES = *.lnt demo.svl asn1_deployment.asn

include $(srcdir)/../Makefile.common

OCARINA_FLAGS += --spark2014

AVAILABLE_TARGETS= parse-aadl build_ada

prove:     ## Prove code correctness
	( cd $(CLEANDIRS)/node_a ; gnatprove -Pnode_a.gpr -XTARGET=SPARK -j 0 --warnings=off --report=fail --assumptions --level=4 )
