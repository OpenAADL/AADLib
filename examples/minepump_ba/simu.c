#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "simu.h"

pthread_mutex_t mutex_simu_minepump;
int CmdPump_Value = 0; /* c = 0, pump is off, c = 1, pump is on */
int WaterLevel_Value = 50;

/*****************************************************************************/
void InitSimu(void) {
  static bool init_done = false;

  if (!init_done) {
    init_done = true;
    pthread_mutex_init(&mutex_simu_minepump,0);
  }
}

/*****************************************************************************/
readhls (int *hls) {
  InitSimu();

  int b;
  pthread_mutex_lock (&mutex_simu_minepump);

  WaterLevel_Value = WaterLevel_Value - CmdPump_Value*4 + 2;
  b = (WaterLevel_Value > 100)?1:0;

  pthread_mutex_unlock (&mutex_simu_minepump);
  *hls = b;
}

/*****************************************************************************/
readlls(int *lls) {
  InitSimu ();

  int b;

  pthread_mutex_lock (&mutex_simu_minepump);
  b = (WaterLevel_Value > 80)?1:0;
  pthread_mutex_unlock (&mutex_simu_minepump);
  *lls = b;
}

/*****************************************************************************/
readms(int *ms) {
  InitSimu ();

  static int b = 50;
  static int b_increment = 2;

  pthread_mutex_lock (&mutex_simu_minepump);

  /* If there is no GUI, we simply emulate the methane sensor. The methane
     gets up and down */

  b += b_increment;

  if (b == 100 || b == 40)
    b_increment = - b_increment;

  pthread_mutex_unlock (&mutex_simu_minepump);
  *ms = b;
}

/*****************************************************************************/
void cmdpump(int cmd) {
  InitSimu ();

  pthread_mutex_lock (&mutex_simu_minepump);
  CmdPump_Value = cmd ? 1 : 0;
  printf("Pump %d\n",CmdPump_Value);
  fflush(stdout);
  pthread_mutex_unlock (&mutex_simu_minepump);
}

/*****************************************************************************/
void cmdalarm(int cmd) {
  InitSimu ();

  int c=cmd?1:0; /* c = 0, alarm is off, c = 1, alarm is on */

  pthread_mutex_lock (&mutex_simu_minepump);
  printf("Alarm %d\t",c);
  fflush(stdout);
  pthread_mutex_unlock (&mutex_simu_minepump);
}
