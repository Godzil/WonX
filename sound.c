/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/sound.h"

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

void sound_init(void)
{
  return;
}

void sound_set_channel(unsigned int flags)
{
  return;
}

unsigned int sound_get_channel(void)
{
  return (0);
}

void sound_set_output(unsigned int flags)
{
  return;
}

unsigned int sound_get_output(void)
{
  return (0);
}

void sound_set_wave(int channel, unsigned char * wave)
{
  return;
}

void sound_set_pitch(int channel, unsigned int frequency)
{
  return;
}

unsigned int sound_get_pitch(int channel)
{
  return (0);
}

void sound_set_volume(int channel, unsigned int volume)
{
  return;
}

unsigned int sound_get_volume(int channel)
{
  return (0);
}

void sound_set_sweep(int sweep, int step)
{
  return;
}

unsigned int sound_get_sweep(void)
{
  return (0);
}

void sound_set_noise(unsigned int flags)
{
  return;
}

unsigned int sound_get_noise(void)
{
  return (0);
}

unsigned int sound_get_random(void)
{
  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
