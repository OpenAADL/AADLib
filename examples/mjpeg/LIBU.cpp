// ***********************************************************************
//
// Filename : LIBU.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Jun 08 15:02:09 EDT 2011
//
//
// ***********************************************************************

#include "LIBU.h"



#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#define Y(x, i, j) Y[x][i * BLOCK_WIDTH + j]
#define Cb(i, j) Cb[i * BLOCK_WIDTH + j]
#define Cr(i, j) Cr[i * BLOCK_WIDTH + j]


void before_libu()
{
	WIDTH = 0;
    HEIGHT = 0;
    BLOCKS_W = 0;
    BLOCKS_H = 0;
    frameCnt = 0;
    offset = 0;
    Ready = 0;
    uiLastCommand = 0;

    hei = 0;
    temp=0;
}

///////////////////////////////////////////////////////////////////////////////
///
/// Thread
///
///////////////////////////////////////////////////////////////////////////////
void libu_funct(unsigned int nbFrames)
{
	SpacePrint("LIBU\n");
	// Variable
	

//	while(1) {
		// Reception des donnees dynamiquement
		//Read<unsigned int>(from_demux, &nbFrames);

		while(frameCnt < nbFrames)
		{
			// Read the command
			Read<unsigned int>(from_demux, &uiCommand);

			///
			///	HEADER
			///
			if (uiCommand == HEADER)
			{
				if (uiLastCommand == uiCommand)	// Received a header with no data, skip image
					frameCnt++;

				// Reception des attributs de l'image
				Read<unsigned int>(from_demux, &WIDTH);
				computeFor(1);
				Read<unsigned int>(from_demux, &HEIGHT);
				computeFor(1);
				Read<unsigned int>(from_demux, &BLOCKS_W);
				computeFor(1);
				Read<unsigned int>(from_demux, &BLOCKS_H);
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

				SpacePrint("Processing frame %d out of %d\n", frameCnt + 1, nbFrames);
				uiLastCommand = HEADER;
			}

			///
			///	DATA
			///
			if (uiCommand == DATA)
			{
				for(unsigned short macroLine = 0; macroLine < (BLOCKS_H / lumVi); ++macroLine)
				{
					// Load Ys, Cb and Cr tables
					for(unsigned short macroColumn = 0; macroColumn < (BLOCKS_W / lumHi); ++macroColumn)
					{
						int minR = 255, minG = 255, minB = 255, minA = 255;
						int maxR = 0, maxG = 0, maxB = 0, maxA = 0;
						int sumR = 0, sumG = 0, sumB = 0, sumA = 0;
						int nbPixels = 0;

						for(unsigned int vi_cnt = 0; vi_cnt < lumVi; ++vi_cnt)
						{
							for(unsigned int hi_cnt = 0; hi_cnt < lumHi; ++hi_cnt)
							{
								Read<SPACE_ALIGNED unsigned char>(from_idct, &Y[(vi_cnt * lumVi) + hi_cnt][0], BLOCK_SIZE);
								//block_metrics(sc_time_stamp().value());
								computeFor(1);
							}
						}

						if(nb_comp > 1) // color
						{
							Read<SPACE_ALIGNED unsigned char>(from_idct, &Cb[0], BLOCK_SIZE);
							//block_metrics(sc_time_stamp().value());

							computeFor(1);
							Read<SPACE_ALIGNED unsigned char>(from_idct, &Cr[0], BLOCK_SIZE);
							//block_metrics(sc_time_stamp().value());

							computeFor(1);

							for(unsigned int vi_cnt = 0; vi_cnt < lumVi; ++vi_cnt)
							{
								for(unsigned int hi_cnt = 0; hi_cnt < lumHi; ++hi_cnt)
								{
									for(int i = 0; i < BLOCK_HEIGHT; ++i)
									{
										for (int j = 0; j < BLOCK_WIDTH; ++j )
										{
											offset = 4 * (((lumVi * macroLine + vi_cnt) * BLOCK_HEIGHT * WIDTH) + (i * WIDTH) + (lumHi * macroColumn * BLOCK_WIDTH) + (hi_cnt * BLOCK_WIDTH) + j);
											if (WIDTH_VGA != WIDTH)
												offset += 4 * ((int)(offset / 4 / WIDTH))*(WIDTH_VGA-WIDTH); // padding to change line

											outputPixel = ycbcr2rgba(Y((vi_cnt * lumVi) + hi_cnt, i, j), Cb(((vi_cnt * BLOCK_HEIGHT + i) / lumVi), ((hi_cnt * BLOCK_WIDTH + j) / lumHi)), Cr(((vi_cnt * BLOCK_HEIGHT + i) / lumVi), ((hi_cnt * BLOCK_WIDTH + j) / lumHi)));
											DeviceWrite(to_vga, offset, &outputPixel, 1);

											int R = (outputPixel >> 0) & 0xFF;
											int G = (outputPixel >> 8) & 0xFF;
											int B = (outputPixel >> 16) & 0xFF;
											int A = (outputPixel >> 24) & 0xFF;

											sumR += R;
											sumG += G;
											sumB += B;
											sumA += A;

											if(R < minR) minR = R;
											if(G < minG) minG = G;
											if(B < minB) minB = B;
											if(A < minA) minA = A;

											if(R > maxR) maxR = R;
											if(G > maxG) maxG = G;
											if(B > maxB) maxB = B;
											if(A > maxA) maxA = A;

											nbPixels++;
										}
									}
								}
							}
						}
						else// grayscale
						{
							for(unsigned int vi_cnt = 0; vi_cnt < lumVi; ++vi_cnt)
							{
								for(unsigned int hi_cnt = 0; hi_cnt < lumHi; ++hi_cnt)
								{
									for(int i = 0; i < BLOCK_HEIGHT; ++i)
									{
										for (int j = 0; j < BLOCK_WIDTH; ++j )
										{
											offset = 4 * (((lumVi * macroLine + vi_cnt) * BLOCK_HEIGHT * WIDTH) + (i * WIDTH) + (lumHi * macroColumn * BLOCK_WIDTH) + (hi_cnt * BLOCK_WIDTH) + j);

											if (WIDTH_VGA != WIDTH)
												offset += 4 * ((int)(offset / 4 / WIDTH))*(WIDTH_VGA-WIDTH); // padding to change line

											outputPixel = grayscale2rgba(Y((vi_cnt * lumVi) + hi_cnt, i, j));
											DeviceWrite(to_vga, offset, &outputPixel, 1);

										}
									}
								}
							}
						}

						Write<int>(to_color_metrics, &minR);
						Write<int>(to_color_metrics, &minG);
						Write<int>(to_color_metrics, &minB);
						Write<int>(to_color_metrics, &minA);

						int avgR = sumR / nbPixels;
						int avgG = sumG / nbPixels;
						int avgB = sumB / nbPixels;
						int avgA = sumA / nbPixels;

						Write<int>(to_color_metrics, &avgR);
						Write<int>(to_color_metrics, &avgG);
						Write<int>(to_color_metrics, &avgB);
						Write<int>(to_color_metrics, &avgA);

						Write<int>(to_color_metrics, &maxR);
						Write<int>(to_color_metrics, &maxG);
						Write<int>(to_color_metrics, &maxB);
						Write<int>(to_color_metrics, &maxA);

						block_metrics(sc_time_stamp().value());
					}
				}

				// Indicate we have completed a frame
				++frameCnt;

				DeviceWrite(to_vga, FRAME_DONE, &frameCnt );

				// Wait for the VGAController to be ready for the next frame
				do
				{
					DeviceRead(from_vga, 0x00000000, &Ready );
				}
				while(Ready == 0);

				uiLastCommand = DATA;
			}
		}

		sc_stop();

	//}
}

