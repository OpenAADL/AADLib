AADL_SOURCES = $(srcdir)/model.aadl
AADL_ROOT    = adiru.impl

OTHER_FILES = $(srcdir)/acc_code.c $(srcdir)/adiru_devices.aadl		\
   $(srcdir)/adiru_errlibrary.aadl $(srcdir)/adiru_memory.aadl		\
   $(srcdir)/adiru_processor.aadl $(srcdir)/adirup_code.c		\
   $(srcdir)/model.aadl $(srcdir)/partitions.aadl $(srcdir)/receive.c	\
   $(srcdir)/shm_code.c $(srcdir)/shm_datatype.aadl			\
   $(srcdir)/subprograms.aadl $(srcdir)/threads.aadl

CLEANDIRS =
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl real deos_conf vxworks653_conf deos_code vxworks653_code
