#ifndef __COMMON_H__
#define __COMMON_H__

const float __attribute__((weak)) dt       = 1.0f/200.0;
const float __attribute__((weak)) dt_de    = 1.0/200.0;
const float __attribute__((weak)) dt_dx    = 1.0/200.0;

/* Controller parameters */
/* Altitude hold */
const float __attribute__((weak)) Kp_h       = 0.1014048;
const float __attribute__((weak)) Ki_h       = 0.0048288;
const float __attribute__((weak)) h_switch   = 50.0;


// Setpoint commands
float __attribute__((weak)) Vz_c     = -2.5;
float __attribute__((weak)) Va_c     =  0.0;
float __attribute__((weak)) h_c      =  11000;

/* Va Speed controller */

const float __attribute__((weak)) K1_intVa =   0.049802610664357;
const float __attribute__((weak)) K1_Va     = -0.486813084356079;
const float __attribute__((weak)) K1_Vz     = -0.077603095495388;
const float __attribute__((weak)) K1_q      = 21.692383376322041;

/* Vz Speed controller */

const float __attribute__((weak)) K2_intVz   = 0.000627342822264;
const float __attribute__((weak)) K2_Vz     = -0.003252836726554;
const float __attribute__((weak)) K2_q       = 0.376071446897134;
const float __attribute__((weak)) K2_az     = -0.001566907423747;


/* Trimming parameters */
const float __attribute__((weak)) h_eq        = 10000.0;
const float __attribute__((weak)) Va_eq       = 230.0;
const float __attribute__((weak)) Vz_eq       = 0.0;
const float __attribute__((weak)) alpha_eq    = 0.026485847681737;
const float __attribute__((weak)) theta_eq  = 0.026485847681737;

/* Atmosphere parameters */
const float __attribute__((weak)) rho0   = 1.225;
const float __attribute__((weak)) g0     = 9.80665;
const float __attribute__((weak)) T0_0   = 288.15;
const float __attribute__((weak)) T0_h  = -0.0065;
const float __attribute__((weak)) Rs     = 287.05;

/* Aircraft parameters */
const float __attribute__((weak)) masse       = 57837.5;
const float __attribute__((weak)) I_y         = 3781272.0;
const float __attribute__((weak)) S          =  122.6;
const float __attribute__((weak)) cbar        = 4.29;
const float __attribute__((weak)) CD_0        = 0.016;
const float __attribute__((weak)) CD_alpha    = 2.5;
const float __attribute__((weak)) CD_deltae   = 0.05;
const float __attribute__((weak)) CL_alpha    = 5.5;
const float __attribute__((weak)) CL_deltae   = 0.193;
const float __attribute__((weak)) alpha_0    = -0.05;
const float __attribute__((weak)) Cm_0        = 0.04;
const float __attribute__((weak)) Cm_alpha   = -0.83;
const float __attribute__((weak)) Cm_deltae  = -1.5;
const float __attribute__((weak)) Cm_q       = -30;


#define delta_th_eq (1.5868660794926)
#define delta_e_eq (0.012009615652468)


#endif