void block_metrics(uint64_t value)
{
	//SpacePrint("LIBU RECEIVED block %llu\n", value);

	Write<Uint64_t>(to_block_metrics, &value, 1);
}

//
//  LIBU::ycbcr2rgba
//////////////////////////////////////////////////////////////////////////////
///
/// This function converts YCbCr values within a valid range of 0-255 to RGBA
/// values within a valid range of 0-255.
///
/// @param  =>  y : luma component
/// @param  =>  cb : blue-difference chroma components
/// @param  =>  cr : red-difference chroma components
///
/// @return =>  RGBA color conversion
//////////////////////////////////////////////////////////////////////////////
unsigned int ycbcr2rgba(unsigned char y, unsigned char cb, unsigned char cr)
{
	unsigned int RGBAWord;
	int R, G, B, A;

	R = (((y << 10) + 1436 * (cr - 128)) >> 10);
	G = (((y << 10) - 352  * (cb - 128) - 732 * (cr - 128)) >> 10);
	B = (((y << 10) + 1815 * (cb - 128)) >> 10);
	A = 255;

	if (R < 0)
		R = 0;
	else if (R > 255)
		R = 255;

	if (G < 0)
		G = 0;
	else if (G > 255)
		G = 255;

	if (B < 0)
		B = 0;
	else if (B > 255)
		B = 255;

	//
	// pixels are stored as such : 0xAABBGGRR
	//
	RGBAWord = A;
	RGBAWord <<= 8;
	RGBAWord |= B;
	RGBAWord <<= 8;
	RGBAWord |= G;
	RGBAWord <<= 8;
	RGBAWord |= R;

	return RGBAWord;
}


//
//  LIBU::grayscale2rgba
//////////////////////////////////////////////////////////////////////////////
///
/// This function converts YCbCr values within a valid range of 0-255 to RGBA
/// values within a valid range of 0-255.
///
/// @param  =>  y : luma component
///
/// @return =>  RGBA grayscale conversion
//////////////////////////////////////////////////////////////////////////////
unsigned int grayscale2rgba(unsigned char y)
{
	unsigned int RGBAWord;
	int R, G, B, A;

	R = y;
	G = y;
	B = y;
	A = 255;

	//
	// pixels are stored as such : 0xAABBGGRR
	//
	RGBAWord = A;
	RGBAWord <<= 8;
	RGBAWord |= B;
	RGBAWord <<= 8;
	RGBAWord |= G;
	RGBAWord <<= 8;
	RGBAWord |= R;

	return RGBAWord;
}
