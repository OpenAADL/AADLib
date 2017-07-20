#include "common.h"
#include "io.h"

#include "../common/app2_code.c"

void va_filter_aadl (float va, float* output) {
  *output = Va_filter (va);

}

void h_filter_aadl (float h, float* output) {
  *output = h_filter (h);

}

void az_filter_aadl (float az, float* output) {
  *output = az_filter (az);
}

void vz_filter_aadl (float vz, float* output) {
  *output = Vz_filter (vz);

}

void q_filter_aadl (float q, float* output) {
  *output = q_filter (q);
}
