/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/key.h"

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

int key_press_check(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_press_check() : \n"); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Flush(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_press_check() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_hit_check(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_hit_check() : \n"); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Flush(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_hit_check() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_wait(void)
{
  XDisplay x_display;
  volatile int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_wait() : \n"); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());

  /*
   * 以下はホットスポットになり得るので注意!
   * key_wait() 中に割り込みを受け付けるために一時的にタイマを Unpause する．
   * タイマ割り込みのコールバック関数中でキー入力の割り込み処理も行われるため，
   * do〜while ループ中での XDisplay_Flush() は必要無し．
   */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));
  /*
   * タイマ割り込みによるキー入力処理に期待していったん Unpause するため，
   * 再び Pause するまでは XDisplay の描画関連の関数などを呼び出しては
   * いけないので注意．
   * (XDisplay_GetKeyPress() は単に変数の値を返すだけなので問題無い)
   */
  ret = 0;
  do {
#if 0 /* タイマを Unpause しない場合には必要 */
    XDisplay_Flush(x_display);
#endif
    ret = XDisplay_GetKeyPress(x_display);
  } while (ret == 0);
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_wait() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void key_set_repeat(int rate, int delay)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_set_repeat() : rate = %d, delay = %d\n", rate, delay);
  fflush(stdout);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_set_repeat() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int key_get_repeat(void)
{
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_get_repeat() : \n"); fflush(stdout);

  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_get_repeat() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_hit_check_with_repeat(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_hit_check_with_repeat() : \n"); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Flush(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_hit_check_with_repeat() : return value = 0x%04x\n",
	 (int)ret);
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
