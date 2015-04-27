
#include "gtypes.h"


int adirup_validated_data1=0;
int adirup_validated_data2=0;
int adirup_validated_data3=0;
int adirup_validated_data4=0;
int adirup_validated_data5=0;
int adirup_validated_data6=0;
int t1=0;
int t2=0;
int error_code=22;
int adirup_health_status[6]={0,0,0,0,1,0};

int acc5_data_store[10]={0};
int acc5_error_msg_code=0;
int x5=0;
int acc5_x=0;
int pt=8;

void adirup_hm (int in_data1, int in_data2,int in_data3, int in_data4,int in_data5, int in_data6,
		int* output1, int* output2,int* output3, int* output4,int* output5, int* output6,int recovery_action, int* error_msg)
{
#ifndef __DEOS__
	printf ("%d> ADIRU Processor Health Manager runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++);
	printf ("\n");
#else
	myprint_str_int ("ADIRU Processor Health Manager runs ",pt++);
#endif
	pt=pt+9;
	int i=0;

	switch (recovery_action) {
	case 211:
#ifndef __DEOS__
		printf ("ADIRU processor receive recovery action %d\n", recovery_action);
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_validated_data1=0;
		*output1=adirup_validated_data1;
#ifndef __DEOS__
		printf ("ADIRU processor dumps Acc1! \n");
#else
		myprint_str ("ADIRU processor dumps Acc1! \n");

#endif
		break;
	case 221:
#ifndef __DEOS__
		printf ("ADIRU processor receive recovery action %d\n", recovery_action);
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_validated_data2=0;
		*output2=adirup_validated_data2;
#ifndef __DEOS__
		printf ("ADIRU processor dumps Acc2! \n");
#else
		myprint_str_int ("ADIRU processor dumps Acc2!");
#endif
		break;
	case 231:
#ifndef __DEOS__
		printf ("ADIRU processor receive recovery action %d\n", recovery_action);
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_validated_data3=0;
		*output3=adirup_validated_data3;
#ifndef __DEOS__
		printf ("ADIRU processor dumps Acc3! \n");
#else
		myprint_str ("ADIRU processor dumps Acc3! \n");
#endif
		break;
	case 241:
#ifndef __DEOS__
		printf ("ADIRU processor receive recovery action %d\n", recovery_action);
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_validated_data4=0;
		*output4=adirup_validated_data4;
#ifndef __DEOS__
		printf ("ADIRU processor dumps Acc4! \n");
#else
		myprint_str ("ADIRU processor dumps Acc4! \n");
#endif
		break;
	case 251:
#ifndef __DEOS__
		printf (" |->ADIRU processor receive recovery action:-> %d\n", recovery_action);

		printf ("\n");
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_health_status[4]=1;
		adirup_validated_data5=0;
		*output5=adirup_validated_data5;
#ifndef __DEOS__

		printf (" |->ADIRU processor dumps Accelerometer 5!!!\n");
		printf ("\n");
#else
		myprint_str (" |->ADIRU processor dumps Accelerometer 5!!!");
#endif
		break;
	case 261:
#ifndef __DEOS__
		printf (" |->ADIRU processor receive recovery action:-> %d\n", recovery_action);
		printf ("\n");
#else
		myprint_str_int ("ADIRU processor receive recovery action ", recovery_action);
#endif
		adirup_health_status[5]=1;
		adirup_validated_data6=0;
		*output6=adirup_validated_data6;
#ifndef __DEOS__

		printf (" |->ADIRU processor dumps Accelerometer 6!!!\n");
		printf ("\n");
#else
		myprint_str (" |->ADIRU processor dumps Accelerometer 6!!!");
#endif
		break;
	default: ;

	}
	/*----------------Reset event happens!-----------------------------------------------------*/

	/*-----------------------------------------------------------------------------------------*/
	if (t1!=12) {
#ifndef __DEOS__
		printf("  |->Current System Sensors Status:\n");
		printf ("\n");
#else
		myprint_str ("  |->Current System Sensors Status:");
#endif
		for (i=0;i<6;i++) {
			switch (adirup_health_status[i]) {
			case 0:
#ifndef __DEOS__
				printf(" |->Accelerometer %d is working....\n",i+1);
				printf ("\n");
#else
				myprint_str_int (" |->Accelerometer is working, id= ",i+1);
#endif
				break;
			case 1:
#ifndef __DEOS__
				printf(" |->Accelerometer %d failed!!!\n",i+1);
				printf ("\n");
#else
				myprint_str_int (" |->Accelerometer failed !!! id=",i+1);
#endif
				break;
			default: ;
			}
		}

	}
	if (t1==2) {
#ifndef __DEOS__

		printf(" |->ADIRU Processor unknown reset---->----->\n");
		printf ("\n");
#else
		myprint_str (" |->ADIRU Processor unknown reset---->----->");
#endif
	}

	if (t1==12) {
#ifndef __DEOS__

		printf("  |->Current System Sensors Status:\n");
		printf ("\n");
#else
		myprint_str ("  |->Current System Sensors Status:");
#endif
		adirup_health_status[4]=0;

		for (i=0;i<6;i++) {
			switch (adirup_health_status[i]) {
			case 0:
#ifndef __DEOS__
				printf("  |->Accelerometer %d is working....\n",i+1);
				printf ("\n");
#else
				myprint_str_int ("  |->Accelerometer %d is working.... id=",i+1);
#endif
				break;
			case 1:
#ifndef __DEOS__
				printf("  |->Accelerometer failed!!! id=",i+1);
				printf ("\n");
#else
				myprint_str_int ("  |->Accelerometer failed !!! id=",i+1);
#endif
				break;
			default: ;
			}
		}

	}

	t1++;

	if (adirup_health_status[4]==0){
		if (acc5_data_store[t2]>9) {
			acc5_error_msg_code=251;
			adirup_health_status[4]=1;
			if (x5<3) {
				*error_msg=acc5_error_msg_code; 

			}
			acc5_x=1;
			x5++;
			if (x5>=3) {x5=3;acc5_x=0;}
			if (acc5_x!=0) {
#ifndef __DEOS__
				printf (" |->ADIRU Processor sends error msg to SHM:-> %d\n", acc5_error_msg_code);
				printf ("\n");
#else
				myprint_str_int (" |->ADIRU Processor sends error msg to SHM:-> ", acc5_error_msg_code);
#endif
			}
		}
		t2++;
		if (t2>9) {t2=0;}
	}

	adirup_validated_data1=in_data1;

}

void solve (int in_data1,int in_data2)
{
	printf ("ADIRUp_solve receive data from ADIRUp_HM %d\n", in_data1);

}
