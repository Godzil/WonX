/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <unistd.h>
#include <signal.h>

#include "UNIXTimerP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* コールバック関数                                                          */
/*---------------------------------------------------------------------------*/

/* pointed_unix_timer の値はいつ変化するかわからないので，最適化を禁止する */

volatile static UNIXTimer pointed_unix_timer = NULL;

static void UNIXTimer_CallBackFunction(int argument)
{
  int ret;

  /*
   * static なフラグを立てて，コールバック関数からコールバック関数が
   * 呼ばれたのを検出するのが必要かも．
   */

  if (pointed_unix_timer == NULL) return;
  if (!pointed_unix_timer->timer_on) return;

  if (pointed_unix_timer->pause) {
    pointed_unix_timer->interrupt_in_pause++;
  } else {
    if (pointed_unix_timer->interrupt_in_pause == 0)
      pointed_unix_timer->interrupt_in_pause = 1;
    while (pointed_unix_timer->interrupt_in_pause > 0) {
      pointed_unix_timer->interrupt_in_pause--;
      if (pointed_unix_timer->callback != NULL) {

	/*
	 * コールバック関数の中から UNIXTimer_Unpause() などが呼ばれて，
	 * そこからさらにコールバック関数が呼ばれたりしたときのために，
	 * ポーズする．
	 */
	pointed_unix_timer->pause++;

	ret = (*pointed_unix_timer->callback)(pointed_unix_timer->parameter);

	pointed_unix_timer->pause--;

	/*
	 * コールバック関数の中で UNIXTimer_* 関連の関数が呼び出されると，
	 * ここで UNIXTimer オブジェクトの状態が変わってしまう可能性がある．
	 */

	/*
	 * 以下の処理は同じことを関数の先頭でやっているので，
	 * 最適化されて削除されないように注意すること．
	 */
	if (pointed_unix_timer == NULL) return;
	if (!pointed_unix_timer->timer_on) return;

	if (ret) {
	  pointed_unix_timer->interrupt_in_pause = 0;
	  UNIXTimer_OFF(pointed_unix_timer);
	  return;
	}

	/*
	 * コールバック関数中で，ポーズの状態が切り替わってしまった
	 * ときのため．
	 * 以下の処理は同じようなことをちょっと前にやっているので，
	 * 最適化されて削除されないように注意すること．
	 */
	if (pointed_unix_timer->pause) break;

      }
    }
  }

  if (pointed_unix_timer->auto_preset)
    UNIXTimer_ON(pointed_unix_timer);
  else
    UNIXTimer_OFF(pointed_unix_timer);

  return;
}

/*---------------------------------------------------------------------------*/
/* タイマの ON, OFF                                                          */
/*---------------------------------------------------------------------------*/

/*
 * このあたりの処理は，処理中にタイマ割り込みが発生しないかどうかを
 * 常に注意すること．でないと不可解なバグの原因になる．
 */

int UNIXTimer_ON(UNIXTimer unix_timer)
{
  int t;

  unix_timer->timer_on = 1;
  pointed_unix_timer = unix_timer;

  /*
   * SIGALRM を使用するので，sleep() 中にアラームが起きた場合には，
   * コールバック関数からの復帰後に sleep() の残り時間は継続されない．
   */
  signal(SIGALRM, UNIXTimer_CallBackFunction);

#if 0 /* use ualarm() */
  /* ualarm(); の引数に0を用いてはダメなので */
  t = unix_timer->interval * 1000;
  if (t < 1) t = 1;
  ualarm(t, 0);
#else /* use alarm() */
  /* alarm(); の引数に0を用いてはダメなので */
  t = unix_timer->interval / 1000;
  if (t < 1) t = 1;
  alarm(t);
#endif

  return (0);
}

int UNIXTimer_OFF(UNIXTimer unix_timer)
{
  alarm(0); /* タイマを無効にする */
  unix_timer->timer_on = 0;
  pointed_unix_timer = NULL;
  return (0);
}

int UNIXTimer_IsON(UNIXTimer unix_timer)
{ return (unix_timer->timer_on != 0); }
int UNIXTimer_IsOFF(UNIXTimer unix_timer)
{ return (unix_timer->timer_on == 0); }

/*---------------------------------------------------------------------------*/
/* 一時停止                                                                  */
/*---------------------------------------------------------------------------*/

/*
 * 関数の先頭と末尾を Pause, Unpause でくくるばあいなどは，
 * 関数から関数を呼び出したときに，２重 Pause, Unpause が起きるので
 * 注意すること．(ただし，ポーズはネストできる)
 */

/*
 * ポーズはネストされるので，UNIXTimer_Unpause() を安易に繰り返し呼んだり
 * しないように注意すること．
 */

