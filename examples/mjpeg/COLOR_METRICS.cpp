// ***********************************************************************
//
// Filename : COLOR_METRICS.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Tue Sep 24 10:38:50 EDT 2013
//
//
// ***********************************************************************

#include "COLOR_METRICS.h"





struct color_statistics {
	int minR, minG, minB, minA;
	int avgR, avgG, avgB, avgA;
	int maxR, maxG, maxB, maxA;
};

#define BURST_SIZE 50

void color()
{
	int nb_blocks = 0;


		int minR = 255, minG = 255, minB = 255, minA = 255;
		int maxR = 0, maxG = 0, maxB = 0, maxA = 0;
		int sumR = 0, sumG = 0, sumB = 0, sumA = 0;

		color_statistics block_colors[BURST_SIZE];

		Read<int>(from_libu, block_colors, BURST_SIZE);

		for(int i=0; i<BURST_SIZE; i++) {
			sumR += block_colors[i].avgR;
			sumG += block_colors[i].avgG;
			sumB += block_colors[i].avgB;
			sumA += block_colors[i].avgA;

			if(minR < block_colors[i].minR) minR = block_colors[i].minR;
			if(minG < block_colors[i].minG) minG = block_colors[i].minG;
			if(minB < block_colors[i].minB) minB = block_colors[i].minB;
			if(minA < block_colors[i].minA) minA = block_colors[i].minA;

			if(maxR > block_colors[i].maxR) maxR = block_colors[i].maxR;
			if(maxG > block_colors[i].maxG) maxG = block_colors[i].maxG;
			if(maxB > block_colors[i].maxB) maxB = block_colors[i].maxB;
			if(maxA > block_colors[i].maxA) maxA = block_colors[i].maxA;


		nb_blocks += BURST_SIZE;

		//if(nb_blocks >= 100) {
		//	sc_stop();
		//}
	}
}
