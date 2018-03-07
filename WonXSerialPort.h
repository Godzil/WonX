#ifndef _WonXSerialPort_h_INCLUDED_
#define _WonXSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWSerialPort.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonXSerialPort * WonXSerialPort;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

WWSerialPort WonXSerialPort_GetWWSerialPort(WonXSerialPort wonx_serial_port);
WWSerialPort WonXSerialPort_SetWWSerialPort(WonXSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port);

WonXSerialPort WonXSerialPort_Create();
WonXSerialPort WonXSerialPort_Destroy(WonXSerialPort wonx_serial_port);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
