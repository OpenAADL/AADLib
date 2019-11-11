#include<stdio.h>
#include<types.h>

void print_spg
(test__ba__backend__a_struct_impl a_data_in) {

  printf("****************************************** \n");
  printf("#elems of a_data = %d\n", a_data_in.elem);
  fflush(stdout);
  for (int i = 0; i < a_data_in.elem; i++)
  { 

  	printf("a_data.all_elems [%d] = %d\n", i, a_data_in.all_elems [i]);
  	fflush(stdout);
  }
  printf("****************************************** \n");
}

void consume_spg (test__ba__backend__a_struct_impl data)
{
   printf ("Consume %d\n", data.elem);
   fflush(stdout);
}
