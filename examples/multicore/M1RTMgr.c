#include <stdio.h>
#include "MsgType.h"

static uint8_t FirstTimeThrough 	 = TRUE;
static uint32_t	MessageCounter		= 0;


void m1rtinit(initmsg *msg){
	printf("Mission Bus 1 Remote Terminal Initialization - Start\n");
	msg->InitializationComplete = TRUE;
	printf("Mission Bus 1 Remote Terminal  - Complete\n");
}

void m1rtmgr(initmsg msg,busmsg *RTtoBCMsg){
	if(msg.InitializationComplete){
		if(FirstTimeThrough){
			printf("Mission Bus 1 Remote Terminal  - Start\n");
			FirstTimeThrough = FALSE;
		}
		if(MessageCounter == 0){
			RTtoBCMsg->MsgQueue[0].Msg[0]=1;
			RTtoBCMsg->MsgQueue[0].Msg[1]++;
			MessageCounter = 800;				// 8 Seconds
			printf("RT1 Sending Message (%d) to BC\n",RTtoBCMsg->MsgQueue[0].Msg[1]);
		}
		else {
			RTtoBCMsg->MsgQueue[0].Msg[0]=0;
			MessageCounter--;
		}
	}
}
