/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/system.h"

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

void sys_interrupt_set_hook(int type, intvector_t * vector,
			    intvector_t * old_vector)
{
  WWInterrupt ww_interrupt;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : sys_interrupt_set_hook() : type = %d, vector = %p, old_vector = %p\n", type, vector, old_vector);
  fflush(stdout);

  ww_interrupt = WonXSystem_GetWWInterrupt(WonX_GetWonXSystem());

  old_vector->callback = WWInterrupt_GetCallback(ww_interrupt, type);
  old_vector->cs = WWInterrupt_GetCS(ww_interrupt, type);
  old_vector->ds = WWInterrupt_GetDS(ww_interrupt, type);

  WWInterrupt_SetCallback(ww_interrupt, type, vector->callback);
  WWInterrupt_SetCS(ww_interrupt, type, vector->cs);
  WWInterrupt_SetDS(ww_interrupt, type, vector->ds);

  printf("call : sys_interrupt_set_hook() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void sys_interrupt_reset_hook(int type, intvector_t * old_vector)
{
  WWInterrupt ww_interrupt;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : sys_interrupt_reset_hook() : type = %d, old_vector = %p\n", type, old_vector);
  fflush(stdout);

  ww_interrupt = WonXSystem_GetWWInterrupt(WonX_GetWonXSystem());

  WWInterrupt_SetCallback(ww_interrupt, type, old_vector->callback);
  WWInterrupt_SetCS(ww_interrupt, type, old_vector->cs);
  WWInterrupt_SetDS(ww_interrupt, type, old_vector->ds);

  printf("call : sys_interrupt_reset_hook() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void sys_wait(unsigned int wait_time)
{
}

unsigned long int sys_get_tick_count(void)
{
  return (0);
}

void sys_sleep(void)
{
}

void sys_set_sleep_time(int sleep_time)
{
}

int sys_get_sleep_time(void)
{
  return (0);
}

void sys_set_awake_key(int pattern)
{
}

int sys_get_awake_key(void)
{
  return (0);
}

void sys_set_keepalive_int(int pattern)
{
}

void sys_get_ownerinfo(int size, char * buffer)
{
}

int sys_suspend(int core)
{
  return (0);
}

void sys_resume(int core)
{
}

void sys_set_remote(int remote)
{
}

unsigned int sys_get_remote(void)
{
  return (0);
}

void * sys_alloc_iram(void * p, unsigned int size)
{
  return (NULL);
}

void sys_free_iram(void * p)
{}

void * sys_get_my_iram(void)
{
  return (NULL);
}

unsigned int sys_get_version(void)
{
  return (0);
}

int sys_swap(int core)
{
  return (0);
}

void sys_set_resume(unsigned int flags)
{
}

unsigned int sys_get_resume(void)
{
  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
