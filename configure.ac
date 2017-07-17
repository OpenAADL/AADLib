AC_PREREQ(2.57)
AC_INIT(AADLib, 2017.x)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_AUX_DIR(support)

##########################################
# Initialization.
##########################################

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE([1.9 tar-pax] foreign)

##########################################
# Check fo various programs.
##########################################

AC_CHECK_PROG(MV, mv, mv)
AC_CHECK_PROG(RM, rm, rm)
AC_CHECK_PROG(CP, cp, cp)

##########################################
# Check for GNU Make
##########################################

AM_GNU_MAKE

##########################################
# Check for Ocarina
##########################################

AM_PATH_OCARINA(1.1, ,AC_MSG_ERROR([Ocarina 1.1 or later is not installed on your system]))

##########################################
# Windows requires specific targets
##########################################

case "$host_os" in
  cygwin* | mingw*)
    windows=true
    ;;
  *)
    windows=false
    ;;
esac
AM_CONDITIONAL(WINDOWS, test x$windows = xtrue)

############################################
# Set the value corresponding to cygpath -u
############################################

if test x"$CYGPATH_W" = x"echo"; then
   CYGPATH_U="echo"
else
   CYGPATH_U="cygpath -u"
fi
AC_SUBST(CYGPATH_U)

###############################################################
# Force the installation prefix to be equal to the Ocarina one
###############################################################

prefix='$(OCARINA_PREFIX)'

##########################################
# Output generated files
##########################################

dnl Important! One file per line, nothing before
dnl or after except whitespace! This section
dnl may, one day, be edited automatically to remove
dnl some entries.

AC_OUTPUT([
	Makefile
	examples/Makefile
	examples/adiru/Makefile
        examples/ahrs_discovery/Makefile
        examples/aocs/Makefile
	examples/aram/Makefile
	examples/ardupilot/Makefile
	examples/arinc653_annex/Makefile
	examples/arinc653_annex/example_1/Makefile
	examples/arinc653_annex/example_2/Makefile
	examples/asl/Makefile
	examples/behavior_annex/Makefile
	examples/car/Makefile
	examples/data_modeling_annex/Makefile
	examples/fcs/Makefile
	examples/flow_analysis/Makefile
	examples/fms/Makefile
	examples/isr/Makefile
	examples/line_follower/Makefile
	examples/memory/Makefile
	examples/mixin/Makefile
        examples/mosart/Makefile
        examples/multicore/Makefile
	examples/paparazzi/Makefile
        examples/pathfinder_system/Makefile
	examples/perseus/Makefile
	examples/producer_consumer/Makefile
	examples/radar/Makefile
	examples/rap/Makefile
	examples/rap_code/Makefile
	examples/ravenscar/Makefile
	examples/rma/Makefile
	examples/redundancy/Makefile
        examples/robot/Makefile
        examples/robot_ba/Makefile
	examples/round_robin/Makefile
	examples/satellite/Makefile
        examples/stm32discovery_ada/Makefile
        examples/time_triggered/Makefile
	examples/units/Makefile
	examples/uxv/Makefile
	examples/uxv/emaxxv2/Makefile
	examples/uxv/minirocket/Makefile
	examples/uxv/quadrirotorv0/Makefile
	examples/uxv/quadrirotorv1/Makefile
	examples/uxv/traxsterv3/Makefile
	examples/voter/Makefile
	examples/pacemaker/Makefile
	examples/doors/Makefile
	src/Makefile
	src/aadl/Makefile
	src/property_set/Makefile
	src/real/Makefile
])

AC_MSG_NOTICE(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%)
AC_MSG_NOTICE(AADLib configuration is complete!)
AC_MSG_NOTICE(GNU make command name: "$GNU_MAKE")
AC_MSG_NOTICE(%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%)
