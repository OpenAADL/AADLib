#ifndef MSGTYPE_H
#define MSGTYPE_H

#include <stdint.h>

#define FALSE	0
#define TRUE	1
#define MAXNUMBEROFWORDS	34
#define MSGQUEUELENGTH		64

  	//	data InitializationMsg
	//	  properties
    //	    Source_Language => (C);
    //	    Type_Source_Name => "initmsg";
    //		Source_Text => ("MsgType");
  	//  end InitializationMsg;

	typedef struct InitMessageType{
		uint8_t	InitializationComplete;
	}INITMESSAGETYPE;

	typedef INITMESSAGETYPE initmsg;

	//  data BusMessage
	//    properties
	//      Source_Language => (C);
	//      Type_Source_Name => "busmsg";
	//      Source_Text => ("MsgType");
	//  end BusMessage;

	typedef struct BusMessageType{
		uint16_t Msg[MAXNUMBEROFWORDS];
	}BUSMESSAGETYPE;

	typedef struct BusMessageQueueType{
		BUSMESSAGETYPE	MsgQueue[MSGQUEUELENGTH];
		uint32_t		NumberOfMessages;
	}BUSMESSAGEQUEUETYPE;

	typedef BUSMESSAGEQUEUETYPE	busmsg;

#endif
