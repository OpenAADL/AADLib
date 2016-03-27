// ***********************************************************************
//
// Filename : DEMUX.h
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:01:58 EDT 2011
//
//
// ***********************************************************************

#ifndef DEMUX_H
#define DEMUX_H

#include "jpeg.h"

// Typedef
typedef enum JPEGReaderState
{
	LookingForMarker,
	MarkerFound
} JPEGReaderState;


		
		


		// Thread
	    void demux_funct(void);
	    void before_demux(void);
		
	
		
		

		///
		/// Methods
		///
		unsigned short get_next_mk();
		void skip_segment();
		void find_info(void);
		unsigned char read_8_bits();
		unsigned short read_16_bits();
		void skip_bytes(unsigned short NbBytes);

		/// Variables
		///

		unsigned int m_nbFrames;
		unsigned int m_uiOffset;
		SPACE_ALIGNED unsigned char m_Buffer[4];
		bool m_BufferValid;

		unsigned int currentFrame;
		unsigned int dataMagic;
		unsigned short temp_mk;
		unsigned int header_size, height, width, nb_comp;
		unsigned int HiVi;

		unsigned char pot_mark;
		unsigned short mark;
		unsigned int found_mk, done, end_nb;

		unsigned short image_max_height;
		unsigned short image_max_width;
		unsigned int NBLOCKS, BLOCKS_H, BLOCKS_W, marker;
		unsigned int uiDummy;
		bool hasHuffTable;
		bool shouldSkip;
	

#endif
