// ***********************************************************************
//
// Filename : BLOCK_METRICS.h
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Sep 11 12:06:11 EDT 2013
//
//
// ***********************************************************************

#ifndef BLOCK_METRICS_H
#define BLOCK_METRICS_H


#include "SpaceBaseModule.h"

#include <stdint.h>


	double to_mseconds(uint64_t value);

	// Thread
	void metrics();
	
private:
	
    uint64_t m_time_resolution;
	

#endif
