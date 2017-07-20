#include "common.h"

float
altitude_hold(float h_f, float h_c){
  float Vz_c     = -2.5;
	static float y = 0.0;
	static float Ts_h = 1.0/50.0;
	static float integrator = 532.2730285;

	if ((h_f - h_c) < -50) {
		// Output
		y = Vz_c;
	}
	else if ((h_f - h_c) > 50) {
		// Output
		y = -Vz_c;
	}
	else {
		// Output
		y = Kp_h * (h_f - h_c) + Ki_h * integrator;
		// State
		integrator += Ts_h * (h_f - h_c);
	}

	return y;
}

float
Vz_control(float Vz_f, float Vz_c, float q_f, float az_f){
	static float y = 0.0;
	static float Ts_K2 = 1.0/50.0;
	static float integrator = 0.0;

	// Output
	y = K2_intVz * integrator + K2_Vz * Vz_f + K2_q * q_f + K2_az * az_f + delta_e_eq;
	// State
	integrator += Ts_K2 * (Vz_c - Vz_f);

	return y;
}

float
Va_control(float Va_f, float Vz_f, float q_f, float Va_c){
	static float y = 0.0;
	static float Ts_K1 = 1.0/50.0;
	static float integrator = 0.0;

	// Output
	y = K1_intVa * integrator + K1_Va * (Va_f - Va_eq) + K1_Vz * Vz_f + K1_q * q_f + delta_th_eq;
	// State
	integrator += Ts_K1 * (Va_c - Va_f + Va_eq);

	return y;
}
