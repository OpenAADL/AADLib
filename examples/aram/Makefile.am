AADL_SOURCES = $(srcdir)/gaia-validation.aadl
AADL_ROOT    = gaia.validation

OTHER_FILES = $(srcdir)/blocks.aadl $(srcdir)/gaia-validation.aadl	\
	   $(srcdir)/data_types.aadl $(srcdir)/gaia.aadl		\
	   $(srcdir)/gaia-functions.aadl $(srcdir)/library.aadl		\
	   $(srcdir)/gaia-implementations.aadl $(srcdir)/lib.real	\
	   $(srcdir)/aram_properties.aadl				\
	   $(srcdir)/mission_properties.aadl				\
	   $(srcdir)/processor_properties.aadl				\
	   $(srcdir)/bus_properties.aadl				\
	   $(srcdir)/physical_properties.aadl


CLEANDIRS = gaia_first_architecture gaia_second_architecture gaia_validation
CLEANFILES =

include $(srcdir)/../Makefile.common

AVAILABLE_TARGETS= mission-parse functional-parse blocks-parse		\
	  impl-parse validation-parse instanciate-impl1			\
	  instanciate-impl2 connectivity-matrix-impl1			\
	  connectivity-matrix-impl2 functions-matrix-validation		\
	  check-real-functional check-real-first-impl			\
	  check-real-second-impl check-real-validation check-real

OCARINA_FLAGS=-aadlv2 -y -I$(srcdir)
REAL_FLAGS=-g real_theorem -real_lib ./lib.real

MISSION=gaia.aadl
FUNCTIONAL=gaia-functions.aadl
BLOCKS=blocks.aadl
IMPLEMENTATION=gaia-implementations.aadl
VALIDATION=gaia-validation.aadl

mission-parse:
	ocarina $(OCARINA_FLAGS) $(MISSION)

functional-parse:
	ocarina $(OCARINA_FLAGS) $(FUNCTIONAL)

blocks-parse:
	ocarina $(OCARINA_FLAGS) $(BLOCKS)

impl-parse:
	ocarina $(OCARINA_FLAGS) $(IMPLEMENTATION)

validation-parse:
	ocarina $(OCARINA_FLAGS) $(VALIDATION)

instanciate-impl1:
	ocarina $(OCARINA_FLAGS) $(IMPLEMENTATION) -i -r gaia.first_architecture

instanciate-impl2:
	ocarina $(OCARINA_FLAGS) $(IMPLEMENTATION) -i -r gaia.second_architecture

connectivity-matrix-impl1:
	ocarina $(OCARINA_FLAGS) $(IMPLEMENTATION) -g connection_matrix -r gaia.first_architecture

connectivity-matrix-impl2:
	ocarina $(OCARINA_FLAGS) $(IMPLEMENTATION) -g connection_matrix -r gaia.second_architecture

functions-matrix-validation:
	-ocarina $(OCARINA_FLAGS) -g function_matrix -r gaia.validation $(VALIDATION)

parse-all: mission-parse			\
	functional-parse			\
	blocks-parse				\
	impl-parse				\
	validation-parse

instance-all: 	instanciate-impl1		\
	instanciate-impl2

check-all: parse-all				\
	instance-all				\
	connectivity-matrix-impl1		\
	connectivity-matrix-impl2		\
	check-real				\
	functions-matrix-validation

check-real-functional:
	-ocarina $(OCARINA_FLAGS) $(REAL_FLAGS) -r gaia.functional $(FUNCTIONAL)

check-real-first-impl:
	-ocarina $(OCARINA_FLAGS) $(REAL_FLAGS) -r gaia.first_architecture $(IMPLEMENTATION)

check-real-second-impl:
	-ocarina $(OCARINA_FLAGS) $(REAL_FLAGS) -r gaia.second_architecture $(IMPLEMENTATION)

check-real-validation:
	-ocarina $(OCARINA_FLAGS) $(REAL_FLAGS) -r gaia.validation $(VALIDATION)

check-real: check-real-functional check-real-first-impl check-real-second-impl check-real-validation
