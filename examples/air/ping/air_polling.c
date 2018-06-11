#include <stdio.h>

#include <po_hi_debug.h>
#include <po_hi_types.h>
#include <po_hi_transport.h>
#include <po_hi_gqueue.h>

#include <deployment.h>
#include <request.h>
#include <activity.h>

#include <air.h>
#include <a653.h>

void user_ports_polling ()
{
   __po_hi_port_t portno;
   __po_hi_node_t mynode;
   __po_hi_node_t tmpnode;
   __po_hi_request_t request;
   __po_hi_port_kind_t pkind;

   RETURN_CODE_TYPE rc;
   SAMPLING_PORT_CURRENT_STATUS_TYPE STATUS;
   MESSAGE_SIZE_TYPE len;
   PARTITION_ID_TYPE self_id;

   __DEBUGMSG ("Polling ports for partition \n");

   mynode = __po_hi_transport_get_mynode ();

   for (portno = 0 ; portno < __PO_HI_NB_PORTS ; portno++) {
      pkind = __po_hi_transport_get_port_kind (portno);
      tmpnode = __po_hi_transport_get_node_from_entity
        (__po_hi_get_entity_from_global_port (portno));

      if (tmpnode == mynode) {
        /*
         if (pkind ==  __PO_HI_IN_DATA_INTER_PROCESS) {
           ret = XM_read_sampling_message
             (__po_hi_transport_xtratum_get_port (portno),
              &request,
              sizeof (__po_hi_request_t),
              0);
         }
        */
        __DEBUGMSG ("Testing port %d\n",
                    __po_hi_transport_air_get_port (portno));

         if (pkind ==  __PO_HI_IN_EVENT_DATA_INTER_PROCESS) {
           RECEIVE_QUEUING_MESSAGE
             (__po_hi_transport_air_get_port (portno),
              INFINITE_TIME_VALUE,
              &request,
              &len,
              &rc);

           if (rc == NO_ERROR) {
            __po_hi_main_deliver (&request);
           }
         }
      }
   }
}
