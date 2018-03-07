/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/key.h"

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

int key_press_check(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_press_check() : "); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_press_check() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_hit_check(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_hit_check() : "); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_hit_check() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_wait(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_wait() : "); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());

  /*
   * �ʲ��ϥۥåȥ��ݥåȤˤʤ�����Τ����!
   */

  ret = 0;
  do {
    XDisplay_Sync(x_display);
    ret = XDisplay_GetKeyPress(x_display);
  } while (ret == 0);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_wait() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void key_set_repeat(int rate, int delay)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_set_repeat() : rate = %d, delay = %d, ", rate, delay);
  fflush(stdout);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_set_repeat() : return value = none\n"); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int key_get_repeat(void)
{
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_get_repeat() : "); fflush(stdout);

  ret = 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_get_repeat() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int key_hit_check_with_repeat(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : key_hit_check_with_repeat() : "); fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : key_hit_check_with_repeat() : return value = 0x%04x\n",
	 (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
