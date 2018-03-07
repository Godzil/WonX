/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWSerialPortP.h"
#include "etc.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWSerialPort_ON(   WWSerialPort s) { return (s->port_on =  1); }
int WWSerialPort_OFF(  WWSerialPort s) { return (s->port_on =  0); }
int WWSerialPort_IsON( WWSerialPort s) { return (s->port_on != 0); }
int WWSerialPort_IsOFF(WWSerialPort s) { return (s->port_on == 0); }

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
/* ���֥������Ȥκ���                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Create()
{
  WWSerialPort ww_serial_port;

  ww_serial_port = (WWSerialPort)malloc(sizeof(_WWSerialPort));
  if (ww_serial_port == NULL)
    WonX_Error("WWSerialPort_Create", "Cannot allocate memory.");

  WWSerialPort_OFF(ww_serial_port);
  WWSerialPort_SetBaudrate38400(ww_serial_port);
  WWSerialPort_SetSendTimeout(ww_serial_port, 100);
  WWSerialPort_SetReceiveTimeout(ww_serial_port, 100);

  return (ww_serial_port);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

WWSerialPort WWSerialPort_Destroy(WWSerialPort ww_serial_port)
{
  if (ww_serial_port == NULL)
    WonX_Error("WWSerialPort_Destroy", "Object is not created.");

  free(ww_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
