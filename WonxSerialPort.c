/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonxSerialPortP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonxSerialPort_GetWWSerialPort(WonxSerialPort wonx_serial_port)
{ return (wonx_serial_port->ww_serial_port); }
WWSerialPort WonxSerialPort_SetWWSerialPort(WonxSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port)
{ return (wonx_serial_port->ww_serial_port = ww_serial_port); }

WonxSerialPort WonxSerialPort_Create()
{
  WonxSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;

  wonx_serial_port = (WonxSerialPort)malloc(sizeof(_WonxSerialPort));
  if (wonx_serial_port == NULL)
    Wonx_Error("WonxSerialPort_Create", "Cannot allocate memory.");

  ww_serial_port = WWSerialPort_Create();
  if (ww_serial_port == NULL)
    Wonx_Error("WonxSerialPort_Create",
	       "Cannot create WonderWitch serial port.");
  WonxSerialPort_SetWWSerialPort(wonx_serial_port, ww_serial_port);

  return (wonx_serial_port);
}

WonxSerialPort WonxSerialPort_Destroy(WonxSerialPort wonx_serial_port)
{
  WWSerialPort ww_serial_port;

  if (wonx_serial_port == NULL)
    Wonx_Error("WonxSerialPort_Destroy", "Object is not created.");

  ww_serial_port = WonxSerialPort_GetWWSerialPort(wonx_serial_port);
  if (ww_serial_port)
    WonxSerialPort_SetWWSerialPort(wonx_serial_port,
				   WWSerialPort_Destroy(ww_serial_port));

  free(wonx_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
