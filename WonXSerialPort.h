#ifndef _WonXSerialPort_h_INCLUDED_
#define _WonXSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWSerialPort.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonXSerialPort * WonXSerialPort;

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonXSerialPort_GetWWSerialPort(WonXSerialPort wonx_serial_port);
WWSerialPort WonXSerialPort_SetWWSerialPort(WonXSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port);

WonXSerialPort WonXSerialPort_Create();
WonXSerialPort WonXSerialPort_Destroy(WonXSerialPort wonx_serial_port);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
