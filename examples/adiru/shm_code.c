
#include "gtypes.h"

#define __DEOS__

int temp1=0;
int temp2=0;
int recovery_code[6]={13,23,33,43,53,63};
int system_health_status[6]={0,0,0,0,0,0};
int adirup_action_code[6]={211,221,231,241,251,261};
int error_msg_code1[6]={211,221,231,241,251,261};
int error_msg_code2[6]={11,21,31,41,51,61};
int diagnosis_result=0;
int acc1_error_t=0;
int acc2_error_t=0;
int acc3_error_t=0;
int acc4_error_t=0;
int acc5_error_t=0;
int acc6_error_t=0;

int recovery_normal_p=0;
int pt=9;

//extern int local_health_status[6];

void alarm_aggregator (int acc_error_msg, int adirup_error_msg,int* errors)
{
#ifndef __DEOS__
printf ("%d> alarm aggregator runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++);
printf ("\n");  
#else
     myprint_str_int ("alarm aggregator runs id=",pt++);
#endif

//printf ("SHM receives error report from ADIRUp %d\n", adirup_error_msg);
   *errors=acc_error_msg;
   if (adirup_error_msg==251) {
       *errors=error_msg_code2[4];
   }
   if ((*errors)!=0) {
#ifndef __DEOS__
     printf (" |->alarm aggregator receives error report:->%d\n", *errors);
     printf ("\n"); 
#else
     myprint_str_int (" |->alarm aggregator receives error report:-> error=", *errors);
#endif
   }
   temp1=acc_error_msg;
  //printf ("Aggregator sends error msg to diagnosisEngine %d\n", temp1);
}

void diagnosis_engine (int error_msg , int* diagnosed_error)
{
//printf ("diagnosis_engine is runing -------------------------------------------\n");
//printf ("diagnosisEngine receives error msg from Aggregator %d\n", error_msg);
 *diagnosed_error=error_msg;
 temp2=error_msg;
 //printf ("diagnosisEngine sends error msg to mitigationActor %d\n", temp2);
}

void mitigation_actor (char error_msg , int* recovery_action)
{
#ifndef __DEOS__
printf ("%d> mitigation actor runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++); 
printf ("\n"); 
#else
     myprint_str_int (" mitigation actor runs id=",pt++);
#endif
pt=pt+8;
 diagnosis_result=error_msg;
 //printf ("mitigation_actor get diagnosis result %d\n",diagnosis_result);
 switch (diagnosis_result) {
    case 11:
	  if (system_health_status[0]==0) {  
	    if (acc1_error_t<1) {
	    *recovery_action=recovery_code[0];
#ifndef __DEOS__
	    printf ("|->mitigation actor sends recovery action:-> %d\n", recovery_code[0]);
            printf ("\n");
#else
     myprint_str_int ("|->mitigation actor sends recovery action:-> code=", recovery_code[0]);
#endif
	    } 
            if (acc1_error_t==1) {
#ifndef __DEOS__
               printf("acc1 failed!!!!\n");
#else
     myprint_str ("acc1 failed!!!!\n");
#endif
               acc1_error_t=-1;
               *recovery_action=adirup_action_code[0];
#ifndef __DEOS__
               printf ("|->mitigationActor sends imitigation command to ADIRU Procerssor %d\n", adirup_action_code[0]);
#else
     myprint_str_int ("|->mitigationActor sends imitigation command to ADIRU CPU ", adirup_action_code[0]);
#endif
            }
            acc1_error_t++;
          }
            break;
   case 21:
	  if (system_health_status[1]==0) {  
	    if (acc2_error_t<1) {
	    *recovery_action=recovery_code[1];
#ifndef __DEOS__
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[1]);
#else
     myprint_str_int ("mitigationActor sends recovery action ", recovery_code[1]);
#endif
	    } 
            if (acc2_error_t==1) {
#ifndef __DEOS__
               printf("acc2 failed!!!!\n");
#else
     myprint_str ("acc2 failed!!!!\n");
#endif
               acc2_error_t=-1;
               *recovery_action=adirup_action_code[1];
#ifndef __DEOS__
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[1]);
#else
     myprint_str_int ("mitigationActor sends imigation command to ADIRU CPU code=", adirup_action_code[1]);
#endif
            }
            acc2_error_t++;
          }
            break;
   case 31:
	  if (system_health_status[2]==0) {  
	    if (acc3_error_t<1) {
	    *recovery_action=recovery_code[2];
#ifndef __DEOS__
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[2]);
#else
     myprint_str_int ("mitigationActor sends recovery action code=", recovery_code[2]);
#endif
	    } 
            if (acc3_error_t==1) {
#ifndef __DEOS__
               printf("acc3 failed!!!!\n");
#else
     myprint_str ("acc3 failed!!!!\n");
#endif
               acc3_error_t=-1;
               *recovery_action=adirup_action_code[2];
#ifndef __DEOS__
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[2]);
#else
     myprint_str_int ("mitigationActor sends imigation command to ADIRU CPU ", adirup_action_code[2]);
#endif
            }
            acc3_error_t++;
          }
            break;
   case 41:
	  if (system_health_status[3]==0) {  
	    if (acc4_error_t<1) {
	    *recovery_action=recovery_code[3];
#ifndef __DEOS__
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[3]);
#else
     myprint_str_int ("mitigationActor sends recovery action ", recovery_code[3]);
#endif
	    } 
            if (acc4_error_t==1) {
#ifndef __DEOS__
               printf("acc4 failed!!!!\n");
#else
     myprint_str ("acc4 failed!!!!\n");
#endif
               acc4_error_t=-1;
               *recovery_action=adirup_action_code[3];
#ifndef __DEOS__
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[3]);
#else
     myprint_str_int ("mitigationActor sends imigation command to ADIRU CPU code=", adirup_action_code[3]);
