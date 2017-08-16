AADL_SOURCES = $(srcdir)/integration.aadl

AADL_ROOT    = mjpeg::integration::integration.a9impl
#AADL_ROOT =  mjpeg::integration::integration.demuxub_vlda9
#AADL_ROOT =  mjpeg::integration::integration.demuxub_iqzza9
#AADL_ROOT =  mjpeg::integration::integration.demuxub_idcta9
#AADL_ROOT =  mjpeg::integration::integration.demuxlibuub_idcta9

OTHER_FILES = $(srcdir)/BLOCK_METRICS.cpp $(srcdir)/DEMUX.h		\
	$(srcdir)/LIBU.cpp $(srcdir)/BLOCK_METRICS.h			\
	$(srcdir)/IDCT.cpp $(srcdir)/LIBU.h				\
	$(srcdir)/COLOR_METRICS.cpp $(srcdir)/IDCT.h $(srcdir)/VLD.cpp	\
	$(srcdir)/COLOR_METRICS.h $(srcdir)/IQZZ.cpp $(srcdir)/VLD.h	\
	$(srcdir)/DEMUX.cpp $(srcdir)/IQZZ.h				\
	$(srcdir)/mjpeg-platform.aadl $(srcdir)/mjpeg-software.aadl	\
	$(srcdir)/spacestudio.aadl

CLEANDIRS = SpaceStudioProject
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= parse-aadl

# The backend is deactivated for the moment
#spacestudio
