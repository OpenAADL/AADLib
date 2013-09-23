#include <types.h>
#include <libc/stdio.h>
#include <gtypes.h>
#include <libm.h>

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
 printf ("%d> ADIRU Processor Health Manager runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt++); 
 printf ("\n"); 
 pt=pt+9;
 int i=0;
  
 switch (recovery_action) {
   case 211: printf ("ADIRU processor receive recovery action %d\n", recovery_action);
            adirup_validated_data1=0;
            *output1=adirup_validated_data1;
            printf ("ADIRU processor dumps Acc1! \n");            
            break;
   case 221: printf ("ADIRU processor receive recovery action %d\n", recovery_action);
            adirup_validated_data2=0;
            *output2=adirup_validated_data2;
            printf ("ADIRU processor dumps Acc2! \n");            
            break;
   case 231: printf ("ADIRU processor receive recovery action %d\n", recovery_action);
            adirup_validated_data3=0;
            *output3=adirup_validated_data3;
            printf ("ADIRU processor dumps Acc3! \n");            
            break;
   case 241: printf ("ADIRU processor receive recovery action %d\n", recovery_action);
            adirup_validated_data4=0;
            *output4=adirup_validated_data4;
            printf ("ADIRU processor dumps Acc4! \n");            
            break;
   case 251: printf (" |->ADIRU processor receive recovery action:-> %d\n", recovery_action);
            printf ("\n"); 
            adirup_health_status[4]=1;
            adirup_validated_data5=0;
            *output5=adirup_validated_data5;
            printf (" |->ADIRU processor dumps Accelerometer 5!!!\n");
            printf ("\n"); 
            break;
   case 261: printf (" |->ADIRU processor receive recovery action:-> %d\n", recovery_action);
            printf ("\n"); 
            adirup_health_status[5]=1;
            adirup_validated_data6=0;
            *output6=adirup_validated_data6;
            printf (" |->ADIRU processor dumps Accelerometer 6!!!\n"); 
            printf ("\n");            
            break;
   default: ;
           
}
/*----------------Reset event happens!-----------------------------------------------------*/  

/*-----------------------------------------------------------------------------------------*/
if (t1!=12) {
   printf("  |->Current System Sensors Status:\n");
   printf ("\n"); 
	for (i=0;i<6;i++) {
	     switch (adirup_health_status[i]) {
		case 0: printf(" |->Accelerometer %d is working....\n",i+1);
                        printf ("\n"); 
		        break;
		case 1: printf(" |->Accelerometer %d failed!!!\n",i+1);
                        printf ("\n"); 
		        break;
		default: ;
	     }
         }
  
}
if (t1==2) {
   printf(" |->ADIRU Processor unknown reset---->----->\n");
   printf ("\n"); 

}

if (t1==12) {
  
   printf("  |->Current System Sensors Status:\n");
   printf ("\n");
         adirup_health_status[4]=0;   
        
	for (i=0;i<6;i++) {
	     switch (adirup_health_status[i]) {
		case 0: printf("  |->Accelerometer %d is working....\n",i+1);
                        printf ("\n"); 
		        break;
		case 1: printf("  |->Accelerometer %d failed!!!\n",i+1);
                        printf ("\n"); 
		        break;
		default: ;
	     }
         }
   
}

t1++;

/*-----------------acc5 monitor-------------------------*/
if (adirup_health_status[4]==0){ 
	if (acc5_data_store[t2]>9) {
	     acc5_error_msg_code=251;
	     adirup_health_status[4]=1;//acc3 failed.
	     if (x5<3) {
	     *error_msg=acc5_error_msg_code; //send error message out.
	     
	     }
	      acc5_x=1;
	      x5++;
	      if (x5>=3) {x5=3;acc5_x=0;}
             if (acc5_x!=0) {
                  printf (" |->ADIRU Processor sends error msg to SHM:-> %d\n", acc5_error_msg_code);
                  printf ("\n"); 
             }
	} 
t2++;
if (t2>9) {t2=0;}
}

   adirup_validated_data1=in_data1;
  
  //printf ("ADIRUp_HM send validated data %d\n", validated_data);
  //printf ("ADIRUp_HM send error msg to SHM %d\n", error_code);
  
}

void solve (int in_data1,int in_data2)
{
  //printf ("ADIRUp_solve receive data from ADIRUp_HM %d\n", in_data1);
  
}
