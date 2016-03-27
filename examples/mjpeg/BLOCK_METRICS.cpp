// ***********************************************************************
//
// Filename : BLOCK_METRICS.cpp
//
// Author : SpaceStudio generation engine
//
// Creation date : Wed Sep 11 12:06:11 EDT 2013
//
//
// ***********************************************************************

#include "BLOCK_METRICS.h"


#define __STDC_FORMAT_MACROS
#include <inttypes.h>



#define BURST_SIZE 25


void metrics()
{
	uint64_t time_start = 0;
	uint64_t time_start_block_one = 0;
	uint64_t time_end = 0;
	uint64_t latency_total = 0;
	uint64_t latency_avg = 0;
	double throughput = 0;
	unsigned int blockCnt = 0;

	SpacePrint( "BLOCK_METRICS\n" );
	m_time_resolution = 1000; //ps

	//ModuleRead(VLD_ID, SPACE_WAIT_FOREVER, &m_time_resolution, 1);
	//SpacePrint("BLOCK_METRICS %"PRId64" \n", m_time_resolution);


		vld_metrics metrics_start[BURST_SIZE];
		uint64_t time_ends[BURST_SIZE];
		Read<vld_metrics>(from_vld, metrics_start, BURST_SIZE);
		Read<uint64_t>(from_libu, time_ends, BURST_SIZE);

		for(unsigned int i=0;i<BURST_SIZE;i++) {
			blockCnt = metrics_start[i].block_count;
			time_start = metrics_start[i].time_start;
			time_end = time_ends[i];

			uint64_t latency_one = time_end - time_start;
			latency_total += latency_one;
			latency_avg = latency_total / blockCnt;

			if(blockCnt == 1)
				time_start_block_one = time_start;

			throughput = blockCnt / to_mseconds(time_end - time_start_block_one);

			//if(to_mseconds(latency_one) > 0.01f || blockCnt % 1000 == 0)
			//	SpacePrint("%u start: %f ms end: %f ms Latency: %f ms - Throughput: %f block/ms \n",  blockCnt, to_mseconds(time_start), to_mseconds(time_end), to_mseconds(latency_avg),  throughput);
			//for(int i=0; i<10000; i++) {
			//	SpacePrint("~");
			//	SpacePrint("\b");
			//}

			if(blockCnt == 10000)
				sc_stop();
		}
	
}

double to_mseconds(uint64_t value)
{
	double factor = static_cast<double>(m_time_resolution) * 1000;

	return value  * factor * 1e-15;
}
