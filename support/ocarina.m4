# Automake macro for Ocarina

dnl ##########################################################################
dnl AM_PATH_OCARINA([MINIMUM-VERSION [, ACTION-IF-FOUND
dnl                    [, [ACTION-IF-NOT-FOUND]]])
dnl Look for Ocarina, then define OCARINA_ADAFLAGS, OCARINA_LIBS and
dnl OCARINA_RUNTIME

AC_DEFUN([AM_PATH_OCARINA],
[

AC_ARG_ENABLE(ocarina-version-check,
[  --enable-ocarina-version-check          Turn on Ocarina version checking],
[if [[ "$enableval" = "yes" ]]; then
  ocarina_version_check=true
else
  ocarina_version_check=false
fi],
[ocarina_version_check=true])

AC_ARG_WITH(ocarina-prefix,
  AC_HELP_STRING([--with-ocarina-prefix=PREFIX],
                 [Prefix where Ocarina is installed (optional)]),
  [ocarina_config_prefix="$withval"], [ocarina_config_prefix=""])

AC_ARG_WITH(ocarina-runtime,
  AC_HELP_STRING([--with-ocarina-runtime=RUNTIME_PREFIX],
                 [Prefix where the Ocarina runtimes are installed (optional)]),
  [ocarina_runtime_prefix="$withval"], [ocarina_runtime_prefix=""])

min_ocarina_version=ifelse([$1], , 1.1, $1)
min_ocarina_major_version=`echo $min_ocarina_version | \
  sed 's/\([[0-9]]*\).\([[0-9]]*\)/\1/'`
min_ocarina_minor_version=`echo $min_ocarina_version | \
  sed 's/\([[0-9]]*\).\([[0-9]]*\)/\2/'`

AS_IF([test x$ocarina_config_prefix != x],
      [OCARINA_CONFIG=$ocarina_config_prefix/bin/ocarina-config])

AC_PATH_PROG(OCARINA_CONFIG, ocarina-config, no)

AS_IF([test x"$ocarina_config_prefix" != "x" -a "${ocarina_version_check}" = "false"],
      [OCARINA_PREFIX="$ocarina_config_prefix"
       OCARINA_ADAFLAGS="false"
       OCARINA_LIBS="flase"
       OCARINA_RUNTIME="$ocarina_config_prefix/include/ocarina/runtime"
       OCARINA_RESOURCES="$ocarina_config_prefix/share/ocarina"],
      [test "$OCARINA_CONFIG" != "no"],
      [AC_MSG_CHECKING([for Ocarina - version >= $min_ocarina_version])
       OCARINA_PREFIX=`$OCARINA_CONFIG --prefix`
       OCARINA_ADAFLAGS=`$OCARINA_CONFIG --cflags`
       OCARINA_LIBS=`$OCARINA_CONFIG --libs`
       OCARINA_RUNTIME=`$OCARINA_CONFIG --runtime`
       OCARINA_RESOURCES=`$OCARINA_CONFIG --resources`
       ocarina_major_version=`$OCARINA_CONFIG --version | \
         sed 's/Ocarina \([[0-9]]*\).\([[0-9]]*\).*/\1/'`
       ocarina_minor_version=`$OCARINA_CONFIG --version | \
         sed 's/Ocarina \([[0-9]]*\).\([[0-9]]*\).*/\2/'`
       AS_IF([test $ocarina_major_version -gt $min_ocarina_major_version -o \( $ocarina_major_version -eq $min_ocarina_major_version -a $ocarina_minor_version -ge $min_ocarina_minor_version \)],
              [AC_MSG_RESULT(yes)
               ifelse([$2], , :, [$2])],
              [AC_MSG_RESULT(no)
               ifelse([$3], , :, [$3])])],
      [$3])
AC_SUBST(OCARINA_PREFIX)
AC_SUBST(OCARINA_ADAFLAGS)
AC_SUBST(OCARINA_LIBS)
AC_SUBST(OCARINA_RUNTIME)
AC_SUBST(OCARINA_RESOURCES)
])
