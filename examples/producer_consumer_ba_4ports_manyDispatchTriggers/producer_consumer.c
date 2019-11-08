#include<stdio.h>
#include<types.h>
#include<stdlib.h>
#include<time.h> 
#include <string.h>

int nb_call_of_compute_spg = 1;

void compute_spg (test__ba__backend__alpha_type *a_data_out) {

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
(test__ba__backend__alpha_type a_data_in) {

  printf("%d\n", a_data_in);
  fflush(stdout);
}

void print_spg1
(test__ba__backend__alpha_type a_data_in) {

  printf("%d\n", a_data_in);
  fflush(stdout);
}

void print_thread_begin_execution (int thread_index)
{
  char thread_name[20] = {0};
  
  switch (thread_index)
  {
	  case 0:
      {
		  strcpy(thread_name, "computation"); 
		  break;
	  }
      case 1:
      {
		  strcpy(thread_name, "producer"); 
		  break;
	  }
	  case 2:
      {
		  strcpy(thread_name, "consumer"); 
		  break;
	  } 
	  case 3:
      {
		  strcpy(thread_name, "receiver"); 
		  break;
	  } 
	  
	  default: // do nothing;
	  break;
  }
  
  printf("*--------------------------------------------* \n");
  printf("      Thread %s resumes its execution  \n", thread_name);
  printf("*--------------------------------------------* \n");
  fflush(stdout);
}

