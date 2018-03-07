#ifndef _WonxSerialPort_h_INCLUDED_
#define _WonxSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWSerialPort.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonxSerialPort * WonxSerialPort;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

WWSerialPort WonxSerialPort_GetWWSerialPort(WonxSerialPort wonx_serial_port);
WWSerialPort WonxSerialPort_SetWWSerialPort(WonxSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port);

WonxSerialPort WonxSerialPort_Create();
WonxSerialPort WonxSerialPort_Destroy(WonxSerialPort wonx_serial_port);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
