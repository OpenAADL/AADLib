#include<stdio.h>
#include<types.h>

void print_spg
(producer__consumer__alpha_type a_data_in) {

  printf("%d\n", a_data_in);
  fflush(stdout);
}

void consume_spg (producer__consumer__alpha_type data)
{
   printf ("Consume %d\n", data);
   fflush(stdout);
}
