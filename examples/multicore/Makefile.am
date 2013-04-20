AADL_SOURCES = $(srcdir)/AvionicsBusManagers.aadl
AADL_ROOT    = avionicsbusmgr.xps8500

OTHER_FILES = $(srcdir)/BCMgr.c $(srcdir)/busmgr0.aadl			\
	$(srcdir)/M0RTMgr.c $(srcdir)/M1RTMgr.c $(srcdir)/M2RTMgr.c	\
	$(srcdir)/messages.aadl $(srcdir)/MsgType.h			\
	$(srcdir)/rtbusmgr1.aadl $(srcdir)/rtbusmgr0.aadl		\
	$(srcdir)/rtbusmgr2.aadl $(srcdir)/devicesconf.c		\
	$(srcdir)/network.aadl

CLEANDIRS = avionicsbusmgr_xps8500
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl build_c
