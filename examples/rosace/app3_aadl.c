#include "common.h"
#include "io.h"

#include <../common/app3_code.c>

void altitude_hold_aadl (float h_f, float h_c, float* output) {
  *output = altitude_hold (h_f, 10000.0 /*h_c*/);
}

void vz_control_aadl (float vz_f, float vz_c, float q_f, float az_f, float* output) {
  *output = Vz_control (vz_f, vz_c, q_f, az_f);
}

void va_control_aadl (float va_f, float vz_f, float q_f, float va_c, float* output) {
  *output = Va_control (va_f, vz_f, q_f, 230.0 /*va_c*/);
}
