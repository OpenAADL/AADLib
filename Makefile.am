AUTOMAKE_OPTIONS = no-dependencies
ACLOCAL_AMFLAGS = -I support
CLEANFILES = config-stamp

SUBDIRS = src examples
DIST_SUBDIRS = $(SUBDIRS)

clean-local:
	-rm -f *~

EXTRA_DIST = $(srcdir)/README

# We disable checking of the distclean rule, it is a nuisance
distcleancheck:
	@:

distuninstallcheck:
	@:
