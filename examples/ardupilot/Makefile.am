AADL_SOURCES = $(srcdir)/main_Ardupilot.aadl
AADL_ROOT    = ardupilot_shield.impl

OTHER_FILES =					\
	$(srcdir)/ardupilot_platform.aadl	\
	$(srcdir)/ardupilot_software.aadl	\
	$(srcdir)/flt-mgmt.c			\
	$(srcdir)/gps.c				\
	$(srcdir)/throttle.c                    \
	$(srcdir)/userdefined.mk		\
	$(srcdir)/yaw.c

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real
# build_c: probleme pour prendre en compte userdefined.mk lors d'un distcheck

distclean-local:
	-rm -rf ardupilot_i