#endif
            }
            acc4_error_t++;
          }
            break;
   case 51:
	  //if (system_health_status[4]==0) {  
            if (acc5_error_t<1) {
	    *recovery_action=recovery_code[4];
#ifndef __DEOS__
	    printf ("  |->mitigationActor sends recovery action:-> %d\n", recovery_code[4]);
            printf ("\n");
#else
     myprint_str_int ("  |->mitigationActor sends recovery action:-> code=", recovery_code[4]);
#endif
	    } 
            if (acc5_error_t==1) {
               system_health_status[4]=1;
#ifndef __DEOS__
               printf("  |->Accelerometer 5 failed!!!!\n");

               printf ("\n");
#else
     myprint_str ("  |->Accelerometer 5 failed!!!!");
#endif
               acc5_error_t=-1;
               *recovery_action=adirup_action_code[4];
#ifndef __DEOS__
               printf ("  |->mitigationActor sends imigation command to ADIRU Procrssor:-> %d\n", adirup_action_code[4]);
               printf ("\n");
#else
     myprint_str_int ("  |->mitigationActor sends imigation command to ADIRU CPU:-> code=", adirup_action_code[4]);
#endif
            }
            acc5_error_t++;
          //}
            break;
   case 61:
	  if (system_health_status[5]==0) {  
	    if (acc6_error_t<1) {
	    *recovery_action=recovery_code[5];
#ifndef __DEOS__
	    printf ("  |->mitigationActor sends recovery action:-> %d\n", recovery_code[5]);
            printf ("\n");
#else
     myprint_str_int ("  |->mitigationActor sends recovery action:-> code=", recovery_code[5]);
#endif
	    } 
            if (acc6_error_t==1) {
#ifndef __DEOS__
               printf("  |->Accelerometer 6 failed!!!!\n");

               printf ("\n");
#else
     myprint_str ("  |->Accelerometer 6 failed!!!!");
#endif
               acc6_error_t=-1;
               *recovery_action=adirup_action_code[5];
#ifndef __DEOS__
            printf ("  |->mitigationActor sends imigation command to ADIRU Procrssor:-> %d\n", adirup_action_code[5]);

            printf ("\n");
#else
     myprint_str_int ("  |->mitigationActor sends imigation command to ADIRU CPU:-> code=", adirup_action_code[5]);
#endif
            }
            acc6_error_t++;
          }
            break;
    default: *recovery_action=recovery_normal_p;
 }
}


