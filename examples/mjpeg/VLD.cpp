// ***********************************************************************
//
// Filename : VLD.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:02:18 EDT 2011
//
//
// ***********************************************************************

#include "VLD.h"



// Varaible gloable
static int nb_consecutive_ff;

#define HUFF_EOB                0x00
#define HUFF_ZRL                0xF0

#define __STDC_FORMAT_MACROS
#include <inttypes.h>



unsigned int before_vld(unsigned int nbHuff)
{
	tmp = 0;
    cmp = 0;
    nothing = 0;
    x_size = 0;
    y_size = 0;
    nb_comp = 0;
    left = 0;
    picture_no = 0;
    mx_size = 0;
    my_size = 0;
    rx_picture_no = 0; // modif
    magic = 0;
    i  = 0;
    bContinue = false;
	computeFor(1);
	return nbHuff;
}
///////////////////////////////////////////////////////////////////////////////
///
/// Thread
///
///////////////////////////////////////////////////////////////////////////////
void vld_funct(unsigned int uiCommand, unsigned int nbHuff)
{
	SpacePrint("VLD\n");
	// Variables
	
//	unsigned int uiCommand;
	unsigned int uiHasTable;
	unsigned int blockCnt = 0;

	// On lit le nombre de table de Huffman
	//Read<unsigned int>(from_demux, &nbHuff);
	//computeFor(1);

	//uint64_t time_resolution = sc_time_stamp().sc_get_time_resolution()
	//Write(BLOCK_METRICS_ID, &time_resolution, 1);
	
   // Boucle
//	while(1)
//	{
		// Read the command
//		Read<unsigned int>(from_demux, &uiCommand);
		
		///
		/// HEADER
		///
		if (uiCommand == HEADER)
		{
			// Init
			bContinue = false;

		    /* This code can help if we want to tolerate desynchronizations */
		    do
		    {
		    	// Reception du marqueur MAGIC
				Read<unsigned int>(from_demux, &magic);
				computeFor(1);

		        // On s'assure qu'on a bien recu le marqueur
		        if ( magic == DATA_MAGIC )
		        {
		            // On indique qu'on veut poursuivre le traitement
		            bContinue = true;
		        }
		        else
		        	SpacePrint("VLD : (WARNING) Aucune reception du marqueur MAGIC\n");

		    } while (!bContinue);

		    // On passe a la prochaine image
		    picture_no++;

		    // On recoit le numero de l'image
			Read<unsigned int>(from_demux, &rx_picture_no);
			computeFor(1);

			// On s'assure qu'on a bien recu la bonne image
		    if ( rx_picture_no != picture_no )
		        picture_no = rx_picture_no;

			/* Get SOF info from Demux */
			Read<unsigned int>(from_demux, &x_size);
			computeFor(1);
			Read<unsigned int>(from_demux, &y_size);
			computeFor(1);
			Read<unsigned int>(from_demux, &nb_comp);
			computeFor(1);

			for(unsigned int comp_cnt = 0; comp_cnt < nb_comp; ++comp_cnt)
			{
				Read<unsigned int>(from_demux, &HiVi[comp_cnt]);
				computeFor(1);
			}

			lumHi = first_quad(HiVi[0] >> 8);
			lumVi = second_quad(HiVi[0] >> 8);

		    mx_size = intceil(x_size, BLOCK_WIDTH);
		    my_size = intceil(y_size, BLOCK_HEIGHT);

			// Determine if there is a huffman table
			Read<unsigned int>(from_demux, &uiHasTable);
			computeFor(1);

			if (uiHasTable == HAS_TABLE)
			{
				/* Load Huffman Tables */
				huff_tables_init(&huff);
				for(i = 0; i < nbHuff; i++)
				{
					huff_load_tables(&huff);
					computeFor(1);

					if (i < nbHuff-1)
					{
						Read<unsigned int>(from_demux, &uiHasTable);
						computeFor(1);
					}
				}
			}
		}



		///
		/// Start of scan
		///
		if (uiCommand == DATA)
		{
			// Skip 2 bytes
			Read<unsigned int>(from_demux, &nothing);
			computeFor(1);
			Read<unsigned int>(from_demux, &nothing);
			computeFor(1);
			Read<unsigned int>(from_demux, &tmp);
			computeFor(1);

			Read<unsigned int>(from_demux, &cmp);
			computeFor(1);
			Read<unsigned int>(from_demux, &tmp);
			computeFor(1);

			comp.DC_HT = first_quad(tmp);
			comp.AC_HT = second_quad(tmp);

			if(nb_comp > 1)
			{
				// Second component
				Read<unsigned int>(from_demux, &cmp);

				computeFor(1);
				Read<unsigned int>(from_demux, &tmp);

				computeFor(1);

				compCb.DC_HT = first_quad(tmp);
				compCb.AC_HT = second_quad(tmp);

				// Third component
				Read<unsigned int>(from_demux, &cmp);

				computeFor(1);
				Read<unsigned int>(from_demux, &tmp);

				computeFor(1);

				compCr.DC_HT = first_quad(tmp);
				compCr.AC_HT = second_quad(tmp);
			}

			// Skip 3 bytes;
			Read<unsigned int>(from_demux, &nothing);

			computeFor(1);
			Read<unsigned int>(from_demux, &nothing);

			computeFor(1);
			Read<unsigned int>(from_demux, &nothing);

			computeFor(1);

			bitreader_init(&bits);
			comp.PRED = 0;
			compCb.PRED = 0;
			compCr.PRED = 0;

			left = mx_size*my_size;

			// Boucle
			while (left > 0)
			{
				blockCnt++;
			    block_metrics( blockCnt, sc_time_stamp().value());

				for(unsigned int vi_cnt = 0; vi_cnt < lumVi; ++vi_cnt)
				{
					for(unsigned int hi_cnt = 0; hi_cnt < lumHi; ++hi_cnt)
					{
						vld_decode_unpack_block(&bits, 1, &huff, &comp);
						--left;
						computeFor(1);
					}
				}

				if(nb_comp > 1)
				{
					vld_decode_unpack_block(&bits, 0, &huff, &compCb);
					vld_decode_unpack_block(&bits, 0, &huff, &compCr);
					computeFor(1);
				}

				computeFor(1);
			}
		}
//	}
}


///////////////////////////////////////////////////////////////////////////////
///
/// check_ff
///
///////////////////////////////////////////////////////////////////////////////
void check_ff(unsigned char value)
{
    if (value == 0xff) 
        nb_consecutive_ff++;
    else 
        nb_consecutive_ff = 0;
}


///////////////////////////////////////////////////////////////////////////////
///
/// utility and counter to return the number of bits from file right aligned, masked, first bit towards MSB's
///
///////////////////////////////////////////////////////////////////////////////
unsigned int bitreader_get(bitreader_context *cont, int number)
{
    unsigned int ret = 0;

    if (cont->available)
        cont->current &= (1<<cont->available)-1;

    while (number) 
    {
        if ( cont->available == 0 ) 
        {
			computeFor(1);
        	unsigned int value;
			Read<unsigned int>(from_demux, &value);
			computeFor(1);
			cont->current = value;
            cont->available = 8;
        }
        
        if ( number == cont->available ) 
        {
			computeFor(1);
            cont->available = 0;
            ret = (ret<<number) | cont->current;
            break;
        }
        
        if ( number < cont->available ) 
        {
			computeFor(1);
            ret = (ret<<number) | (cont->current>>(cont->available-number));
            cont->available -= number;
            break;
        }
        
        if ( number > cont->available ) 
        {
			computeFor(1);
            ret = (ret<<cont->available) | cont->current;
            number -= cont->available;
            cont->available = 0;
        }
    }

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
///
/// bitreader_get_one
///
///////////////////////////////////////////////////////////////////////////////
unsigned char bitreader_get_one(bitreader_context *cont)
{
    unsigned int ret = 0, tmp;

    if ( cont->available == 0 ) 
    {     
    	unsigned int value;
    	
		Read<unsigned int>(from_demux, &value);
		computeFor(1);

		cont->current = value;
        check_ff(cont->current);
        cont->available = 7;
    } else
        --(cont->available);
        
    tmp = 1<<(cont->available);
    ret = !!(cont->current&tmp);

	computeFor(1);

    return ret;
}


///////////////////////////////////////////////////////////////////////////////
///
/// bitreader_clear
///
///////////////////////////////////////////////////////////////////////////////
void bitreader_clear(bitreader_context *cont)
{
    cont->available = 0;
    nb_consecutive_ff = 0;
}


///////////////////////////////////////////////////////////////////////////////
///
/// bitreader_init
///
///////////////////////////////////////////////////////////////////////////////
void bitreader_init(bitreader_context *cont)
{
    cont->available = 0;
    cont->current = 0;
    nb_consecutive_ff = 0;
}


///////////////////////////////////////////////////////////////////////////////
///
/// huffman table initialization
///
///////////////////////////////////////////////////////////////////////////////
void huff_tables_init( huff_context *cont )
{
    int i, j;

    for ( j=0; j<16; ++j ) 
    {
        for ( i=0; i<4; ++i ) 
        {
            cont->MinCode[i][j] = 0;
            cont->MaxCode[i][j] = 0;
            cont->ValPtr[i][j] = 0;
        }
        cont->DC_Table0[j] = 0;
        cont->AC_Table0[j] = 0;
        cont->DC_Table1[j] = 0;
        cont->AC_Table1[j] = 0;
    }
    cont->HTable[0] = cont->DC_Table0;
    cont->HTable[1] = cont->DC_Table1;
    cont->HTable[2] = cont->AC_Table0;
    cont->HTable[3] = cont->AC_Table1;
	
	computeFor(1);
}

//////////////////////////////////////////////////////////////////////////////
///
///	Lit deux octet
///
//////////////////////////////////////////////////////////////////////////////
unsigned short read_16_bits()
{
	unsigned short value;
	unsigned char reader1;
	unsigned char reader2;

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
        	SpacePrint("Error in VLD");
	}

	inputValue = m_Buffer[alignment];

	m_uiOffset++;

	computeFor(1);
	
	return inputValue;
}


///////////////////////////////////////////////////////////////////////////////
///
/// Loading of Huffman table, with leaves drop ability
///
///////////////////////////////////////////////////////////////////////////////
int huff_load_tables(huff_context *cont)
{
	// Variable
	unsigned int aux = 0, buf = 0, nothing = 0;
	int classe = 0, id = 0, max = 0, LeavesN = 0, LeavesT = 0, i = 0, AuxCode = 0, size = 0;
	
	m_uiOffset = 0;
	m_BufferValid = false;

	Read<unsigned int>(from_demux, &m_uiOffset);
	computeFor(1);

	// Enleve les deux bytes indiquant la taille de la table de Huffman
	size = read_16_bits() - 2;

	// Reception de la table de Huffman
	while ( size > 0 )
	{
		computeFor(1);
		
		// Reception du byte auxiliere
		aux = read_8_bits();

		// First quad
		classe = first_quad(aux);

		// Table no
		id = second_quad(aux);

		if (id > 1)
			SpacePrint("ERROR: Bad HTable identity %d!\n", id);

		id = HUFF_ID(classe, id);

		if (id > 3)
			SpacePrint("ERROR: Bad computed HTable identity %d!\n", id);

		// Decremente la taille restante
		--size;

		// Initialisation
		LeavesT = 0;
		AuxCode = 0;

		// Reception de la table
		for ( i=0; i<16; i++ )
		{
			buf = read_8_bits();
			LeavesN = buf;
			cont->ValPtr[id][i] = LeavesT;
			cont->MinCode[id][i] = AuxCode<<1;
			AuxCode = cont->MinCode[id][i] + LeavesN;
			cont->MaxCode[id][i] = (LeavesN) ? (AuxCode - 1) : (-1);
			LeavesT += LeavesN;
		}

		// Decremente la taille restante
		size -= 16;

		// Verification
		if ( LeavesT > MAX_SIZE(classe) )
			max = MAX_SIZE(classe);
		else
			max = LeavesT;



		// Boucle
		for ( i=0; i<max; ++i )
		{
			/* get huffman table */
			buf = read_8_bits();
			cont->HTable[id][i] = buf;
		}

		// Skip
		for ( i=max; i<LeavesT; ++i )
			nothing = read_8_bits();

		// Decremente la taille restante
		size -= LeavesT;
	}

	// Retourne
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
///
/// extract a single symbol from file using specified huffman table
///
///////////////////////////////////////////////////////////////////////////////
int huff_get_symbol( bitreader_context *cont, huff_context *huff, int select )
{
    long code = 0;
    int length = 0,  index = 0;

    for ( length=0; length<16; ++length ) 
    {
        code = (code<<1) | bitreader_get_one( cont );

        if (code <= huff->MaxCode[select][length])
            break;
    }
    
    index = huff->ValPtr[select][length] + code - huff->MinCode[select][length];

    if (index < MAX_SIZE(select / 2))
        return huff->HTable[select][index];

    SpacePrint("ERROR: Overflowing symbol table with index 0x%x !\n", index);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///
/// intceil
///
///////////////////////////////////////////////////////////////////////////////
int intceil(int N, int D)
{
    return (N+D-1)/D;
}


///////////////////////////////////////////////////////////////////////////////
///
/// transform JPEG number format into usual 2's complement format
///
///////////////////////////////////////////////////////////////////////////////
long reformat(unsigned int S, int good)
{
    unsigned int ext, sign;

    if (!good)
        return 0;
    sign = !((1<<(good-1))&(S));
    ext = 0-(sign<<good);
    return (S|ext)+sign;
}


///////////////////////////////////////////////////////////////////////////////
///
/// here we unpack a 8x8 DCT block
///
///////////////////////////////////////////////////////////////////////////////
void vld_decode_unpack_block( bitreader_context *bits, char mustOutput, huff_context *huff, cd_t *comp)
{
	// Variable
	unsigned char symbol;
	SPACE_ALIGNED short T[BLOCK_SIZE];
	unsigned int temp, i, run, cat;
	int value;
	
	// Initialisation
    for (i = 0; i < BLOCK_SIZE; i++)
        T[i] = 0;
		
	computeFor(1);
		
    /* first get the DC coefficient */
    symbol = huff_get_symbol( bits, huff, HUFF_ID(DC_CLASS,comp->DC_HT) );
    temp = bitreader_get( bits, symbol );
    value = reformat( temp, symbol );
    value += comp->PRED;
    comp->PRED = value;

	 /* reoganize and unquantify -> move to ZZ and IQ  */
    T[0] = value;

	 /* then the AC ones if symbol found is EOB and process not finish, missing values are replaced by zero  */
    for ( i=1; i<BLOCK_SIZE; i++ ) 
    {
        symbol = huff_get_symbol( bits, huff, HUFF_ID(AC_CLASS,comp->AC_HT) );
        
        if (symbol == HUFF_EOB)
            break;
			
        if (symbol == HUFF_ZRL) 
        {            
            i += 15;
            continue;
        }
        
        cat = symbol & 0xf;
        run = symbol >> 4;
        i += run;
        temp = bitreader_get( bits, cat );
        value = reformat( temp, cat );
        T[i] = value;
    }

	Write<SPACE_ALIGNED short>(to_iqzz, &T[0], BLOCK_SIZE);
	computeFor(1);
}

void block_metrics(unsigned int blockCnt, uint64_t value)
{
	vld_metrics metrics;
	metrics.block_count = blockCnt;
	metrics.time_start = value;
	Write<vld_metrics>(to_block_metrics, &metrics, 1);
}
