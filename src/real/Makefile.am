# Retrieve all source files

BRUTE_REAL=${shell find . $(srcdir) -name '*.real' | grep -v 'b~' 2> /dev/null}
REAL_SOURCES = ${sort $(srcdir) $(BRUTE_REAL)}

EXTRA_DIST= $(REAL_SOURCES)

clean-local:
	-rm *~
