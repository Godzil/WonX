#ifndef _WonxSerialPort_h_INCLUDED_
#define _WonxSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWSerialPort.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonxSerialPort * WonxSerialPort;

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonxSerialPort_GetWWSerialPort(WonxSerialPort wonx_serial_port);
WWSerialPort WonxSerialPort_SetWWSerialPort(WonxSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port);

WonxSerialPort WonxSerialPort_Create();
WonxSerialPort WonxSerialPort_Destroy(WonxSerialPort wonx_serial_port);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
