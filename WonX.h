#ifndef _wonx_h_INCLUDED_
#define _wonx_h_INCLUDED_

#include "WonXDisplay.h"
#include "WonXText.h"
#include "WonXSystem.h"
#include "WonXSerialPort.h"

/*****************************************************************************/
/* ディスプレイの確保                                                        */
/*****************************************************************************/

int WonX_IsCreated(void);
void WonX_Create(void);
WonXDisplay WonX_GetWonXDisplay(void);
WonXText WonX_GetWonXText(void);
WonXSystem WonX_GetWonXSystem(void);
WonXSerialPort WonX_GetWonXSerialPort(void);

#endif
