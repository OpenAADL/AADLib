AUTOMAKE_OPTIONS = no-dependencies
ACLOCAL_AMFLAGS = -I support
CLEANFILES = config-stamp

SUBDIRS = src examples
DIST_SUBDIRS = $(SUBDIRS)

clean-local:
	-rm -rf *~ ocarina_out

EXTRA_DIST = $(srcdir)/README.md

# We disable checking of the distclean rule, it is a nuisance
distcleancheck:
	@:

distuninstallcheck:
	@:
