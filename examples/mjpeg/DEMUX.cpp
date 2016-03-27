// ***********************************************************************
//
// Filename : DEMUX.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:01:58 EDT 2011
//
//
// ***********************************************************************

#include "DEMUX.h"
#include <stdio.h>

void before_demux()
{
	currentFrame = 0;
	dataMagic = DATA_MAGIC;
	temp_mk = 0;
	header_size = 0;
	height = 0;
	width = 0;
	nb_comp = 0;

		pot_mark = 0;
		mark = 0;
		found_mk = 0;
		done = 0;
		end_nb = 0;

		image_max_height = 0;
		image_max_width = 0;
		NBLOCKS = 0;
		BLOCKS_H = 0;
		BLOCKS_W = 0;
		marker = 0;
		hasHuffTable = false;
		shouldSkip = true;
}


///////////////////////////////////////////////////////////////////////////////
///
/// Thread
///
///////////////////////////////////////////////////////////////////////////////
void demux_funct(void)
{

	

	SpacePrint("DEMUX\n");


		find_info();

		// Boucle toutes les images
		while(currentFrame < m_nbFrames)
		{
			hasHuffTable = false;
			shouldSkip = true;

			// go to the next "start of image" marker
			while(temp_mk != SOI_MK)
			{
				temp_mk = get_next_mk();
			}

			// Initialisation
			found_mk = 0;
			done = 0;
			
			while (!done)
			{
				// On boucle tant qu'on n'a pas trouve un marqueur
				if (!found_mk)
					mark = get_next_mk();

				// process the new marker
				switch (mark)
				{
					// "start of frame" marker
					case SOF_MK:

						// Tells other modules they should be expecting a header
						uiDummy = HEADER;
						Write<unsigned int>(to_vld, &uiDummy);
						Write<unsigned int>(to_iqzz, &uiDummy);
						Write<unsigned int>(to_idct, &uiDummy);
						Write<unsigned int>(to_libu, &uiDummy);

						currentFrame++;

						header_size = read_16_bits(); // header size
						read_8_bits();                // precision, but we ignore it
						height = read_16_bits();      // image height
						width = read_16_bits();       // image width
						nb_comp = read_8_bits();      // nb of components

						// Set global image attributes and diffuse to others core modules
						image_max_width = ROUND_UP(width, BLOCK_WIDTH);
						image_max_height = ROUND_UP(height, BLOCK_WIDTH);
						BLOCKS_W = (image_max_width/BLOCK_WIDTH);
						BLOCKS_H = (image_max_height/BLOCK_HEIGHT);
						NBLOCKS = (BLOCKS_H*BLOCKS_W);
		
						// send some more info for synchronisation
						Write<unsigned int>(to_vld, &dataMagic);
						computeFor(1);
						Write<unsigned int>(to_vld, &currentFrame);
						computeFor(1);

						Write<unsigned int>(to_vld, &width);
						computeFor(1);
						Write<unsigned int>(to_vld, &height);
						computeFor(1);
						Write<unsigned int>(to_vld, &nb_comp);
						computeFor(1);

						Write<unsigned int>(to_iqzz, &NBLOCKS);
						computeFor(1);
						Write<unsigned int>(to_iqzz, &nb_comp);
						computeFor(1);

						Write<unsigned int>(to_idct, &NBLOCKS);
						computeFor(1);

						Write<unsigned int>(to_libu, &width);
						computeFor(1);
						Write<unsigned int>(to_libu, &height);
						computeFor(1);
						Write<unsigned int>(to_libu, &BLOCKS_W);
						computeFor(1);
						Write<unsigned int>(to_libu, &BLOCKS_H);
						computeFor(1);
						Write<unsigned int>(to_libu, &nb_comp);
						computeFor(1);

						for (unsigned int i = 0; i < nb_comp; ++i)
						{
							read_8_bits(); // ignoring component ID (it's always sorted anyway: 1, 2, 3)
							HiVi = read_16_bits(); // HiVi (1 byte) + Selector (1 byte)
							Write<unsigned int>(to_vld, &HiVi);
							computeFor(1);
							Write<unsigned int>(to_iqzz, &HiVi);
							computeFor(1);
							Write<unsigned int>(to_libu, &HiVi);
							computeFor(1);
						}
						computeFor(1);

					break;

					// Huffman table marker
					case DHT_MK:

						hasHuffTable = true;
						uiDummy = HAS_TABLE;
						Write<unsigned int>(to_vld, &uiDummy);

						Write<unsigned int>(to_vld, &m_uiOffset); // Huffman table is found, sending address to VLD module
						computeFor(1);
						skip_segment(); // skip the rest of the DHT segment (VLD will load the table)
						computeFor(1);
						break;

					// quantization table marker
					case DQT_MK:

						uiDummy = HAS_TABLE;
						Write<unsigned int>(to_iqzz, &uiDummy);

						Write<unsigned int>(to_iqzz, &m_uiOffset); // quantization table is found, sending address to IQZZ module
						computeFor(1);
						skip_segment(); // skip the rest of the DQT segment (IQZZ will load the table)
						computeFor(1);
						break;

					// RESTART INTERVAL MARKER
					case DRI_MK:
						/* skip sizes */
						read_8_bits();
						read_8_bits();
						read_8_bits();
						read_8_bits();
						computeFor(1);
						break;
			
					// START OF SCAN
					case SOS_MK:

						if (!hasHuffTable)
						{
							uiDummy = !HAS_TABLE;
							Write<unsigned int>(to_vld, &uiDummy);
						}

						if (shouldSkip)
							break;

						// Tell other module they should be expecting data
						uiDummy = DATA;
						Write<unsigned int>(to_vld, &uiDummy);
						Write<unsigned int>(to_iqzz, &uiDummy);
						Write<unsigned int>(to_idct, &uiDummy);
						Write<unsigned int>(to_libu, &uiDummy);

						// Initialisation
						found_mk = 0;

						// On boucle tant qu'on n'a pas trouve un marqueur
						while (!found_mk)
						{
							marker = read_8_bits();

							//Devrait seulement arriver a EOI marker
							if (marker == 0xff)
							{
								pot_mark = read_8_bits();

								if (pot_mark == 0)
								{
									unsigned int ff = 0xff;
									Write<unsigned int>(to_vld, &ff);
									//SpacePrint("1 DEMUX - %d \n",ff);
									computeFor(1);
								}
								else
								{
									mark = 0xff00|pot_mark;
									found_mk = 1;

								}
							}
							else /* buf isn't 0xff */
							{
								Write<unsigned int>(to_vld, &marker);
								//SpacePrint("2 DEMUX - %d \n",marker);
								computeFor(1);
							}
						}

						break;

					// END OF IMAGE MARKER
					case EOI_MK:

						// Indique la fin de l'image
						done = 1;
						computeFor(1);
						break;

					// COMMMENT MARKER
					case COM_MK:

						skip_segment();
						computeFor(1);
						break;
	
					// Traitement par defaut
					default:
						if ((mark&MK_MSK) == APP_MK)
						{
							shouldSkip = false;
							skip_segment();	// On passe au prochain segment
							computeFor(1);
						}
						else if (RST_MK(mark))
						{
							computeFor(1);
							break;
						}
						else
						{
							done = 1;
							++end_nb;
							computeFor(1);
							break;
						}
				}
			}
		}

		// Let LIBU process all frames
		while(1)
		{
			computeFor(1);
		}
	
}

// DEMUX::get_next_mk
// ***********************************************************************
///
/// get_next_mk : returns the next marker in the MJPEGRAM (input image file)
///
/// @return =>  one byte of data
///
// ***********************************************************************
unsigned short get_next_mk()
{
    unsigned char buffer = 0x00;
    unsigned short returnValue;
    
    while(buffer != 0xFF)
    {
    	buffer = read_8_bits();
    }

    buffer = read_8_bits();
    returnValue = 0xFF00 | buffer;

    return returnValue;
}


///////////////////////////////////////////////////////////////////////////////
///
/// skip_segment  -- Permet d'ignorer le segment en cours
///
///////////////////////////////////////////////////////////////////////////////
void skip_segment()
{
	unsigned short size = 0;
	
	// On lit la taille du segment (On enleve les 2 bytes pour la taille)
    size = read_16_bits() - 2;

	// On saute
	skip_bytes(size);
}


//////////////////////////////////////////////////////////////////////////////
///
///	Determine les informations dynamiquement
///
//////////////////////////////////////////////////////////////////////////////
void find_info(void)
{
	// Variable
	m_nbFrames = 0;
	unsigned int nbHuff = 0;
	unsigned int nbQuant = 0;
	unsigned char buffer;
	/*	
	// On se met en etat initial
	JPEGReaderState state = LookingForMarker;
	
	//On passe au travers du tableau de donnees lues
	for(int i = 0; i < TAILLE_FICHIER; i++)
	{
		buffer = read_8_bits();
		
		// On verifie si l'on cherche un marker et si c'est le cas si s'en est un
		if(state == LookingForMarker && buffer == 0xFF)
		{
			//On indique que nous avons trouve le marker
			state = MarkerFound;
		}
		// Sinon on verifie si le caractere precedent etait un marker et si nous avons un begin of frame
		else if(state == MarkerFound && buffer == 0xC0)
		{
			// On incremente le nombre de frame
			m_nbFrames++;
			
			// On se remet en recherche d'un marker
			state = LookingForMarker;
		}
		// Sinon on verifie si nous sommes au premier frame si nous avons un debut de table d'huffman (pour les compters)
		else if(m_nbFrames == 1 && state == MarkerFound && buffer == 0xC4)
		{
			// On incremente le nombre de table d'huffman
			nbHuff++;
			
			// On se remet en recherche d'un marker
			state = LookingForMarker;
		}
		else if(m_nbFrames == 1 && state == MarkerFound && buffer == 0xDB)
		{
			// On incremente le nombre de table quantification
			nbQuant++;

			// On se remet en recherche d'un marker
			state = LookingForMarker;
		}
		else
		{
			// On se remet en recherche d'un marker
			state = LookingForMarker;
		}
	}
*/
	m_nbFrames = 3;
	nbHuff = 1;
	nbQuant = 1;
	
	// Envoie les donnees aux modules
	Write<unsigned int>(to_libu, &m_nbFrames);
	computeFor(1);
	Write<unsigned int>(to_vld, &nbHuff);
	computeFor(1);
	Write<unsigned int>(to_iqzz, &nbQuant);
	computeFor(1);

	// On remet le pointeur au debut du fichier
	m_uiOffset = 0;
}


// DEMUX::read_8_bits
// ***********************************************************************
///
/// read_8_bits : reads one byte from the MJPEGRAM (input image file)
///
/// @return =>  one byte of data
///
// ***********************************************************************
unsigned char read_8_bits()
{
	unsigned char returnValue;
	unsigned char byteAlignment = (m_uiOffset & 0x3);
	
	// if the address is a multiple of 4 or if the buffer value is not valid,
	// we need to read a new word (4 bytes) from memory
	if (byteAlignment == 0 || !m_BufferValid)
	{
		eSpaceStatus eStatus = DeviceRead(XILINXBRAM1_ID, m_uiOffset & 0xFFFFFFFC, &m_Buffer[0], 4);

        if(eStatus == SPACE_OK)
        {
        	m_BufferValid = true;
        }
        else
        {
        	SpacePrint("DEMUX::read_8_bits - Error\n");
        	m_BufferValid = false;
        }
	}

	returnValue = m_Buffer[byteAlignment];

	m_uiOffset++; // increase offset to next byte

	computeFor(1);
	
	return returnValue;
}


// DEMUX::read_16_bits
// ***********************************************************************
///
/// read_8_bits : reads two bytes from the MJPEGRAM (input image file)
///
/// @return =>  two bytes of data
///
// ***********************************************************************
unsigned short read_16_bits()
{
	unsigned short returnValue;
	unsigned char buffer_1;
	unsigned char buffer_2;


	buffer_1 = read_8_bits();
	buffer_2 = read_8_bits();

	returnValue = buffer_1 << 8;
	returnValue |= buffer_2;

	computeFor(1);
	
	return (returnValue);
}


//////////////////////////////////////////////////////////////////////////////
///
///	Saute des octets
///
//////////////////////////////////////////////////////////////////////////////
void skip_bytes(unsigned short NbBytes)
{
	m_uiOffset+=NbBytes;
	m_BufferValid = false;
}
