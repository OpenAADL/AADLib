// ***********************************************************************
//
// Filename : LIBU.h
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:02:09 EDT 2011
//
//
// ***********************************************************************

#ifndef LIBU_H
#define LIBU_H


#include "jpeg.h"

#include <stdint.h>


void libu_funct(unsigned int nbFrames);
void before_libu(void);
	    
	unsigned int WIDTH;
		unsigned int HEIGHT;
		unsigned int BLOCKS_W;
		unsigned int BLOCKS_H;

		unsigned int frameCnt;
		unsigned int nb_comp, HiVi[NB_MAX_COMP], lumHi, lumVi;
		SPACE_ALIGNED unsigned char Y[4][BLOCK_SIZE], Cb[BLOCK_SIZE], Cr[BLOCK_SIZE];
		int offset;
		unsigned int outputPixel;
		unsigned long Ready;
		unsigned int uiLastCommand;
		unsigned int uiCommand;


		int hei;
		int temp;

	    unsigned int ycbcr2rgba(unsigned char y, unsigned char cb, unsigned char cr);
	    unsigned int grayscale2rgba(unsigned char y);
		void block_metrics(uint64_t value);

};

#endif
