#ifndef _WonXSerialPort_h_INCLUDED_
#define _WonXSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonXSerialPort * WonXSerialPort;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include "WWSerialPort.h"
#include "UNIXSerialPort.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonXSerialPort_GetWWSerialPort(WonXSerialPort wonx_sp);
WWSerialPort WonXSerialPort_SetWWSerialPort(WonXSerialPort wonx_sp,
					    WWSerialPort ww_sp);

UNIXSerialPort WonXSerialPort_GetUNIXSerialPort(WonXSerialPort wonx_sp);
UNIXSerialPort WonXSerialPort_SetUNIXSerialPort(WonXSerialPort wonx_sp,
						UNIXSerialPort unix_sp);

WonXSerialPort WonXSerialPort_Create();
WonXSerialPort WonXSerialPort_Destroy(WonXSerialPort wonx_serial_port);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
