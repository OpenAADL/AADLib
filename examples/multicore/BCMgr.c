#include <stdint.h>
#include <stdio.h>
#include "MsgType.h"

static uint8_t FirstTimeThrough 	 = TRUE;

void bcinit(initmsg *msg){
	printf("Bus Controller Initialization - Start\n");
	msg->InitializationComplete = TRUE;
	printf("Bus Controller Initialization - Complete\n");
}

void bcmgr(initmsg msg, busmsg M0RTtoBCMsg, busmsg M1RTtoBCMsg, busmsg M2RTtoBCMsg){
	if(msg.InitializationComplete){
		if(FirstTimeThrough){
			printf("Bus Controller Manager - Start\n");
			FirstTimeThrough = FALSE;
		}
	}
	if(M0RTtoBCMsg.MsgQueue[0].Msg[0] > 0){
		printf("Message Received from RT Bus Mgr 0 (%d)\n",M0RTtoBCMsg.MsgQueue[0].Msg[1]);
	}
	if(M1RTtoBCMsg.MsgQueue[0].Msg[0] > 0){
		printf("Message Received from RT Bus Mgr 1 (%d)\n",M1RTtoBCMsg.MsgQueue[0].Msg[1]);
	}
	if(M2RTtoBCMsg.MsgQueue[0].Msg[0] > 0){
		printf("Message Received from RT Bus Mgr 2 (%d)\n",M2RTtoBCMsg.MsgQueue[0].Msg[1]);
	}
}
