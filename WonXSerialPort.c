/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonXSerialPortP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWSerialPort WonXSerialPort_GetWWSerialPort(WonXSerialPort wonx_sp)
{ return (wonx_sp->ww_serial_port); }
WWSerialPort WonXSerialPort_SetWWSerialPort(WonXSerialPort wonx_sp,
					    WWSerialPort ww_sp)
{ return (wonx_sp->ww_serial_port = ww_sp); }

UNIXSerialPort WonXSerialPort_GetUNIXSerialPort(WonXSerialPort wonx_sp)
{ return (wonx_sp->unix_serial_port); }
UNIXSerialPort WonXSerialPort_SetUNIXSerialPort(WonXSerialPort wonx_sp,
						UNIXSerialPort unix_sp)
{ return (wonx_sp->unix_serial_port = unix_sp); }

WonXSerialPort WonXSerialPort_Create()
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;

  wonx_serial_port = (WonXSerialPort)malloc(sizeof(_WonXSerialPort));
  if (wonx_serial_port == NULL)
    WonX_Error("WonXSerialPort_Create", "Cannot allocate memory.");

  ww_serial_port = WWSerialPort_Create();
  if (ww_serial_port == NULL)
    WonX_Error("WonXSerialPort_Create",
	       "Cannot create WonderWitch serial port.");
  WonXSerialPort_SetWWSerialPort(wonx_serial_port, ww_serial_port);

  unix_serial_port = UNIXSerialPort_Create();
  if (unix_serial_port == NULL)
    WonX_Error("WonXSerialPort_Create",
	       "Cannot create UNIX serial port.");
  WonXSerialPort_SetUNIXSerialPort(wonx_serial_port, unix_serial_port);

  return (wonx_serial_port);
}

WonXSerialPort WonXSerialPort_Destroy(WonXSerialPort wonx_serial_port)
{
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;

  if (wonx_serial_port == NULL)
    WonX_Error("WonXSerialPort_Destroy", "Object is not created.");

  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  if (ww_serial_port)
    WonXSerialPort_SetWWSerialPort(wonx_serial_port,
				   WWSerialPort_Destroy(ww_serial_port));

  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);
  if (unix_serial_port)
    WonXSerialPort_SetUNIXSerialPort(wonx_serial_port,
				     UNIXSerialPort_Destroy(unix_serial_port));

  free(wonx_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
