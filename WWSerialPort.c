/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWSerialPortP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWSerialPort_Open(    WWSerialPort s) { return (s->opened =  1); }
int WWSerialPort_Close(   WWSerialPort s) { return (s->opened =  0); }
int WWSerialPort_IsOpened(WWSerialPort s) { return (s->opened != 0); }
int WWSerialPort_IsClosed(WWSerialPort s) { return (s->opened == 0); }

int WWSerialPort_GetBaudrate(WWSerialPort s) { return (s->baudrate); }
int WWSerialPort_SetBaudrate(WWSerialPort s, int baudrate)
{ return (s->baudrate = baudrate); }

int WWSerialPort_SetBaudrate9600(WWSerialPort s)
{ return (WWSerialPort_SetBaudrate(s, WW_SERIAL_PORT_BAUDRATE_9600)); }
int WWSerialPort_SetBaudrate38400(WWSerialPort s)
{ return (WWSerialPort_SetBaudrate(s, WW_SERIAL_PORT_BAUDRATE_38400)); }
int WWSerialPort_IsBaudrate9600(WWSerialPort s)
{ return (WWSerialPort_GetBaudrate(s) == WW_SERIAL_PORT_BAUDRATE_9600); }
int WWSerialPort_IsBaudrate38400(WWSerialPort s)
{ return (WWSerialPort_GetBaudrate(s) == WW_SERIAL_PORT_BAUDRATE_38400); }

int WWSerialPort_GetSendTimeout(WWSerialPort s)
{ return (s->send_timeout); }
int WWSerialPort_SetSendTimeout(WWSerialPort s, int timeout)
{ return (s->send_timeout = timeout); }
int WWSerialPort_GetReceiveTimeout(WWSerialPort s)
{ return (s->receive_timeout); }
int WWSerialPort_SetReceiveTimeout(WWSerialPort s, int timeout)
{ return (s->receive_timeout = timeout); }

unsigned int WWSerialPort_GetCancelKey(WWSerialPort s)
{ return (s->cancel_key); }
unsigned int WWSerialPort_SetCancelKey(WWSerialPort s, int cancel_key)
{ return (s->cancel_key = cancel_key); }

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Create()
{
  WWSerialPort ww_serial_port;

  ww_serial_port = (WWSerialPort)malloc(sizeof(_WWSerialPort));
  if (ww_serial_port == NULL)
    WonX_Error("WWSerialPort_Create", "Cannot allocate memory.");

  WWSerialPort_Close(ww_serial_port);
  WWSerialPort_SetBaudrate38400(ww_serial_port);
  WWSerialPort_SetSendTimeout(ww_serial_port, 100);
  WWSerialPort_SetReceiveTimeout(ww_serial_port, 100);

  return (ww_serial_port);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Destroy(WWSerialPort ww_serial_port)
{
  if (ww_serial_port == NULL)
    WonX_Error("WWSerialPort_Destroy", "Object is not created.");

  WWSerialPort_Close(ww_serial_port);

  free(ww_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
