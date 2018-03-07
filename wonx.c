#include <stdio.h>
#include <stdlib.h>

#include "wonx/wonx.h"

#include "WonX.h"
#include "WonXDisplay.h"
#include "WWDisplay.h"
#include "XDisplay.h"

#include "WWColorMap.h"
#include "WWPalette.h"
#include "WWCharacter.h"
#include "WWSprite.h"

/*****************************************************************************/
/* �����˸������� WonX �Υ����ӥ��ؿ�                                        */
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

/* ���顼�ޥå׾���ν��� */
void wonx_print_colormap_data(void)
{
  WWDisplay ww_display;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_colormap_data() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  WWColorMap_PrintData(WWDisplay_GetColorMap(ww_display), stdout);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_colormap_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* �ѥ�åȾ���ν����������ؿ� */
static void _print_palette_data(int n)
{
  WWDisplay ww_display;
  WWPalette ww_palette;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_palette = WWDisplay_GetPalette(ww_display, n);
  WWPalette_PrintData(ww_palette, ww_display, stdout);
  return;
}

/* �ѥ�åȾ���ν��� */
void wonx_print_palette_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_palette_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 16 - 1))
    WonX_Error("wonx_print_palette_data", "number is out of range.");
  _print_palette_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_palette_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ���٤ƤΥѥ�åȾ������� */
void wonx_print_all_palette_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_palette_data() : \n");
  fflush(stdout);

  for (n = 0; n < 16; n++) _print_palette_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_palette_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ����饯������ν����������ؿ� */
static void _print_character_data(int n)
{
  WWDisplay ww_display;
  WWCharacter ww_character;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_character = WWDisplay_GetCharacter(ww_display, n);
  WWCharacter_PrintData(ww_character, ww_display, stdout);
  return;
}

/* ����饯������ν��� */
void wonx_print_character_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_character_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 512 - 1))
    WonX_Error("wonx_print_character_data", "number is out of range.");
  _print_character_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_character_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ���٤ƤΥ���饯���������� */
void wonx_print_all_character_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_character_data() : \n");
  fflush(stdout);

  for (n = 0; n < 512; n++) _print_character_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_character_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ���ץ饤�Ⱦ���ν����������ؿ� */
static void _print_sprite_data(int n)
{
  WWDisplay ww_display;
  WWSprite ww_sprite;
  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_sprite = WWDisplay_GetSprite(ww_display, n);
  WWSprite_PrintData(ww_sprite, stdout);
  return;
}

/* ���ץ饤�Ⱦ���ν��� */
void wonx_print_sprite_data(int n)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_sprite_data() : number = %d\n", n);
  fflush(stdout);

  if ((n < 0) || (n > 128 - 1))
    WonX_Error("wonx_print_sprite_data", "number is out of range.");
  _print_sprite_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_sprite_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ���٤ƤΥ��ץ饤�Ⱦ������� */
void wonx_print_all_sprite_data(void)
{
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_print_all_sprite_data() : \n");
  fflush(stdout);

  for (n = 0; n < 128; n++) _print_sprite_data(n);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_print_all_sprite_data() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/* ���ߤ�ɽ��/��ɽ���Υ�٥�μ�����(1�ʾ��ɽ����0�ʲ�����ɽ��) */
int wonx_get_lcddraw_level(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_get_lcddraw_level() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_GetLCDDrawLevel(x_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wonx_get_lcddraw_level() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* ���ߤ�ɽ��/��ɽ���Υ�٥������ */
int wonx_set_lcddraw_level(int level)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_set_lcddraw_level() : level = %d\n", level);
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_SetLCDDrawLevel(x_display, level);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_set_lcddraw_level() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* ɽ����٥�򲼤��� */
int wonx_lcddraw_level_down(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_lcddraw_level_down() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_LCDDrawLevelDown(x_display);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_lcddraw_level_down() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/* ɽ����٥��夲�� */
int wonx_lcddraw_level_up(void)
{
  XDisplay x_display;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wonx_lcddraw_level_up() : \n");
  fflush(stdout);

  x_display = WonXDisplay_GetXDisplay(WonX_GetWonXDisplay());
  ret = XDisplay_LCDDrawLevelUp(x_display);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wonx_lcddraw_level_up() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
