#include "common.h"

float
Va_filter(float Va) {
	static float y  = 0.0;
	static float x1 = 0.0;
	static float x2 = 0.0;
	static float x1_tmp = 0.0;
	static float x2_tmp = 0.0;
	static unsigned short debut = 1;
	/* 100 Hz coefficients */
	static float a0 = 0.956543675476034;
	static float a1 = -1.955578398054313;
	static float b0 = 0.000479064865372430;
	static float b1 =  0.000486212556348925;

	if (debut) {
		debut  = 0;
		x1     = Va_eq * (1.0 + a1 - b1);
		x2     = Va_eq;
	}
	// Output
	y = x2;
	// State
	x1_tmp =     - a0 * x2 + b0 * Va;
	x2_tmp =  x1 - a1 * x2 + b1 * Va;
	// Update
	x1 = x1_tmp;
	x2 = x2_tmp;

	return y;
} /* end of Va filter 100 Hz */


float
h_filter(float h){
	static float y  = 0.0;
	static float x1 = 0.0;
	static float x2 = 0.0;
	static float x1_tmp = 0.0;
	static float x2_tmp = 0.0;
	static unsigned short debut = 1;
	/* 100 Hz coefficients */
	static float a0 = 0.766000101841272;
	static float a1 = -1.734903205885821;
	static float b0 = 0.014857648981438;
	static float b1 =  0.016239246974013;

	if (debut) {
		debut  = 0;
		x1     = h_eq * (1.0 + a1 - b1);
		x2     = h_eq;
	}
	// Output
	y = x2;
	// State
	x1_tmp =     - a0 * x2 + b0 * h;
	x2_tmp =  x1 - a1 * x2 + b1 * h;
	// Update
	x1 = x1_tmp;
	x2 = x2_tmp;

	return y;
} 

float
az_filter(float az){
	static float y  = 0.0;
	static float x1 = 0.0;
	static float x2 = 0.0;
	static float x1_tmp = 0.0;
	static float x2_tmp = 0.0;
	static unsigned short debut = 1;
	/* 100 Hz coefficient */
	static float a0 = 0.411240701442774;
	static float a1 = -1.158045899830964;
	static float b0 = 0.107849979167580;
	static float b1 =  0.145344822444230;

	if (debut) {
		debut  = 0;
		x1     = 0.0;
		x2     = 0.0;
	}
	// Output
	y = x2;
	// State
	x1_tmp =     - a0 * x2 + b0 * az;
	x2_tmp =  x1 - a1 * x2 + b1 * az;
	// Update
	x1 = x1_tmp;
	x2 = x2_tmp;

	return y;
}

float
Vz_filter(float Vz) {
	static float y  = 0.0;
	static float x1 = 0.0;
	static float x2 = 0.0;
	static float x1_tmp = 0.0;
	static float x2_tmp = 0.0;
	static unsigned short debut = 1;
	/* 100 Hz coefficients */
	static float a0 = 0.956543675476034;
	static float 	a1 = -1.955578398054313;
	static float b0 = 0.000479064865372430;
	static float 	b1 =  0.000486212556348925;

	if (debut) {
		debut  = 0;
		x1     = 0.0;
		x2     = 0.0;
	}
	// Output
	y = x2;
	// State
	x1_tmp =     - a0 * x2 + b0 * Vz;
	x2_tmp =  x1 - a1 * x2 + b1 * Vz;
	// Update
	x1 = x1_tmp;
	x2 = x2_tmp;

	return y;
}

float
q_filter(float q){
	static float y  = 0.0;
	static float x1 = 0.0;
	static float x2 = 0.0;
	static float x1_tmp = 0.0;
	static float x2_tmp = 0.0;
	static unsigned short debut = 1;
	/* 100 Hz coefficients */
	static float a0 = 0.766000101841272;
	static float a1 = -1.734903205885821;
	static float b0 = 0.014857648981438;
	static float b1 =  0.016239246974013;

	if (debut) {
		debut  = 0;
		x1     = 0.0;
		x2     = 0.0;
	}
	// Output
	y = x2;
	// State
	x1_tmp =     - a0 * x2 + b0 * q;
	x2_tmp =  x1 - a1 * x2 + b1 * q;
	// Update
	x1 = x1_tmp;
	x2 = x2_tmp;

	return y;
}
