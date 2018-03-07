#ifndef _WWSerialPort_h_INCLUDED_
#define _WWSerialPort_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWSerialPort * WWSerialPort;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/comm.h"

/*****************************************************************************/
/* ��������                                                                */
/*****************************************************************************/

#define WW_SERIAL_PORT_BAUDRATE_9600  0
#define WW_SERIAL_PORT_BAUDRATE_38400 1

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWSerialPort_Open(    WWSerialPort s);
int WWSerialPort_Close(   WWSerialPort s);
int WWSerialPort_IsOpened(WWSerialPort s);
int WWSerialPort_IsClosed(WWSerialPort s);

int WWSerialPort_GetBaudrate(WWSerialPort s);
int WWSerialPort_SetBaudrate(WWSerialPort s, int baudrate);

int WWSerialPort_SetBaudrate9600(WWSerialPort s);
int WWSerialPort_SetBaudrate38400(WWSerialPort s);
int WWSerialPort_IsBaudrate9600(WWSerialPort s);
int WWSerialPort_IsBaudrate38400(WWSerialPort s);

int WWSerialPort_GetSendTimeout(WWSerialPort s);
int WWSerialPort_SetSendTimeout(WWSerialPort s, int timeout);
int WWSerialPort_GetReceiveTimeout(WWSerialPort s);
int WWSerialPort_SetReceiveTimeout(WWSerialPort s, int timeout);

unsigned int WWSerialPort_GetCancelKey(WWSerialPort s);
unsigned int WWSerialPort_SetCancelKey(WWSerialPort s, int cancel_key);

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ���                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Create();

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Destroy(WWSerialPort ww_serial_port);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
