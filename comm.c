/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include "wonx_include/comm.h"

#include "wonx_configure.h"
#include "WonX.h"
#include "WonXSerialPort.h"
#include "WWSerialPort.h"
#include "UNIXSerialPort.h"
#include "etc.h"

/*****************************************************************************/
/* 互換関数の定義                                                            */
/*****************************************************************************/

/*
 * Xサーバとの同期の整合性がとれなくなるなどの問題が考えられるので，
 * 互換関数の内部は UNIXTimer_Pause(), UNIXTimer_Unpause() でくくり，
 * タイマ割り込みを一時停止して処理を行う．また，unpause するまえに，
 * かならず sync するようにする．
 */

/*
 * タイマの一時停止の２重解除の問題が出てくるので，
 * 互換関数から互換関数を呼んではいけない．
 * (一時停止はネストされるが，いちおう)
 * 似たような処理をする関数の場合は，必ず static な別関数に処理をまとめ，
 * そっちを呼び出すようにすること．
 * 引数の表示の問題もあるしね．
 */

void comm_open(void)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_open() : \n");
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (WWSerialPort_IsOpened(ww_serial_port))
    WonX_Warning("comm_open", "WW serial port has already opened.");
  WWSerialPort_Open(ww_serial_port);

  if (UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Warning("comm_open", "UNIX serial port has already opened.");
  UNIXSerialPort_Open(unix_serial_port);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_open() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void comm_close(void)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_close() : \n");
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsClosed(ww_serial_port))
    WonX_Warning("comm_close", "WW serial port is not opened.");
  WWSerialPort_Close(ww_serial_port);

  if (!UNIXSerialPort_IsClosed(unix_serial_port))
    WonX_Warning("comm_close", "UNIX serial port is not opened.");
  UNIXSerialPort_Close(unix_serial_port);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_close() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

static void comm_output(unsigned char c)
{
  WonXSerialPort wonx_serial_port;
  UNIXSerialPort unix_serial_port;

  wonx_serial_port = WonX_GetWonXSerialPort();
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);
  UNIXSerialPort_SendCharacter(unix_serial_port, c);

  return;
}

static int comm_input(int timeout)
{
  WonXSerialPort wonx_serial_port;
  UNIXSerialPort unix_serial_port;
  int c;

  wonx_serial_port = WonX_GetWonXSerialPort();
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);
  c = UNIXSerialPort_ReceiveCharacter(unix_serial_port,
				      WONX_SERIAL_PORT_TIMETICKS * timeout);

  return (c);
}

int comm_send_char(unsigned char c)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_send_char() : character = \'");
  wonx_print_character(stdout, c);
  printf("\'\n");
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_send_char", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_send_char", "UNIX serial port is not opened.");

  printf("output to serial port : \"");
  comm_output(c);
  printf("\"\n");
  fflush(stdout);
  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_send_char() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_receive_char(void)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int c;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_receive_char() : \n");
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_receive_char", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_receive_char", "UNIX serial port is not opened.");

  c = comm_input(WWSerialPort_GetReceiveTimeout(ww_serial_port));

  if (c == -1) ret = ERR_SIO_TIMEOUT;
  else ret = c;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_receive_char() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_receive_with_timeout(int timeout)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int c;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_receive_with_timeout() : timeout = %d\n", timeout);
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_receive_with_timeout", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_receive_with_timeout", "UNIX serial port is not opened.");

  c = comm_input(timeout);

  if (c == -1) ret = ERR_SIO_TIMEOUT;
  else ret = c;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_receive_with_timeout() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_send_string(char * string)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int ret;
  char * p;
  int i;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_send_string() : string = \"");
  for (p = string; *p != '\0'; p++) wonx_print_character(stdout, *p);
  printf("\"\n");
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_send_string", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_send_string", "UNIX serial port is not opened.");

  printf("output to serial port : \"");
  for (i = 0; string[i]; i++) {
    comm_output(string[i]);
  }
  printf("\"\n");
  fflush(stdout);
  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_send_string() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_send_block(void * buffer, int size)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int ret;
  int i;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_send_block() : buffer = %p, size = %d\n", buffer, size);
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_send_block", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_send_block", "UNIX serial port is not opened.");

  printf("output to serial port : \"");
  for (i = 0; i < size; i++) {
    comm_output(((char *)buffer)[i]);
  }
  printf("\"\n");
  fflush(stdout);
  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_send_block() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_receive_block(void * buffer, int size)
{
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;
  int ret;
  int c;
  int i;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_receive_block() : buffer = %p, size = %d\n",
	 buffer, size);
  fflush(stdout);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  if (!WWSerialPort_IsOpened(ww_serial_port))
    WonX_Error("comm_receive_block", "WW serial port is not opened.");
  if (!UNIXSerialPort_IsOpened(unix_serial_port))
    WonX_Error("comm_receive_block", "UNIX serial port is not opened.");

  ret = 0;
  for (i = 0; i < size; i++) {
    c = comm_input(WWSerialPort_GetReceiveTimeout(ww_serial_port));
    if (c == -1) {
      ret = ERR_SIO_TIMEOUT;
      break;
    }
    ((char *)buffer)[i] = c;
  }

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_receive_block() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void comm_set_timeout(int recv_timeout, int send_timeout)
{
  WWSerialPort ww_serial_port;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_set_timeout() : receive_timeout = %d, send_timeout = %d\n", recv_timeout, send_timeout);
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  WWSerialPort_SetReceiveTimeout(ww_serial_port, recv_timeout);
  WWSerialPort_SetSendTimeout(   ww_serial_port, send_timeout);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_set_timeout() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void comm_set_baudrate(int baudrate)
{
  WWSerialPort ww_serial_port;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_set_baudrate() : baudrate = %d\n", baudrate);
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  switch (baudrate) {
  case COMM_SPEED_9600:  WWSerialPort_SetBaudrate9600( ww_serial_port); break;
  case COMM_SPEED_38400: WWSerialPort_SetBaudrate38400(ww_serial_port); break;
  default: WonX_Error("comm_set_baudrate", "Invalid baudrate");
  }

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_set_baudrate() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int comm_get_baudrate(void)
{
  WWSerialPort ww_serial_port;
  int ret = 0;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_get_baudrate() : \n");
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  if (WWSerialPort_IsBaudrate9600(ww_serial_port))
    ret = COMM_SPEED_9600;
  else if (WWSerialPort_IsBaudrate38400(ww_serial_port))
    ret = COMM_SPEED_38400;
  else WonX_Error("comm_get_baudrate", "Invalid baudrate");

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_get_baudrate() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void comm_set_cancel_key(unsigned int pattern)
{
  WWSerialPort ww_serial_port;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_set_cancel_key() : pattern = %u\n", (int)pattern);
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  WWSerialPort_SetCancelKey(ww_serial_port, pattern);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_set_cancel_key() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

unsigned int comm_get_cancel_key(void)
{
  WWSerialPort ww_serial_port;
  unsigned int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_get_cancel_key() : \n");
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  /* ここに処理を書く */
  ret = WWSerialPort_GetCancelKey(ww_serial_port);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_get_cancel_key() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int comm_xmodem(void * xmodem)
{
  WWSerialPort ww_serial_port;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : comm_xmodem() : xmodem = %p\n", xmodem);
  fflush(stdout);

  ww_serial_port = WonXSerialPort_GetWWSerialPort(WonX_GetWonXSerialPort());

  /* 未サポート */
  printf("call : comm_xmodem() : not supported.\n");
  fflush(stdout);
  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : comm_xmodem() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
