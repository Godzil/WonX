/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonXSerialPortP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonXSerialPort_GetWWSerialPort(WonXSerialPort wonx_serial_port)
{ return (wonx_serial_port->ww_serial_port); }
WWSerialPort WonXSerialPort_SetWWSerialPort(WonXSerialPort wonx_serial_port,
					    WWSerialPort ww_serial_port)
{ return (wonx_serial_port->ww_serial_port = ww_serial_port); }

WonXSerialPort WonXSerialPort_Create()
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;

  wonx_serial_port = (WonXSerialPort)malloc(sizeof(_WonXSerialPort));
  if (wonx_serial_port == NULL)
    WonX_Error("WonXSerialPort_Create", "Cannot allocate memory.");

  ww_serial_port = WWSerialPort_Create();
  if (ww_serial_port == NULL)
    WonX_Error("WonXSerialPort_Create",
	       "Cannot create WonderWitch serial port.");
  WonXSerialPort_SetWWSerialPort(wonx_serial_port, ww_serial_port);

  return (wonx_serial_port);
}

WonXSerialPort WonXSerialPort_Destroy(WonXSerialPort wonx_serial_port)
{
  WWSerialPort ww_serial_port;

  if (wonx_serial_port == NULL)
    WonX_Error("WonXSerialPort_Destroy", "Object is not created.");

  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  if (ww_serial_port)
    WonXSerialPort_SetWWSerialPort(wonx_serial_port,
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
