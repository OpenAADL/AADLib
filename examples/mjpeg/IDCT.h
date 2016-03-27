// ***********************************************************************
//
// Filename : IDCT.h
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:01:53 EDT 2011
//
//
// ***********************************************************************

#ifndef IDCT_H
#define IDCT_H

#include "SpaceBaseModule.h"
#include "jpeg.h"

#include <systemc.h>

// Definition
#define c0_1  16384
#define c0_s2 23170
#define c1_1  16069
#define c1_s2 22725
#define c2_1  15137
#define c2_s2 21407
#define c3_1  13623
#define c3_s2 19266
#define c4_1  11585
#define c4_s2 16384
#define c5_1  9102
#define c5_s2 12873
#define c6_1  6270
#define c6_s2 8867
#define c7_1  3196
#define c7_s2 4520
#define c8_1  0
#define c8_s2 0
#define sqrt2 c0_s2

/* The number of bits of accuracy in all (signed) integer operations:
   May lie between 1 and 32 (bounds inclusive).
*/
#define ARITH_BITS      16

/* The minimum signed integer value that fits in ARITH_BITS: */
#define ARITH_MIN       (-1 << (ARITH_BITS-1))
#define ARITH_MAX       (~ARITH_MIN)

/* The number of bits coefficients are scaled up before 2-D idct: */
#define S_BITS           3
/* The number of bits in the fractional part of a fixed point constant: */
#define C_BITS          14

/* This version is vital in passing overall mean error test. */
#define descale(x, n) (((x) + (1 << ((n) - 1)) - ((x) < 0)) >> (n))


	   	
		// Thread
	    void idct_funct(unsigned int uiCommand);
	    void before_idct(void);
		
	
		
		void rot(int f, int k, int x, int y, int* rx, int* ry);
		void idct_1d(int* Y);
	int Y[BLOCK_SIZE];
		int row, column;
		SPACE_ALIGNED short in[BLOCK_SIZE];
		SPACE_ALIGNED unsigned char Idct[BLOCK_SIZE];
		unsigned int block;
		unsigned int NBLOCKS;


#endif
