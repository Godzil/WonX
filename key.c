/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/key.h"

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

int key_press_check(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_press_check() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_hit_check(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_hit_check() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_wait(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_wait() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());

  /*
   * �ʲ��ϥۥåȥ��ݥåȤˤʤ�����Τ����!
   */

  ret = 0;
  do {
    XDisplay_Sync(x_display);
    ret = XDisplay_GetKeyPress(x_display);
  } while (ret == 0);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void key_set_repeat(int rate, int delay)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_set_repeat() : rate = %d, delay = %d, ", rate, delay);
  fflush(stdout);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = none\n"); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

int key_get_repeat(void)
{
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_get_repeat() : "); fflush(stdout);

  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int key_hit_check_with_repeat(void)
{
  XDisplay x_display;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : key_hit_check_with_repeat() : "); fflush(stdout);

  x_display = WonxDisplay_GetXDisplay(Wonx_GetWonxDisplay());
  XDisplay_Sync(x_display);

  ret = XDisplay_GetKeyPress(x_display);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("return value = 0x%04x\n", (int)ret); fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
