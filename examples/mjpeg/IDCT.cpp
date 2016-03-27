// ***********************************************************************
//
// Filename : IDCT.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:01:53 EDT 2011
//
//
// ***********************************************************************

#include "IDCT.h"




/* Butterfly: but(a,b,x,y) = rot(sqrt(2),4,a,b,x,y) */
#define but(a,b,x,y)    do { x = a - b; y = a + b; } while(0)
#define Y(i,j)          Y[8*i+j]
#define Idct_fnc(i,j)       Idct[8*i+j]

// Table static
static const int COS[2][8] = {
    {c0_1, c1_1, c2_1, c3_1, c4_1, c5_1, c6_1, c7_1},
    {c0_s2, c1_s2, c2_s2, c3_s2, c4_s2, c5_s2, c6_s2, c7_s2}
};

void before_idct()
{
	NBLOCKS = 0;
}

///////////////////////////////////////////////////////////////////////////////
///
/// Thread
///
///////////////////////////////////////////////////////////////////////////////
void idct_funct(unsigned int uiCommand)
{
	SpacePrint("IDCT\n");
	// Variable
	
	//unsigned int uiCommand;


		// Read the command
		//Read<unsigned int>(from_demux, SPACE_WAIT_FOREVER, &uiCommand);

		///
		///	HEADER
		///
		if (uiCommand == HEADER)
		{
			// Get frame attributes from demux (first SOF)
			Read<unsigned int>(from_demux, &NBLOCKS);
		}

		///
		///	DATA
		///
		if (uiCommand == DATA)
		{
			for (block = 0; block < (2 * NBLOCKS); ++block)
			{
				Read<SPACE_ALIGNED short>(from_iqzz, &in[0], BLOCK_SIZE);
				computeFor(1);
				for (row = 0; row < BLOCK_HEIGHT; row++)
				{
					for (column = 0; column < BLOCK_WIDTH; column++)
						Y(row, column) = in[row*BLOCK_WIDTH+column] << S_BITS;
					idct_1d(&Y(row, 0));
					/* Result Y is scaled up by factor sqrt(8)*2^S_BITS. */
				}

				for (column = 0; column < BLOCK_WIDTH; column++)
				{
					int Yc[BLOCK_HEIGHT];

					for (row = 0; row < BLOCK_HEIGHT; row++)
						Yc[row] = Y(row, column);

					idct_1d(Yc);

					for (row = 0; row < BLOCK_HEIGHT; row++)
					{
						/* Result is once more scaled up by a factor sqrt(8). */
						int r = 128 + descale(Yc[row], 2*S_BITS);
						/* Clip to 8 bits unsigned: */
						r = r > 0 ? (r < 255 ? r : 255) : 0;
						Idct_fnc(row, column) = r;
					}
				}
	
				computeFor(100);
				Write<SPACE_ALIGNED unsigned char>(to_libu, &Idct[0], BLOCK_SIZE);
				computeFor(1);
			}
		}

}


///////////////////////////////////////////////////////////////////////////////
///
/// rot
///
///////////////////////////////////////////////////////////////////////////////
void rot(int f, int k, int x, int y, int* rx, int* ry)
{
#define Cos(k)  COS[f][k]
#define Sin(k)  Cos(8-k)
    *rx = (Cos(k) * x - Sin(k) * y) >> C_BITS;
    *ry = (Sin(k) * x + Cos(k) * y) >> C_BITS;
#undef Cos
#undef Sin
}


///////////////////////////////////////////////////////////////////////////////
///
/// idct_1d
///
///////////////////////////////////////////////////////////////////////////////
void idct_1d(int* Y)
{
	// Variable
    int z1[8], z2[8], z3[8];

    /* Stage 1: */
    but(Y[0], Y[4], z1[1], z1[0]);
    rot(1, 6, Y[2], Y[6], &z1[2], &z1[3]);
    but(Y[1], Y[7], z1[4], z1[7]);
    z1[5] = (sqrt2 * Y[3]) >> C_BITS;
    z1[6] = (sqrt2 * Y[5]) >> C_BITS;

    /* Stage 2: */
    but(z1[0], z1[3], z2[3], z2[0]);
    but(z1[1], z1[2], z2[2], z2[1]);
    but(z1[4], z1[6], z2[6], z2[4]);
    but(z1[7], z1[5], z2[5], z2[7]);

    /* Stage 3: */
    z3[0] = z2[0];
    z3[1] = z2[1];
    z3[2] = z2[2];
    z3[3] = z2[3];
    rot(0, 3, z2[4], z2[7], &z3[4], &z3[7]);
    rot(0, 1, z2[5], z2[6], &z3[5], &z3[6]);

    /* Final stage 4: */
    but(z3[0], z3[7], Y[7], Y[0]);
    but(z3[1], z3[6], Y[6], Y[1]);
    but(z3[2], z3[5], Y[5], Y[2]);
    but(z3[3], z3[4], Y[4], Y[3]);
}