/*
 * このあたりの処理は，処理中にタイマ割り込みが発生しないかどうかを
 * 常に注意すること．でないと不可解なバグの原因になる．
 */

int UNIXTimer_Pause(UNIXTimer unix_timer)
{
  unix_timer->pause++; /* ポーズはネストできる */

  return (0);
}

int UNIXTimer_Unpause(UNIXTimer unix_timer)
{
  if (unix_timer->pause == 0)
    Wonx_Error("UNIXTimer_Unpause", "Duplicated unpause.");

  if (unix_timer->pause == 1) {
    if (unix_timer->interrupt_in_pause > 0) {

      /*
       * 万が一，ここでタイマ割り込みが発生しても，
       * unix_timer->pause は 1 なので，コールバック関数は呼ばれないので，
       * 問題無し．
       * オートプリセットならば，べつに問題無し．
       * オートプリセットでなければ timer_on フラグが落ちるので，問題無い．
       */

      /*
       * 処理中にタイマ割り込みが発生すると面倒なので，
       * タイマをいったん無効にする．
       */
      alarm(0);

      /*
       * 状態値を変更する直前・直後で割り込みが入ると面倒なので，
       * 割り込みをOFFにしてからデクリメントする．
       */
      /* コールバック関数を呼ぶ前に，pause フラグを無効にする */
      unix_timer->pause--; /* ポーズはネストできる */

      /* コールバック関数の呼び出し */
      UNIXTimer_CallBackFunction(0);
    }
  } else {
    unix_timer->pause--; /* ポーズはネストできる */
  }

  return (0);
}

int UNIXTimer_IsPause(UNIXTimer unix_timer)
{ return (unix_timer->pause != 0); }

/*---------------------------------------------------------------------------*/
/* オートプリセット                                                          */
/*---------------------------------------------------------------------------*/

int UNIXTimer_SetAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset = 1); }
int UNIXTimer_ResetAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset = 0); }
int UNIXTimer_IsAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset != 0); }

/*---------------------------------------------------------------------------*/
/* インターバル                                                              */
/*---------------------------------------------------------------------------*/

int UNIXTimer_GetInterval(UNIXTimer unix_timer)
{ return (unix_timer->interval); }
int UNIXTimer_SetInterval(UNIXTimer unix_timer, int interval)
{ return (unix_timer->interval = interval); }

/*---------------------------------------------------------------------------*/
/* コールバック関数の呼び出し時のパラメータ                                  */
/*---------------------------------------------------------------------------*/

void * UNIXTimer_GetParameter(UNIXTimer unix_timer)
{ return (unix_timer->parameter); }
void * UNIXTimer_SetParameter(UNIXTimer unix_timer, void * parameter)
{ return (unix_timer->parameter = parameter); }

/*---------------------------------------------------------------------------*/
/* コールバック関数の取得・登録                                              */
/*---------------------------------------------------------------------------*/

UNIXTimerCallBack UNIXTimer_GetCallBack(UNIXTimer unix_timer)
{ return (unix_timer->callback); }
UNIXTimerCallBack UNIXTimer_SetCallBack(UNIXTimer unix_timer,
					UNIXTimerCallBack callback)
{ return (unix_timer->callback = callback); }

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

UNIXTimer UNIXTimer_Create(int auto_preset, int interval, void * parameter,
			   UNIXTimerCallBack callback)
{
  UNIXTimer unix_timer;

  unix_timer = (UNIXTimer)malloc(sizeof(_UNIXTimer));
  if (unix_timer == NULL)
    Wonx_Error("UNIXTimer_Create", "Cannot allocate memory.");

  unix_timer->timer_on           = 0;
  unix_timer->pause              = 0;
  unix_timer->interrupt_in_pause = 0;
  unix_timer->auto_preset        = 0;
  unix_timer->interval           = 0;
  unix_timer->parameter          = NULL;
  unix_timer->callback           = NULL;

  if (auto_preset) UNIXTimer_SetAutoPreset(unix_timer);
  else UNIXTimer_ResetAutoPreset(unix_timer);

  UNIXTimer_SetInterval(unix_timer, interval);
  UNIXTimer_SetParameter(unix_timer, parameter);
  UNIXTimer_SetCallBack(unix_timer, callback);

  return (unix_timer);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

/*
 * このあたりの処理は，処理中にタイマ割り込みが発生しないかどうかを
 * 常に注意すること．でないと不可解なバグの原因になる．
 */

UNIXTimer UNIXTimer_Destroy(UNIXTimer unix_timer)
{
  if (unix_timer == NULL)
    Wonx_Error("UNIXTimer_Destroy", "Object is not created.");

  UNIXTimer_OFF(unix_timer);

  free(unix_timer);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
