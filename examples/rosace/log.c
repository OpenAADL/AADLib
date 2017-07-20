#include <stdio.h>
#include "types.h"
#define FMTFLOAT "%5.15f"

void rosace_log
    (rosace__software__rosace_float t,
    rosace__software__rosace_float va,
    rosace__software__rosace_float az,
    rosace__software__rosace_float q,
    rosace__software__rosace_float vz,
    rosace__software__rosace_float h,
    rosace__software__rosace_float delta_th_c,
    rosace__software__rosace_float delta_e_c)
{

  static int first=1;
  if (first) {
    printf("# %15s, %15s, %15s, %15s, %15s, %15s, %15s, %15s\n",
           "T","Va","az","q","Vz","h","delta_th_c","delta_e_c");
    first = 0;
  }

  printf("%3.4f, ", t);
  printf(FMTFLOAT", ", va);
  printf(FMTFLOAT", ", az);
  printf(FMTFLOAT", ", q);
  printf(FMTFLOAT", ", vz);
  printf(FMTFLOAT", ", h);
  printf(FMTFLOAT", ", delta_th_c);
  printf(FMTFLOAT"\n", delta_e_c);

}
