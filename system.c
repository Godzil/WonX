/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/system.h"

#include "WonX.h"

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

void sys_interrupt_set_hook(int type, intvector_t * vector,
			    intvector_t * old_vector)
{
  WWInterrupt ww_interrupt;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
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

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void sys_interrupt_reset_hook(int type, intvector_t * old_vector)
{
  WWInterrupt ww_interrupt;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : sys_interrupt_reset_hook() : type = %d, old_vector = %p\n", type, old_vector);
  fflush(stdout);

  ww_interrupt = WonXSystem_GetWWInterrupt(WonX_GetWonXSystem());

  WWInterrupt_SetCallback(ww_interrupt, type, old_vector->callback);
  WWInterrupt_SetCS(ww_interrupt, type, old_vector->cs);
  WWInterrupt_SetDS(ww_interrupt, type, old_vector->ds);

  printf("call : sys_interrupt_reset_hook() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
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
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
