/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/key.h"

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

int key_press_check(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_press_check() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_hit_check(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_hit_check() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_wait(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_wait() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());

  /*
   * 以下はホットスポットになり得るので注意!
   */

  ret = 0;
  do {
    XDisplay_Sync(x_display);
    ret = XDisplay_GetKeyPress(x_display);
  } while (ret == 0);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void key_set_repeat(int rate, int delay)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_set_repeat() : rate = %d, delay = %d, ", rate, delay);
  fflush(stdout);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

int key_get_repeat(void)
{
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_get_repeat() : "); fflush(stdout);

  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_hit_check_with_repeat(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_hit_check_with_repeat() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
