/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdlib.h>

#include "sys/system.h"

#include "Wonx.h"

/*****************************************************************************/
/* �ߴ��ؿ������                                                            */
/*****************************************************************************/

/*
 * X�����ФȤ�Ʊ�������������Ȥ�ʤ��ʤ�ʤɤ����꤬�ͤ�����Τǡ�
 * �ߴ��ؿ��������� UNIXTimer_Pause(), UNIXTimer_Unpause() �Ǥ����ꡤ
 * �����޳����ߤ�����ߤ��ƽ�����Ԥ����ޤ���unpause ����ޤ��ˡ�
 * ���ʤ餺 sync ����褦�ˤ��롥
 */

/*
 * �����ޤΰ����ߤΣ��Ų�������꤬�ФƤ���Τǡ�
 * �ߴ��ؿ�����ߴ��ؿ���Ƥ�ǤϤ����ʤ���
 * (�����ߤϥͥ��Ȥ���뤬����������)
 * �����褦�ʽ����򤹤�ؿ��ξ��ϡ�ɬ�� static ���̴ؿ��˽�����ޤȤᡤ
 * ���ä���ƤӽФ��褦�ˤ��뤳�ȡ�
 * ������ɽ��������⤢�뤷�͡�
 */

void sys_interrupt_set_hook(int type, intvector_t * intvector,
			    intvector_t * last_intvector)
{
  WWInterrupt ww_interrupt;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sys_interrupt_set_hook() : type = %d, intvector = %p, last_intvector = %p\n", type, intvector, last_intvector);
  fflush(stdout);

  ww_interrupt = WonxSystem_GetWWInterrupt(Wonx_GetWonxSystem());

  last_intvector->callback = WWInterrupt_GetCallback(ww_interrupt, type);
  last_intvector->cs = WWInterrupt_GetCS(ww_interrupt, type);
  last_intvector->ds = WWInterrupt_GetDS(ww_interrupt, type);

  WWInterrupt_SetCallback(ww_interrupt, type, intvector->callback);
  WWInterrupt_SetCS(ww_interrupt, type, intvector->cs);
  WWInterrupt_SetDS(ww_interrupt, type, intvector->ds);

  printf("call : sys_interrupt_set_hook() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void sys_interrupt_reset_hook(int type, intvector_t * last_intvector)
{
  WWInterrupt ww_interrupt;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sys_interrupt_reset_hook() : type = %d, last_intvector = %p\n", type, last_intvector);
  fflush(stdout);

  ww_interrupt = WonxSystem_GetWWInterrupt(Wonx_GetWonxSystem());

  WWInterrupt_SetCallback(ww_interrupt, type, last_intvector->callback);
  WWInterrupt_SetCS(ww_interrupt, type, last_intvector->cs);
  WWInterrupt_SetDS(ww_interrupt, type, last_intvector->ds);

  printf("call : sys_interrupt_reset_hook() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void sys_wait(unsigned int time)
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

int  sys_get_sleep_time(void)
{
  return (0);
}

void sys_set_awake_key(int awake_key_pattern)
{
}

int  sys_get_awake_key(void)
{
  return (0);
}

void sys_set_keepalive_int(int keepalive_pattern)
{
}

void sys_get_ownerinfo(int size, char *buffer)
{
}

int  sys_suspend(int core)
{
  return (0);
}

void sys_resume(int core)
{
}

void sys_set_remote(int remote_enable)
{
}

unsigned int sys_get_remote(void)
{
  return (0);
}

void * sys_alloc_iram(void *pointer, unsigned size)
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
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
