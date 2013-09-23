#include <types.h>
#include <libc/stdio.h>
#include <gtypes.h>
#include <libm.h>

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

printf ("%d> alarm aggregator runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++);
printf ("\n");  


//printf ("SHM receives error report from ADIRUp %d\n", adirup_error_msg);
   *errors=acc_error_msg;
   if (adirup_error_msg==251) {
       *errors=error_msg_code2[4];
   }
   if ((*errors)!=0) {
     printf (" |->alarm aggregator receives error report:->%d\n", *errors);
     printf ("\n"); 
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

printf ("%d> mitigation actor runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++); 
printf ("\n"); 
pt=pt+8;
 diagnosis_result=error_msg;
 //printf ("mitigation_actor get diagnosis result %d\n",diagnosis_result);
 switch (diagnosis_result) {
    case 11:
	  if (system_health_status[0]==0) {  
	    if (acc1_error_t<1) {
	    *recovery_action=recovery_code[0];
	    printf ("|->mitigation actor sends recovery action:-> %d\n", recovery_code[0]);
            printf ("\n");
	    } 
            if (acc1_error_t==1) {
               printf("acc1 failed!!!!\n");
               acc1_error_t=-1;
               *recovery_action=adirup_action_code[0];
               printf ("|->mitigationActor sends imitigation command to ADIRU Procrssor %d\n", adirup_action_code[0]);
            }
            acc1_error_t++;
          }
            break;
   case 21:
	  if (system_health_status[1]==0) {  
	    if (acc2_error_t<1) {
	    *recovery_action=recovery_code[1];
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[1]);
	    } 
            if (acc2_error_t==1) {
               printf("acc2 failed!!!!\n");
               acc2_error_t=-1;
               *recovery_action=adirup_action_code[1];
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[1]);
            }
            acc2_error_t++;
          }
            break;
   case 31:
	  if (system_health_status[2]==0) {  
	    if (acc3_error_t<1) {
	    *recovery_action=recovery_code[2];
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[2]);
	    } 
            if (acc3_error_t==1) {
               printf("acc3 failed!!!!\n");
               acc3_error_t=-1;
               *recovery_action=adirup_action_code[2];
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[2]);
            }
            acc3_error_t++;
          }
            break;
   case 41:
	  if (system_health_status[3]==0) {  
	    if (acc4_error_t<1) {
	    *recovery_action=recovery_code[3];
	    printf ("mitigationActor sends recovery action %d\n", recovery_code[3]);
	    } 
            if (acc4_error_t==1) {
               printf("acc4 failed!!!!\n");
               acc4_error_t=-1;
               *recovery_action=adirup_action_code[3];
               printf ("mitigationActor sends imigation command to ADIRU Procrssor %d\n", adirup_action_code[3]);
            }
            acc4_error_t++;
          }
            break;
   case 51:
	  //if (system_health_status[4]==0) {  
            if (acc5_error_t<1) {
	    *recovery_action=recovery_code[4];
	    printf ("  |->mitigationActor sends recovery action:-> %d\n", recovery_code[4]);
            printf ("\n");
	    } 
            if (acc5_error_t==1) {
               system_health_status[4]=1;
               printf("  |->Accelerometer 5 failed!!!!\n");
               printf ("\n");
               acc5_error_t=-1;
               *recovery_action=adirup_action_code[4];
               printf ("  |->mitigationActor sends imigation command to ADIRU Procrssor:-> %d\n", adirup_action_code[4]);
               printf ("\n");
            }
            acc5_error_t++;
          //}
            break;
   case 61:
	  if (system_health_status[5]==0) {  
	    if (acc6_error_t<1) {
	    *recovery_action=recovery_code[5];
	    printf ("  |->mitigationActor sends recovery action:-> %d\n", recovery_code[5]);
            printf ("\n");
	    } 
            if (acc6_error_t==1) {
               printf("  |->Accelerometer 6 failed!!!!\n");
               printf ("\n");
               acc6_error_t=-1;
               *recovery_action=adirup_action_code[5];
            printf ("  |->mitigationActor sends imigation command to ADIRU Procrssor:-> %d\n", adirup_action_code[5]);
            printf ("\n");
            }
            acc6_error_t++;
          }
            break;
    default: *recovery_action=recovery_normal_p;
 }
}


