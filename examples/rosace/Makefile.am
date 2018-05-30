AADL_SOURCES = $(srcdir)/rosace-posix.aadl
AADL_ROOT    = rosace_posix.multicore

OTHER_FILES = $(srcdir)/common/README $(srcdir)/common/app2_code.c	\
	$(srcdir)/common/app3_code.c $(srcdir)/common/app_code.c	\
	$(srcdir)/common/common.h $(srcdir)/common/io.h			\
	$(srcdir)/rosace-software.aadl $(srcdir)/log.c			\
	$(srcdir)/rosace-threads.aadl $(srcdir)/app2_aadl.c		\
	$(srcdir)/rosace-hardware.aadl $(srcdir)/rosace-xtratum.aadl	\
	$(srcdir)/app3_aadl.c $(srcdir)/rosace-posix.aadl		\
	$(srcdir)/rosace.aadl $(srcdir)/app_aadl.c			\
	$(srcdir)/rosace-rtems.aadl $(srcdir)/userdefined.mk

CLEANDIRS = rosace_posix_monocore rosace_xtratum_smp	\
	rosace_posix_multicore rosace_rtems_monocore	\
	rosace_rtems_multicore rosace_xtratum_monocore

CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl build_c check_specific

check_specific: posix_monocore posix_mc rtems_monocore rtems_multicore \
        xtratum_monocore xtratum_multicore

posix_monocore:
	$(OCARINA) $(OCARINA_FLAGS) -g polyorb_hi_c -r ROSACE::POSIX::rosace_posix.monocore rosace-posix.aadl

posix_mc:
	$(OCARINA) $(OCARINA_FLAGS) -g polyorb_hi_c -r ROSACE::POSIX::rosace_posix.multicore rosace-posix.aadl

rtems_monocore:
	$(OCARINA) $(OCARINA_FLAGS) -g polyorb_hi_c -r ROSACE::RTEMS::rosace_rtems.monocore rosace-rtems.aadl

rtems_multicore:
	$(OCARINA) $(OCARINA_FLAGS) -g polyorb_hi_c -r ROSACE::RTEMS::rosace_rtems.multicore rosace-rtems.aadl

xtratum_monocore:
	$(OCARINA) $(OCARINA_FLAGS) -g xtratum_configuration -r ROSACE::XtratuM::rosace_xtratum.monocore rosace-xtratum.aadl
	$(OCARINA) $(OCARINA_FLAGS) -g polyorb_hi_c -r ROSACE::XtratuM::rosace_xtratum.monocore rosace-xtratum.aadl

xtratum_multicore:
	$(OCARINA) $(OCARINA_FLAGS) -g xtratum_configuration -r ROSACE::XtratuM::rosace_xtratum.smp rosace-xtratum.aadl

air_monocore:
	$(OCARINA) $(OCARINA_FLAGS) -g air_configuration -r ROSACE::XtratuM::rosace_xtratum.monocore rosace-xtratum.aadl
