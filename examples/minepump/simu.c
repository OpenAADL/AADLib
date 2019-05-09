#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef __SIMU_SOCKET__
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif /* __SIMU_SOCKET__ */

#include "simu.h"

#ifdef __SIMU_SOCKET__
FILE * sockin;
#endif /* __SIMU_SOCKET__ */

FILE * sockout;
pthread_mutex_t mutex_simu_minepump;
int CmdPump_Value = 0; /* c = 0, pump is off, c = 1, pump is on */
BYTE WaterLevel_Value = 50;

/*****************************************************************************/
void InitSimu(void) {
  if (sockout != NULL)
    return;

#ifdef __SIMU_SOCKET__

  int sock;
  struct sockaddr_in address;

  if ((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
    perror("Can't open socket");

  address.sin_family = AF_INET; /* Internet address family */
  address.sin_addr.s_addr=inet_addr("127.0.0.1"); /* Server IP address */
  address.sin_port =htons(4242); /* Server port */
  if (connect(sock, (struct sockaddr*)&address,sizeof(address)) < 0)
    perror("Je ne peux me connecter au simulateur. Assurez-vous que minepump.tcl s'execute");

  sockin=fdopen(sock,"r");
  sockout=fdopen(sock,"w");

#else
  sockout=stdout;
#endif /* __SIMU_SOCKET__ */

  pthread_mutex_init(&mutex_simu_minepump,0);
}

/*****************************************************************************/
BYTE ReadHLS(void) {
  InitSimu();

  BYTE b;
  pthread_mutex_lock (&mutex_simu_minepump);

#ifdef __SIMU_SOCKET__
  fprintf(sockout,"HLS\n");
  fflush(sockout);
  b=fgetc(sockin);
#else
  WaterLevel_Value = WaterLevel_Value - CmdPump_Value*4 + 2;
  b = (WaterLevel_Value > 100)?1:0;
#endif /* __SIMU_SOCKET__ */

  pthread_mutex_unlock (&mutex_simu_minepump);
  return b;
}

/*****************************************************************************/
BYTE ReadLLS(void) {
  InitSimu ();

  BYTE b;
  pthread_mutex_lock (&mutex_simu_minepump);

#ifdef __SIMU_SOCKET__
  fprintf(sockout,"LLS\n");
  fflush(sockout);
  b=fgetc(sockin);
#else
  b = (WaterLevel_Value > 80)?1:0;
#endif /* __SIMU_SOCKET__ */

  pthread_mutex_unlock (&mutex_simu_minepump);
  return b;
}

/*****************************************************************************/
BYTE ReadMS(void) {
  InitSimu ();

  static BYTE b = 50;

  pthread_mutex_lock (&mutex_simu_minepump);

#ifdef __SIMU_SOCKET__
  fprintf(sockout,"MS\n");
  fflush(sockout);
  b=fgetc(sockin);
#else
  /* If there is no GUI, we simply emulate the methane sensor. The methane
     gets up and down */

  static BYTE b_increment = 2;
  b += b_increment;

  if (b == 100 || b == 40)
    b_increment = - b_increment;

#endif /* __SIMU_SOCKET__ */

  pthread_mutex_unlock (&mutex_simu_minepump);
  return b;
}

/*****************************************************************************/
void CmdPump(BYTE cmd) {
  InitSimu ();

  pthread_mutex_lock (&mutex_simu_minepump);
  CmdPump_Value = cmd ? 1 : 0;
#ifndef __SIMU_SOCKET__
  fprintf(sockout,"WL = %3d\t", WaterLevel_Value);
#endif /* __SIMU_SOCKET__ */
  fprintf(sockout,"Pump %d\n",CmdPump_Value);
  fflush(sockout);
  pthread_mutex_unlock (&mutex_simu_minepump);
}

/*****************************************************************************/
void CmdAlarm(BYTE cmd) {
  InitSimu ();

  int c=cmd?1:0; /* c = 0, alarm is off, c = 1, alarm is on */

  pthread_mutex_lock (&mutex_simu_minepump);
  fprintf(sockout,"Alarm %d\t",c);
  fflush(sockout);
  pthread_mutex_unlock (&mutex_simu_minepump);
}
