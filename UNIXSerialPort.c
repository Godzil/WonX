/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include "UNIXSerialPortP.h"
#include "WonX.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* ポートの open/close                                                       */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_Open(UNIXSerialPort unix_serial_port)
{
  unix_serial_port->opened = 1;
  return (0);
}
int UNIXSerialPort_Close(UNIXSerialPort unix_serial_port)
{
  unix_serial_port->opened = 0;
  return (0);
}

int UNIXSerialPort_IsOpened(UNIXSerialPort unix_serial_port)
{ return (unix_serial_port->opened != 0); }
int UNIXSerialPort_IsClosed(UNIXSerialPort unix_serial_port)
{ return (unix_serial_port->opened == 0); }

/*---------------------------------------------------------------------------*/
/* 受信データがあるかどうか                                                  */
/*---------------------------------------------------------------------------*/

/*
 * タイムアウト時間をミリ秒単位で指定．
 * 0 のときは，即時
 * -1 のときは，無期限待ち
 */

int UNIXSerialPort_IsDataExisting(UNIXSerialPort unix_serial_port,
				  int timeout)
{
  fd_set bitmap;
  struct timeval t;
  struct timeval * t_p;
#if 0
  int c;
#endif

  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (0);

  /*
   * 0 のときは，即時
   * -1 のときは，無期限待ち
   */
  if (timeout == -1) {
    t_p = NULL;
  } else {
    t.tv_sec  =  timeout / 1000;
    t.tv_usec = (timeout % 1000) * 1000;
    t_p = &t;
  }

  /*
   * FreeBSD3.4 で実験したところ，
   * アラームシグナルを使用する場合，select()でのブロック中に
   * アラームシグナルが発生すると，その直後にselect()もタイムアウト
   * してしまうので，注意．
   * (select() がタイムアウトした後にアラームシグナルが発生する場合は，
   *  正常に動作した)
   * 論理上は問題が無いが，期待した時間だけ待ってくれないという現象が
   * 起きる可能性がある．
   */

#if 0
  /* 読み飛ばしたい文字があるときは，こっちのコードを使う */
  do {
    FD_ZERO(&bitmap);
    FD_SET(fileno(stdin), &bitmap);
    select(fileno(stdin) + 1, &bitmap, NULL, NULL, t_p);

    if (!FD_ISSET(fileno(stdin), &bitmap))
      return (0);

    c = fgetc(stdin);
  } while (0); /* 読み飛ばしたい文字があるときは，ここでcをチェックする */
  ungetc(c, stdin);
#else
  FD_ZERO(&bitmap);
  FD_SET(fileno(stdin), &bitmap);
  select(fileno(stdin) + 1, &bitmap, NULL, NULL, t_p);

  if (!FD_ISSET(fileno(stdin), &bitmap))
    return (0);
#endif

  return (1);
}

/*---------------------------------------------------------------------------*/
/* 受信                                                                      */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_ReceiveCharacter(UNIXSerialPort unix_serial_port,
				    int timeout)
{
  int c;

  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (-1);

  c = UNIXSerialPort_IsDataExisting(unix_serial_port, timeout)
    ? fgetc(stdin) : -1;
  c = (c == '\n') ? '\r' : c; /* \r のエミュレーション */

  return (c);
}

/*---------------------------------------------------------------------------*/
/* 送信                                                                      */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_SendCharacter(UNIXSerialPort unix_serial_port,
				 unsigned char c)
{
  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (0);

  wonx_print_character(stdout, c);

  return (1);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

UNIXSerialPort UNIXSerialPort_Create()
{
  UNIXSerialPort unix_serial_port;

  unix_serial_port = (UNIXSerialPort)malloc(sizeof(_UNIXSerialPort));
  if (unix_serial_port == NULL)
    WonX_Error("UNIXSerialPort_Create", "Cannot allocate memory.");

  unix_serial_port->opened = 0;

  return (unix_serial_port);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

UNIXSerialPort UNIXSerialPort_Destroy(UNIXSerialPort unix_serial_port)
{
  if (unix_serial_port == NULL)
    WonX_Error("UNIXSerialPort_Destroy", "Object is not created.");

  if (UNIXSerialPort_IsOpened(unix_serial_port))
    UNIXSerialPort_Close(unix_serial_port);

  free(unix_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
