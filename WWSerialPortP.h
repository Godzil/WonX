#ifndef _WWSerialPortP_h_INCLUDED_
#define _WWSerialPortP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWSerialPort.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWSerialPort {

  int port_on; /* ポートの状態 */
  int baudrate; /* ボーレート */

  /*
   * タイムアウト時間
   * 本来は VBLANK 単位で指定するのだが，wonx では
   * WONX_SERIAL_PORT_TIMETICKS 単位で指定することにする．
   */
  int send_timeout;
  int receive_timeout;

  unsigned int cancel_key;

} _WWSerialPort;

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
