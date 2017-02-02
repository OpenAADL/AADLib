AADL_SOURCES = $(srcdir)/ahrs-systems.aadl

AADL_ROOT    = ahrs_system.impl

OTHER_FILES = $(srcdir)/ahrs-data_types.aadl				\
	$(srcdir)/ahrs-software.aadl $(srcdir)/ahrs-hardware.aadl	\
	$(srcdir)/ahrs-subprograms.aadl $(srcdir)/ahrs.aadl

CLEANDIRS = ahrs_system_impl
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl c cheddar run_cheddar
