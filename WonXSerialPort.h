#ifndef _WonXSerialPort_h_INCLUDED_
#define _WonXSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonXSerialPort * WonXSerialPort;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include "WWSerialPort.h"
#include "UNIXSerialPort.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
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
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
