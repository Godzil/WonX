/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/bank.h"

#include "WonX.h"

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

void bank_set_map(int bank, int bank_num)
{
  return;
}

int bank_get_map(int bank)
{
  return (0);
}

unsigned char bank_read_byte(int bank, unsigned int off)
{
  return (0);
}

void bank_write_byte(int bank, unsigned int off, unsigned int data)
{
  return;
}

unsigned int bank_read_word(int bank, unsigned int off)
{
  return (0);
}

void bank_write_word(int bank, unsigned int off, unsigned int data)
{
  return;
}

void bank_read_block(int bank, unsigned int off,
		     void * buffer, unsigned int size)
{
  return;
}

void bank_write_block(int bank, unsigned int off,
		      void * buffer, unsigned int size)
{
  return;
}

void bank_fill_block(int bank, unsigned int off,
		     unsigned int size, unsigned int data)
{
  return;
}

void bank_erase_flash(int bank)
{
  return;
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
