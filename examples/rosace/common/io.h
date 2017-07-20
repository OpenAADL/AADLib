#ifndef __IO_H__
#define __IO_H__

typedef unsigned long long uint64_t;

struct aircraft_dynamics_outs_t {
    float Va;
    float Vz;
    float q;
    float az;
    float h;
};

typedef struct {
    struct aircraft_dynamics_outs_t sig_outputs;
    uint64_t t_simu;
    float sig_delta_th_c;
    float sig_delta_e_c;
} output_t;

#endif
