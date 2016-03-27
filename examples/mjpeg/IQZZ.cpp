// ***********************************************************************
//
// Filename : IQZZ.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:02:04 EDT 2011
//
//
// ***********************************************************************

#include "IQZZ.h"



// Table static
static const unsigned char G_ZZ[64] = {
    0, 1, 8, 16, 9, 2, 3, 10,
    17, 24, 32, 25, 18, 11, 4, 5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13, 6, 7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
};


//int before_iqzz()
//{
//	int nbQuant = 0;
//	Read<unsigned int>(from_demux, &nbQuant);	// get the number quantization table   SOLUTION A TROUVER POUR AVANT LE WHILE

//	if(nbQuant > 3)
//		SpacePrint("JPEG encoding not supported\n");
//	return nbQuant;
//}

unsigned int before_iqzz(unsigned int nbQuant)
{
	NBLOCKS = 0;

                	nbQuantReal = 0;
                	size = 0;
	if(nbQuant > 3)
		SpacePrint("JPEG encoding not supported\n");
	return nbQuant;
}


void iqzz_funct(unsigned int uiCommand, unsigned int nbQuant)
{
	SpacePrint("IQZZ\n");

//	unsigned int uiCommand;

/*	ModuleRead<unsigned int>(from_demux, &nbQuant);	// get the number quantization table   SOLUTION A TROUVER POUR AVANT LE WHILE

	if(nbQuant > 3)
		SpacePrint("JPEG encoding not supported\n");*/

	//while(1)
	//{
		// Read the command
		//ModuleRead<unsigned int>(from_demux, &uiCommand);
		computeFor(1);

		///
		///	HEADER
		///
		if (uiCommand == HEADER)
		{
			Read<unsigned int>(from_demux, &NBLOCKS);
			computeFor(1);
			Read<unsigned int>(from_demux, &nb_comp);
			computeFor(1);

			for(unsigned int comp_cnt = 0; comp_cnt < nb_comp; ++comp_cnt)
			{
				Read<unsigned int>(from_demux, &HiVi[comp_cnt]);
				computeFor(1);
			}
		}

		///
		///	QUANTIFICATION TABLE
		///
		if (uiCommand == HAS_TABLE)
		{
			// load quantization tables
			if(nbQuant == 1)
			{
				m_BufferValid = false;
				Read<unsigned int>(from_demux, &m_uiOffset);
				computeFor(1);
				size = read_16_bits();
				nbQuantReal = (size - 2) / 65; // check if the tables are concatenated: nbQuant = (totalSize - 2BytesSize) / tableSize

				load_multi_quant_table(m_QuantizationTables, nbQuantReal);
			}
			else
			{
				nbQuantReal = nbQuant;

				for(int i = 0; i < nbQuantReal; ++i)
				{
					load_quant_table(m_QuantizationTables, i);

					if (i<nbQuantReal-1)
					{
						Read<unsigned int>(from_demux, &uiCommand);
						computeFor(1);
					}
				}
			}
		}

		///
		///	DATA
		///
		if (uiCommand == DATA)
		{
			while(NBLOCKS > 0)
			{
				for(unsigned int comp_cnt = 0; comp_cnt < nb_comp; ++comp_cnt)
				{
					selector = (HiVi[comp_cnt] & 0xFF);
					Hi = first_quad(HiVi[comp_cnt] >> 8);
					Vi = second_quad(HiVi[comp_cnt] >> 8);

					for(unsigned int vi_cnt = 0; vi_cnt < Vi; ++vi_cnt)
						for(unsigned int hi_cnt = 0; hi_cnt < Hi; ++hi_cnt)
						{
							Read<SPACE_ALIGNED short>(from_vld, &in[0], BLOCK_SIZE);
							computeFor(5);

							for (unsigned int k = 0; k < BLOCK_SIZE; ++k)
								UnZZ[G_ZZ[k]] = in[k] * m_QuantizationTables[selector][k];

							Write<SPACE_ALIGNED short>(to_idct, &UnZZ[0], BLOCK_SIZE);
							computeFor(1);

							if(comp_cnt == 0)
								NBLOCKS--;
						}
				}
			}
		}
	
}


///////////////////////////////////////////////////////////////////////////////
///
/// load_multi_quant_table
///
///////////////////////////////////////////////////////////////////////////////
void load_multi_quant_table(unsigned char QuantizationTables[MAX_Q_TABLE][Q_TABLE_SIZE], int nbQuant)
{
	m_BufferValid = false;

	// read the quantization table
	for(int i = 0; i < nbQuant; ++i)
	{
		// Ignore the element precision & destination identifier
		read_8_bits();

		for(int j = 0; j < Q_TABLE_SIZE; ++j)
			QuantizationTables[i][j] = read_8_bits();
	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// load_quant_tables
///
///////////////////////////////////////////////////////////////////////////////
void load_quant_table(unsigned char QuantizationTables[MAX_Q_TABLE][Q_TABLE_SIZE], unsigned short tableID)
{
	m_uiOffset = 0;
	m_BufferValid = false;

	Read<unsigned int>(from_demux, &m_uiOffset); // get the quantization table address
	computeFor(1);

	// Ignore table length (first 2 bytes) and the element precision & destination identifier (last byte)
	read_8_bits();
	read_8_bits();
	read_8_bits();

	// read the quantization table
	for(int i = 0; i < Q_TABLE_SIZE; ++i)
		QuantizationTables[tableID][i] = read_8_bits();
}


//////////////////////////////////////////////////////////////////////////////
///
///	Lit deux octet
///
//////////////////////////////////////////////////////////////////////////////
unsigned short read_16_bits()
{
	unsigned short value;
	unsigned char reader1 = 0;
	unsigned char reader2 = 0;

	reader1 = read_8_bits();
	reader2 = read_8_bits();

	value = reader1 << 8;
	value = value | reader2;

	computeFor(1);
	
	return (value);
}


//////////////////////////////////////////////////////////////////////////////
///
///	Lit un octet
///
//////////////////////////////////////////////////////////////////////////////
unsigned char read_8_bits()
{
	unsigned char inputValue;

	unsigned char alignment = (m_uiOffset & 0x3);
	
	// Address is a multiple of 4: need to read a new word from memory
	if (alignment == 0 || !m_BufferValid) 
	{
		eSpaceStatus eStatus = DeviceRead(XILINXBRAM1_ID, m_uiOffset & 0xFFFFFFFC, &m_Buffer[0], 4);

        if(eStatus == SPACE_OK)
        	m_BufferValid = true;
        else
        	SpacePrint("Error in IQZZ");
	}

	inputValue = m_Buffer[alignment];
	
	m_uiOffset++;

	computeFor(1);
	return inputValue;
}
