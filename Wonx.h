#ifndef _wonx_h_INCLUDED_
#define _wonx_h_INCLUDED_

#include "WonxDisplay.h"
#include "WonxText.h"
#include "WonxSystem.h"
#include "WonxSerialPort.h"

/*****************************************************************************/
/* ディスプレイの確保                                                        */
/*****************************************************************************/

int Wonx_IsCreated(void);
void Wonx_Create(void);
WonxDisplay Wonx_GetWonxDisplay(void);
WonxText Wonx_GetWonxText(void);
WonxSystem Wonx_GetWonxSystem(void);
WonxSerialPort Wonx_GetWonxSerialPort(void);

#endif
