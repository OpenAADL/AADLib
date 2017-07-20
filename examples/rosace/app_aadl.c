#include <stdbool.h>

#include <common.h>
#include <io.h>

#define MATH
#include <app_code.c>

void aircraft_dynamics_aadl (float delta_e, float t, float* va, float* vz, float* q, float* az, float* h) {
  static bool first_run = true;
  struct aircraft_dynamics_outs_t outputs;

  if (first_run) {
    first_run = false;
    delta_e = 0.012009615652468, t = 41813.92119463;
  }

  aircraft_dynamics (delta_e, t, &outputs);
  *va = outputs.Va;
  *vz = outputs.Vz;
  *q = outputs.q;
  *az = outputs.az;
  *h = outputs.h;
}

void elevator_aadl (float delta_e_c, float* output) {
  *output = elevator (delta_e_c);
}

void engine_aadl (float delta_th_c, float* output) {
  *output = engine (delta_th_c);
}
