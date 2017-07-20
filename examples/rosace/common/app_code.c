#include "common.h"
#include "io.h"

#ifdef MATH
#include <math.h>
#else
#define pow(x,y) x
#define cos(x) 0.0
#define sin(x) 0.0
#define atan(x) 1.0
#define sqrt(x) x
#endif

void aircraft_dynamics (float delta_e, float T,  struct aircraft_dynamics_outs_t *outputs){

	static int debut = 1;

	static float u 	= 0.0;
	static float w 	= 0.0;
	static float q 	= 0.0;
	static float theta 	= 0.0;
	static float h 	= 0.0;
	static float u_dot 	= 0.0;
	static float w_dot 	= 0.0;
	static float q_dot 	= 0.0;
	static float theta_dot = 0.0;
	static float h_dot 	= 0.0;

	static float CD 	= 0.0;
	static float CL 	= 0.0;
	static float Cm 	= 0.0;

	static float Xa 	= 0.0;
	static float Za 	= 0.0;
	static float Ma 	= 0.0;

	static float alpha 	= 0.0;
	static float qbar 	= 0.0;
	static float V 	= 0.0;
	static float rho 	= 0.0;

	if (debut) {
		debut = 0;
		u     = Va_eq * cos(theta_eq);
		w     = Va_eq * sin(theta_eq);
		q     = 0.0;
		theta = theta_eq;
		h     = h_eq;
	}

	rho   = rho0 * pow(1.0 + T0_h / T0_0 * h,- g0 / (Rs * T0_h) - 1.0);
	alpha = atan(w/u);
	/* print_float(alpha, "alpha:"); */
	/* print_float(w, "w:"); */
	/* print_float(u, "u:"); */
	V     = sqrt(u * u + w * w);
	qbar  = 0.5 * rho * V * V;
	CL    = CL_deltae * delta_e + CL_alpha * (alpha - alpha_0);
	/* print_float(CL_deltae,"CL_deltae:"); */
	/* print_float(delta_e,"delta_e:"); */
	/* print_float(CL_alpha,"CL_alpha:"); */
	/* print_float(alpha_0,"alpha_0:"); */
	CD    = CD_0 + CD_deltae * delta_e + CD_alpha * (alpha - alpha_0) * (alpha - alpha_0);
	Cm    = Cm_0 + Cm_deltae * delta_e + Cm_alpha * alpha + 0.5 * Cm_q * q * cbar / V;
	Xa    = - qbar * S * (CD * cos(alpha) - CL * sin(alpha));
	Za    = - qbar * S * (CD * sin(alpha) + CL * cos(alpha));
	/* print_float(qbar, "qbar:"); */
	/* print_float(S, "S:"); */
	/* print_float(CD, "CD:"); */
	/* print_float(sin(alpha), "sin(alpha):"); */
	/* print_float(CL, "CL:"); */
	/* print_float(cos(alpha), "cos(alpha):"); */
	/* print_float(CD * sin(alpha), "CD * sin"); */
	/* print_float(CL * cos(alpha), "CL * cos"); */
	/* print_float((CD * sin(alpha) + CL * cos(alpha)), "le plus"); */
	/* print_float(qbar * S,"qbar * S"); */
	/* print_float(Za, "Za:"); */

	Ma    = qbar * cbar * S * Cm;

	// Output
	outputs -> Va = V;
	outputs -> Vz = w * cos(theta) - u * sin(theta);
	outputs -> q  = q;
	outputs -> az = g0 * cos(theta) + Za / masse;
	/* print_float(g0, "g0:"); */
	/* print_float(cos(theta), "cos(theta):"); */
	/* print_float(Za, "Za:"); */
	/* print_float(masse, "masse:"); */

	outputs -> h  = h;
	// State Equation
	u_dot     = - g0 * sin (theta) - q * w + (Xa + T) / masse;
	w_dot     = g0 * cos (theta) + q * u + Za / masse;
	q_dot     = Ma / I_y;
	theta_dot = q;
	h_dot     = u * sin(theta) - w * cos(theta);
	// Update State
	u     += dt * u_dot;
	w     += dt * w_dot;
	q     += dt * q_dot;
	theta += dt * theta_dot;
	h     += dt * h_dot;


	static float Time = 0.0;


	// instant++;
	Time = Time + dt;
}

float
elevator(float delta_e_c) {

	static float y  = delta_e_eq;
	static float x1 = delta_e_eq;
	static float x2 = 0.0;
	static float x1_dot = 0.0;
	static float x2_dot = 0.0;
	static float omega = 25.0;
	static float xi = 0.85;

	// Output
	y = x1;
	// State Equation
	x1_dot = x2;
	x2_dot = -omega * omega * x1 - 2.0 * xi * omega * x2 + omega * omega * delta_e_c;
	// Update State
	x1 += dt_de * x1_dot;
	x2 += dt_de * x2_dot;

	return y;
}


float
engine(float delta_th_c) {

	static float y      = delta_th_eq;
	static float x1     = delta_th_eq;
	static float x1_dot = 0.0;
	static float tau    = 0.75;

	// Output
	y = 26350.0 * x1;
	// State Equation
	x1_dot = -tau * x1 + tau * delta_th_c;
	// Update State
	x1 += dt_dx * x1_dot;

	return y;
}
