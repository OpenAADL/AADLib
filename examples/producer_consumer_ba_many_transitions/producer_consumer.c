#include<stdio.h>
#include<types.h>
#include<stdlib.h>
#include <time.h> 

int nb_call_of_compute_spg = 1;

//void compute_spg (base_types__integer *a_data_out) {
void compute_spg (int* a_data_out) {

    if (nb_call_of_compute_spg == 1)
    	// Use current time as seed for random generator 
    	srand(time(0)); 

		nb_call_of_compute_spg++;

    /* random int between 0 and 20 */
    int r = rand() % 20 + 1; 
    printf ("compute_spg : value = %d \n", r);   
    *a_data_out = r;        
}

void print_spg
(test__ba__backend__a_struct_impl a_data_in) {

  printf("****************************************** \n");
  printf("#elems of consumed data = %d\n", a_data_in.elem);
  fflush(stdout);
  for (int i = 0; i < a_data_in.elem; i++)
  { 

  	printf("Consumed data.all_elems [%d] = %d\n", i, a_data_in.all_elems [i]);
  	fflush(stdout);
  }
  printf("****************************************** \n");
}

void print_thread_begin_execution ()
{

  printf("*--------------------------------------------* \n");
  printf("      Thread consumer starts execution  \n");
  printf("*--------------------------------------------* \n");
  fflush(stdout);
}

