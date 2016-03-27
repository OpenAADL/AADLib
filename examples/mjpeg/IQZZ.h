// ***********************************************************************
//
// Filename : IQZZ.h
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:02:04 EDT 2011
//
//
// ***********************************************************************

#ifndef IQZZ_H
#define IQZZ_H

#define MAX_Q_TABLE 3
#define Q_TABLE_SIZE 64


#include <jpeg.h>


		void iqzz_funct(unsigned int uiCommand, unsigned int nbQuant);
		unsigned int before_iqzz(unsigned int nbQuant);


		unsigned long m_uiOffset;
		unsigned char m_Buffer[4];
		bool m_BufferValid;
		unsigned char m_QuantizationTables[MAX_Q_TABLE][Q_TABLE_SIZE];

		SPACE_ALIGNED short in[BLOCK_SIZE];
		SPACE_ALIGNED short UnZZ[BLOCK_SIZE];
		unsigned int NBLOCKS;
		unsigned int nb_comp, HiVi[NB_MAX_COMP], Hi, Vi, selector;

		int nbQuantReal;
		int size;

		
		
		///
		/// Methods
		///
		void load_multi_quant_table(unsigned char QuantizationTables[MAX_Q_TABLE][Q_TABLE_SIZE], int nbQuant);
		void load_quant_table(unsigned char QuantizationTables[MAX_Q_TABLE][Q_TABLE_SIZE], unsigned short tableID);
		unsigned short read_16_bits();
		unsigned char read_8_bits();


#endif
