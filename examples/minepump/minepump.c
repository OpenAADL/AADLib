/* Files generated from AADL model */
#include <request.h>
#include <deployment.h>
#include <po_hi_gqueue.h>

#include "simu.h" /* MinePump simulator */

#define MS_L1 70
#define MS_L2 100

#define Normal 0
#define Alarm1 1
#define Alarm2 2
#define LowLevel 0
#define HighLevel 1

/*****************************************************************************/
/* Helper macros to access AADL entities                                     */

#define LOCAL_PORT(THREAD_INSTANCE_NAME, PORT_NAME) THREAD_INSTANCE_NAME ## _local_ ## PORT_NAME
#define REQUEST_PORT(THREAD_INSTANCE_NAME, PORT_NAME) THREAD_INSTANCE_NAME ## _global_ ## PORT_NAME
#define PORT_VARIABLE(THREAD_INSTANCE_NAME, PORT_NAME) vars.REQUEST_PORT(THREAD_INSTANCE_NAME,PORT_NAME).REQUEST_PORT(THREAD_INSTANCE_NAME,PORT_NAME)

/*****************************************************************************/
/* WaterLevelMonitoring_Thread is a periodic task, period = 250 ms.
   It has one output port called "WaterAlarm", of integer type

   At each dispatch, it reads the HLS and LLS sensors, using the
   ReadHLS() and RealLLS() functions.

   - If HLS is true, it sends "HighValue" through its out port;
   - else, if LLS is false, it sends "LowValue";
   - otherwise, it sends the previous value.
*/

void waterlevelmonitoring_body(__po_hi_task_id self) {

  /* Logic of the thread */
  static int waterlvl = LowLevel;

  if (ReadHLS()) {
    waterlvl = HighLevel;
  } else if (!ReadLLS()) {
    waterlvl = LowLevel;
  }

  /* Send waterlvl through the wateralarm port */

  /* NOTE: Sending through an output port requires some discipline in
     naming conventions */

  __po_hi_request_t request;  /* AADL request type */

  /* The name of an output port is built from the thread_instance name
       and the port name using the REQUEST_PORT macro */

  request.port = REQUEST_PORT (waterlevelmonitoring_thread, wateralarm);

  /* The name of the corresponding port variable is built from the
     port name, following similar pattern. */

  request.PORT_VARIABLE (waterlevelmonitoring_thread,wateralarm) = waterlvl;

  /* We send the request through the thread *local* port, built from
     the instance name and the port name using the LOCAL_PORT macro */

  __po_hi_gqueue_store_out
      (self,
       LOCAL_PORT (waterlevelmonitoring_thread, wateralarm),
       &request);
}

/*****************************************************************************/
/* MethaneMonitoring_Thread is a periodic task, period = 100 ms.
   It has one output port called "MethaneLevel", of integer type

   At each dispatch, it reads the MS sensor. Depending on the methane
   level (constant MS_L1 and MS_L2), it sends either normal, Alert1 or
   Alert2 through its output port.
*/

void methanemonitoring_body (__po_hi_task_id self) {

  /* Logic of the thread */
  int level = Normal;
  BYTE MS;

  MS=ReadMS();
  if (MS>MS_L2) {
    level=Alarm2;
  } else if (MS>MS_L1) {
    level=Alarm1;
  } else {
    level=Normal;
  }

  /* Port management */
  __po_hi_request_t request;
  request.port = REQUEST_PORT (methanemonitoring_thread, methanelevel);
  request.PORT_VARIABLE (methanemonitoring_thread,methanelevel) = level;
  __po_hi_gqueue_store_out
    (self,
     LOCAL_PORT (methanemonitoring_thread, methanelevel),
     &request);

}

/*****************************************************************************/
/* PumpCtrl_Thread is a sporadic task, with a MIAT of 1 ms It is
   triggered by incoming events from sensors.

   It has two input ports (dispatching)
   * MethaneLevel, of integer type
   * WaterLevel, of integer type

   and one output port
   * WaterAlarm, of integer type

   This task manages the alarm logic, and the pump.

   - if the alarm level is different from Normal, it sends the value 1
     through its wateralarm output port, otherwise it sends 0;
   - if the alarm level is Alarm2 then the pump is deactivated (cmd =
     0 sent to CmdPump); else, if the water level is high, then the
     pump is activated (cmd = 1 sent to CmdPump), otherwise the pump
     is left off.
*/

void pumpctrl_body(__po_hi_task_id self) {
  int niveau_eau, niveau_alarme, alarme;
  int cmd=0;

  /* Read from the MethaneLevel port */
  __po_hi_request_t request;

  /* Get the value from the methanelevel port */
  __po_hi_gqueue_get_value
    (self,
     LOCAL_PORT (pumpctrl_thread,methanelevel),
     &(request));

  /* Extract it from the port variable */
  niveau_alarme = request.PORT_VARIABLE (pumpctrl_thread,methanelevel);

  /* Dequeue the event */
  __po_hi_gqueue_next_value (self, LOCAL_PORT (pumpctrl_thread,methanelevel));

  if (niveau_alarme==Normal) {
    alarme=0;
  } else {
    alarme=1;
  }

  /* Send alarme value through the WaterAlarm port */

  request.port = REQUEST_PORT(pumpctrl_thread, wateralarm);
  request.PORT_VARIABLE(pumpctrl_thread,wateralarm) = alarme;
  __po_hi_gqueue_store_out
    (self,
     LOCAL_PORT (pumpctrl_thread, wateralarm),
     &request);

  if (niveau_alarme==Alarm2) {
    cmd=0;
  } else {

    /* Read from the WaterLevel port */
    __po_hi_gqueue_get_value(self,LOCAL_PORT (pumpctrl_thread,waterlevel),&(request));
    niveau_eau = request.PORT_VARIABLE(pumpctrl_thread,waterlevel);
    __po_hi_gqueue_next_value (self, LOCAL_PORT (pumpctrl_thread,waterlevel));

    if (niveau_eau==HighLevel) {
      cmd=1;
    } else if (niveau_eau==LowLevel) {
      cmd=0;
    }
  }

  CmdPump(cmd);
}

/*****************************************************************************/
/* WaterAlarm_Thread is a sporadic task, with a MIAT of 1 ms
   It has one input port (dispatching)
   * WaterAlarm, of integer type

   It calls CmdAlarm with the value read.
*/

void wateralarm_body(__po_hi_task_id self) {
  int value = 1;

  /* Read from the WaterAlarm port */

  __po_hi_request_t request;
  __po_hi_gqueue_get_value(self,LOCAL_PORT (wateralarm_thread,wateralarm),&(request));
  value = request.PORT_VARIABLE(wateralarm_thread,wateralarm);
  __po_hi_gqueue_next_value (self, LOCAL_PORT (wateralarm_thread, wateralarm));

  CmdAlarm(value);
}
