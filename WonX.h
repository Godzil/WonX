#ifndef _wonx_h_INCLUDED_
#define _wonx_h_INCLUDED_

#include "WonXDisplay.h"
#include "WonXSystem.h"
#include "WonXSerialPort.h"

int WonX_IsCreated(void);
void WonX_Create(void);
WonXDisplay WonX_GetWonXDisplay(void);
WonXSystem WonX_GetWonXSystem(void);
WonXSerialPort WonX_GetWonXSerialPort(void);

/*===========================================================================*/
/* エラー処理                                                                */
/*===========================================================================*/

int WonX_Error(char * funcname, char * message);
int WonX_Warning(char * funcname, char * message);

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
