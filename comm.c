/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/comm.h"

#include "Wonx.h"

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
{}

void comm_close(void)
{}

int comm_send_char(unsigned char c)
{
  return (0);
}

int comm_receive_char(void)
{
  return (0);
}

int comm_receive_with_timeout(int timeout)
{
  return (0);
}

int comm_send_string(char * string)
{
  return (0);
}

int comm_send_block(void * buffer, int size)
{
  return (0);
}

int comm_receive_block(void * buffer, int size)
{
  return (0);
}

void comm_set_timeout(int recv_timeout, int send_timeout)
{
}

void comm_set_baudrate(int baudrate)
{
}

int comm_get_baudrate(void)
{
  return (0);
}

void comm_set_cancel_key(unsigned int pattern)
{
}

unsigned int comm_get_cancel_key(void)
{
  return (0);
}

int comm_xmodem(void * xmodem)
{
  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
