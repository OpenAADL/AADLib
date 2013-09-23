#include <types.h>
#include <libc/stdio.h>
#include <gtypes.h>
#include <libm.h>

int acc1_data[20]={0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,0};
int acc2_data[20]={9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,0};
int acc3_data[20]={9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,0};
int acc4_data[20]={9,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,0};
int acc5_data[20]={9,8,7,6,5,4,3,2,1,0,1,2,3,40,5,60,7,80,9,0};
int acc6_data[20]={9,8,7,60,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,0};

int acc1_data_temp=0;
int acc2_data_temp=0;
int acc3_data_temp=0;
int acc4_data_temp=0;
int acc5_data_temp=0;
int acc6_data_temp=0;

int t1=0;
int t2=0;
int t3=0;
int t4=0;
int t5=0;
int t6=0;
int t7=0;
int local_health_status[6]={0};

int acc1_error_msg_code=0;
int acc2_error_msg_code=0;
int acc3_error_msg_code=0;
int acc4_error_msg_code=0;
int acc5_error_msg_code=0;
int acc6_error_msg_code=0;

int acc1_error_action_code=0;
int acc2_error_action_code=0;
int acc3_error_action_code=0;
int acc4_error_action_code=0;
int acc5_error_action_code=0;
int acc6_error_action_code=0;

int acc1_data_store[10]={0};
int acc2_data_store[10]={0};
int acc3_data_store[10]={0};
int acc4_data_store[10]={0};
int acc5_data_store[10]={0};
int acc6_data_store[10]={0};

int acc1_validated_data=0;
int acc2_validated_data=0;
int acc3_validated_data=0;
int acc4_validated_data=0;
int acc5_validated_data=0;
int acc6_validated_data=0;

int acc1_x=0;
int acc2_x=0;
int acc3_x=0;
int acc4_x=0;
int acc5_x=0;
int acc6_x=0;

int x5=0;
int x6=0;

