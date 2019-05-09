/**
 * simu.h: simulator for the mine pump
 */

#ifndef _SIMU_H_
#define _SIMU_H_
#ifndef BYTE
#define BYTE unsigned char
#endif

void InitSimu(void);
/* Initialize simulator, should be called before any other function
 *  from this unit
 */

BYTE ReadHLS(void);       /* Return status byte from HLS sensor */
BYTE ReadLLS(void);       /* Return status byte from LLS sensor */
BYTE ReadMS(void);        /* Return status byte from MS sensor */
void CmdPump(BYTE cmd);   /* Command pump, 1 = on, 0 = off */
void CmdAlarm(BYTE cmd);  /* Command alarm, 1 = on, 0 = off */

#endif /* _SIMU_H_ */
