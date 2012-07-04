AADL_SOURCES = $(srcdir)/robot.aadl
AADL_ROOT    = line_follower_robot.i

OTHER_FILES =					\
	$(srcdir)/robot.c			\
	$(srcdir)/software_lf.aadl

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real

distclean-local:
	-rm -rf line_follower_robot_i