int Null_Point=0;
int pt1=1;
int pt2=7;
//output data from 0 to 9, then 9 to 0 periodicly.
void acc1dataoutput (int* p,int event_in)
{
 printf ("%d> Accelerometer 1 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++);
 printf ("\n");   
   
switch (event_in) {
   case 13:
      local_health_status[0]=2; 
      printf ("acc1 receive reset command %d\n", event_in);
      printf ("\n"); 
      break;
   default: ;
}

    acc1_data_temp=acc1_data[t1]; 
    *p = acc1_data_temp;
    t1++;
    if (t1>17) {
     t1=0;
    }
    if (acc1_data_temp>9) {
      printf ("  |-> Accelerometer 1 sends data Over Range:->%d\n", acc1_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[0]) {

   case 1://failed
    //printf ("acc1 failed!!!\n");
    break;
   case 2://initialise 
    printf ("acc1 is initialising...\n");
    t1=0;
    local_health_status[0]=0;
    //acc1_error_action_code=0;
    //acc1_error_msg_code=0;
    printf ("acc1 initialised!\n");
    break;
   default: ;
   }
   
}

void acc2dataoutput (int* p,int event_in)
{
  printf ("%d> Accelerometer 2 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++); 
  printf ("\n"); 
   if (event_in==23) {
    printf ("acc2 receive Reset command %d\n", event_in);
    local_health_status[1]=2;
   }
   
    acc2_data_temp=acc2_data[t2]; 
    *p = acc2_data_temp;
    t2++;
    if (t2>17) {
     t2=0;
    }
    if (acc2_data_temp>9) {
      printf ("  |-> Accelerometer 2 sends data Over Range:->%d\n", acc2_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[1]) {

   case 1://failed
    //printf ("acc2 failed!!!\n");
    break;
   case 2://initialise 
    printf ("acc2 is initialising...\n");
    t2=0;
    local_health_status[1]=0;
    //acc2_error_action_code=0;
    //acc2_error_msg_code=0;
    printf ("acc2 initialised!\n");
    break;
   default: ;
   }
   
}

void acc3dataoutput (int* p,int event_in)
{
  printf ("%d> Accelerometer 3 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++); 
  printf ("\n"); 

   if (event_in==33) {
    printf ("acc3 receive Reset command %d\n", event_in);
    local_health_status[2]=2;
   }
   
    acc3_data_temp=acc3_data[t4]; 
    *p = acc3_data_temp;
    t4++;
    if (t4>17) {
     t4=0;
    }
    if (acc3_data_temp>9) {
      printf ("  |-> Accelerometer 3 sends data Over Range:->%d\n", acc3_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[2]) {

   case 1://failed
    //printf ("acc2 failed!!!\n");
    break;
   case 2://initialise 
    printf ("acc3 is initialising...\n");
    t4=0;
    local_health_status[2]=0;
    //acc2_error_action_code=0;
    //acc2_error_msg_code=0;
    printf ("acc3 initialised!\n");
    break;
   default: ;
   }
   
}

void acc4dataoutput (int* p,int event_in)
{
  printf ("%d> Accelerometer 4 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++); 
  printf ("\n"); 
   if (event_in==43) {
    printf ("acc4 receive Reset command %d\n", event_in);
    local_health_status[3]=2;
   }
   
    acc4_data_temp=acc4_data[t5]; 
    *p = acc4_data_temp;
    t5++;
    if (t5>17) {
     t5=0;
    }
    if (acc4_data_temp>9) {
      printf ("  |-> Accelerometer 4 sends data Over Range:->%d\n", acc4_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[3]) {

   case 1://failed
    //printf ("acc2 failed!!!\n");
    break;
   case 2://initialise 
    printf ("acc4 is initialising...\n");
    t5=0;
    local_health_status[3]=0;
    //acc2_error_action_code=0;
    //acc2_error_msg_code=0;
    printf ("acc4 initialised!\n");
    break;
   default: ;
   }
}

void acc5dataoutput (int* p,int event_in)
{
 printf ("%d> Accelerometer 5 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++); 
 printf ("\n"); 
   if (event_in==53) {
    printf ("  |-> Accelerometer 5 receives reset command:->%d\n", event_in);
    printf ("\n");
    local_health_status[4]=2;
   }
   
    acc5_data_temp=acc5_data[t6]; 
    *p = acc5_data_temp;
    t6++;
    if (t6>17) {
     t6=0;
    }
    if (acc5_data_temp>9) {
      printf ("  |-> Accelerometer 5 sends data Over Range:->%d\n", acc5_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[4]) {

   case 1://failed
    //printf ("acc2 failed!!!\n");
    break;
   case 2://initialise 
    printf ("  |-> Accelerometer 5 is initialising......\n");
    printf ("\n"); 
    t6=13;
    local_health_status[4]=0;
    //acc2_error_action_code=0;
    //acc2_error_msg_code=0;
    printf ("  |-> Accelerometer 5 initialised!\n");
    printf ("\n"); 
    break;
   default: ;
   }
}

void acc6dataoutput (int* p,int event_in)
{
 printf ("%d> Accelerometer 6 oputs data >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt1++); 
 printf ("\n"); 
 pt1=pt1+4;
   if (event_in==63) {
    printf ("  |-> Accelerometer 6 receives reset command:->%d\n", event_in);
    printf ("\n"); 
    local_health_status[5]=2;
   }
   
    acc6_data_temp=acc6_data[t7]; 
    *p = acc6_data_temp;
    t7++;
    if (t7>17) {
     t7=0;
    }
    if (acc6_data_temp>9) {
      printf ("  |-> Accelerometer 6 sends data Over Range:->%d\n", acc6_data_temp);
      printf ("\n"); 
    }
  switch (local_health_status[5]) {

   case 1://failed
    //printf ("acc2 failed!!!\n");
    break;
   case 2://initialise 
    printf ("  |-> Accelerometer 6 is initialising......\n");
    printf ("\n"); 
    t7=3;
    local_health_status[5]=0;
    //acc2_error_action_code=0;
    //acc2_error_msg_code=0;
    printf ("  |-> Accelerometer 6 initialised!\n");
    printf ("\n"); 
    break;
   default: ;
   }
}

//check received data range and variance rate.
void acchm_monitor (int in_data1,int in_data2,int in_data3,int in_data4,int in_data5,int in_data6,
                    int* p1,int* p4,int* p6,int* p7,int* p8,int* p9,int recovery_action, int* p2,int* p3,int* p5,int* p10,int* p11,int* p12,int* p13)
{
 printf ("%d> Accelerometer health manager runs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",pt2++); 
 printf ("\n"); 
 pt2=pt2+9;
//printf ("ACC_HM receive data from acc4 %d\n", in_data4);
//printf ("ACC_HM receive data from acc2 %d\n", in_data2);

switch (recovery_action) {
   case 13: printf ("ACC_HM receive recovery action %d\n", recovery_action);
            acc1_error_action_code=13;
            *p3=acc1_error_action_code;
            break;
   case 23: printf ("ACC_HM receive recovery action %d\n", recovery_action);
            acc2_error_action_code=23;
            *p5=acc2_error_action_code;
            break;
   case 33: printf ("ACC_HM receive recovery action %d\n", recovery_action);
            acc3_error_action_code=33;
            *p10=acc3_error_action_code;
            break;
   case 43: printf ("ACC_HM receive recovery action %d\n", recovery_action);
            acc4_error_action_code=43;
            *p11=acc4_error_action_code;
            break;
   case 53: printf ("  |->Accelerometer Health Manager receives recovery action:-> %d\n", recovery_action);
            printf ("\n"); 
            acc5_error_action_code=53;
            *p12=acc5_error_action_code;
            break;
   case 63: printf ("  |->Accelerometer Health Manager receives recovery action:-> %d\n", recovery_action);
            printf ("\n"); 
            acc6_error_action_code=63;
            *p13=acc6_error_action_code;
            break;
   default:
           *p3=Null_Point;
           *p5=Null_Point;
           *p10=Null_Point;
           *p11=Null_Point;
           *p12=Null_Point;
           *p13=Null_Point;
}


//------acc monitor--------------------------------------------------
  acc1_data_store[t3]=in_data1;
  acc2_data_store[t3]=in_data2;
  acc3_data_store[t3]=in_data3;
  acc4_data_store[t3]=in_data4;
  acc5_data_store[t3]=in_data5;
  acc6_data_store[t3]=in_data6;
  
//Data over-range.
  if (acc1_data_store[t3]>9) {
     acc1_error_msg_code=11;
     local_health_status[0]=1;//acc1 failed.
     *p2=acc1_error_msg_code; //send error message out.
     acc1_x=1;
     //printf ("acc1 failed!!!\n");
     printf ("ACC_HM send error msg to SHM %d\n", acc1_error_msg_code);
  }
  
     acc1_validated_data=acc1_data_store[t3];
     *p1=acc1_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc1_validated_data);

/*---------------------------------------------------------------------------*/  
  if (acc2_data_store[t3]>9) {
     acc2_error_msg_code=21;
     local_health_status[1]=1;//acc2 failed.
     *p2=acc2_error_msg_code; //send error message out.
     acc2_x=1;
     //printf ("acc1 failed!!!\n");
     printf ("ACC_HM send error msg to SHM %d\n", acc2_error_msg_code);
  } 

     acc2_validated_data=acc2_data_store[t3];
     *p4=acc2_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc2_validated_data);

/*---------------------------------------------------------------------------*/ 
  if (acc3_data_store[t3]>9) {
     acc3_error_msg_code=31;
     local_health_status[2]=1;//acc3 failed.
     *p2=acc3_error_msg_code; //send error message out.
      acc3_x=1;
     //printf ("acc3 failed!!!\n");
     printf ("ACC_HM send error msg to SHM %d\n", acc3_error_msg_code);
  } 
  
     acc3_validated_data=acc3_data_store[t3];
     *p6=acc3_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc2_validated_data);
  
/*---------------------------------------------------------------------------*/ 
  if (acc4_data_store[t3]>9) {
     acc4_error_msg_code=41;
     local_health_status[3]=1;//acc4 failed.
     *p2=acc4_error_msg_code; //send error message out.
      acc4_x=1;
     printf ("ACC_HM send error msg to SHM %d\n", acc4_error_msg_code);
  } 
  
     acc4_validated_data=acc4_data_store[t3];
     *p7=acc4_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc2_validated_data);
   
/*---------------------------------------------------------------------------*/ 
  if (acc5_data_store[t3]>9) {
     acc5_error_msg_code=51;
     local_health_status[4]=1;//acc3 failed.
     if (x5<3) {
     *p2=acc5_error_msg_code; //send error message out.
     }
      acc5_x=1;
      x5++;
      if (x5>=3) {x5=3;acc5_x=0;}
     if (acc5_x!=0) { 
        printf ("  |->Accelerometer Health Manager sends error msg to SHM:-> %d\n", acc5_error_msg_code);
        printf ("\n"); 
     }  
     
  } 
     acc5_validated_data=acc5_data_store[t3];
     
     *p8=acc5_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc2_validated_data);
 
/*---------------------------------------------------------------------------*/ 
  if (acc6_data_store[t3]>9) {
     acc6_error_msg_code=61;
     local_health_status[5]=1;//acc3 failed.
     if (x6<3) {
        *p2=acc6_error_msg_code; //send error message out.
     }
      acc6_x=1;
      x6++;
      if (x6>=3) {x6=3;acc6_x=0;}
     if (acc6_x!=0) { 
        printf ("  |->Accelerometer Health Manager sends error msg to SHM:-> %d\n", acc6_error_msg_code);
        printf ("\n"); 
     }
  } 
     acc6_validated_data=acc6_data_store[t3];
     *p9=acc6_validated_data;
     
      //printf ("ACC_HM send validated data %d\n", acc2_validated_data);
  
  if ((acc1_x ||acc2_x||acc3_x||acc4_x ||acc5_x||acc6_x)==0) { 
        *p2=Null_Point;
     }
  acc1_x=0;
  acc2_x=0;
  acc3_x=0;
  acc4_x=0;
  acc5_x=0;
  acc6_x=0;
//stucked--------------------

//---------------------------

//over variance rate--------------------

//---------------------------
  t3++;
  if (t3>9) {t3=0;}
//----------
/*----------------------------------------------------------------------------
  int i=0;
  for (i=0;i<10;i++) { 
    printf("acchm recieved data %d\n",acc1_data_store[i]);
  }
------------------------------------------------------------------------------*/
//  printf ("ACC_HM receive recovery command from SHM %d\n", recovery_action);

}
