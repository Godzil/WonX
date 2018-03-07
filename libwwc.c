/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_configure.h"

#include "wonx/libwwc.h"

#include "WonX.h"

/*****************************************************************************/
/* �ߴ��ؿ������                                                            */
/*****************************************************************************/

/*
 * void * �ǥǡ������Ϥ��ؿ��ϡ�����ְ㤨��Х��������ǽ��������Τǡ�
 * void * ��Ŭ�ڤʷ����֤������Ƥ��롥
 */

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

unsigned int wwc_set_color_mode(unsigned int mode)
{
  WWDisplay ww_display;
  unsigned int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_set_color_mode() : mode = 0x%04x\n", (int)mode);
  fflush(stdout);

  switch (mode) {
  case COLOR_MODE_GRAYSCALE :
  case COLOR_MODE_4COLOR :
  case COLOR_MODE_16COLOR :
  case COLOR_MODE_16PACKED :
    break;
  default :
    WonX_Error("wwc_set_color_mode", "unknown color mode.");
  }

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  ret = WWDisplay_SetColorMode(ww_display, mode);

  /* �����������ˤϡ������褹�� */
  WWLCDPanel_SetAllDraw(WWDisplay_GetLCDPanel(ww_display));

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wwc_set_color_mode() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

unsigned int wwc_get_color_mode(void)
{
  WWDisplay ww_display;
  unsigned int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_get_color_mode() : \n"); fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  ret = WWDisplay_GetColorMode(ww_display);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wwc_get_color_mode() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void wwc_palette_set_color(unsigned int palette_num, unsigned int color_num, unsigned int rgb)
{
  WWDisplay ww_display;
  WWPalette ww_palette;
  unsigned short int red, green, blue;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_palette_set_color() : palette_num = %u, color_num = %u, rgb = 0x%04x\n",
	 (int)palette_num, (int)color_num, (int)rgb);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_palette = WWDisplay_GetPalette(ww_display, palette_num);
  red   = (rgb >> 8) & 0x0f;
  green = (rgb >> 4) & 0x0f;
  blue  = (rgb >> 0) & 0x0f;
  WWPalette_SetRed(  ww_palette, color_num, red  );
  WWPalette_SetGreen(ww_palette, color_num, green);
  WWPalette_SetBlue( ww_palette, color_num, blue );

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wwc_palette_set_color() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

unsigned int wwc_palette_get_color(unsigned int palette_num, unsigned int color_num)
{
  WWDisplay ww_display;
  WWPalette ww_palette;
  unsigned short int red, green, blue;
  unsigned short int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_palette_get_color() : palette_num = %u, color_num = %u\n",
	 (int)palette_num, (int)color_num);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_palette = WWDisplay_GetPalette(ww_display, palette_num);

  red   = WWPalette_GetRed(  ww_palette, color_num);
  green = WWPalette_GetGreen(ww_palette, color_num);
  blue  = WWPalette_GetBlue( ww_palette, color_num);

  ret = (red << 8) | (green << 4) | (blue << 0);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wwc_palette_get_color() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*
 * data �� long int �� 8 �� 32 �Х��ȡ�
 */

void wwc_font_set_colordata(unsigned int number, unsigned int count,
			    unsigned long int * data)
{
  WWCharacter ww_character;
  WWDisplay ww_display;
  int i, j, n;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_font_set_colordata() : number = %u, count = %u, data = %p\n",
	 (int)number, (int)count, (void *)data);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  n = 0;
  for (i = 0; i < count; i++) {
    ww_character = WWDisplay_GetCharacter(ww_display, number + i);
    for (j = 0; j < 8; j++) {
      WWCharacter_SetBitmapAsLongInt(ww_character, j, data[n]);
      n++;
    }
  }

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wwc_font_set_colordata() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/*
 * data �� long int �� 8 �� 32 �Х��ȡ�
 */

void wwc_font_get_colordata(unsigned int number, unsigned int count,
			    unsigned long int * data)
{
  WWCharacter ww_character;
  WWDisplay ww_display;
  int i, j, n;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_font_get_colordata() : number = %u, count = %u, data = %p\n",
	 (int)number, (int)count, (void *)data);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  n = 0;
  for (i = 0; i < count; i++) {
    ww_character = WWDisplay_GetCharacter(ww_display, number + i);
    for (j = 0; j < 8; j++) {
      data[n] = WWCharacter_GetBitmapAsLongInt(ww_character, j);
      n++;
    }
  }

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wwc_font_get_colordata() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

unsigned int wwc_get_hardarch(void)
{
  WWDisplay ww_display;
  unsigned int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_get_hardarch() : \n"); fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  ret = WONX_DEFAULT_ARCH;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : wwc_get_hardarch() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void wwc_clear_font(void)
{
  WWDisplay ww_display;
  WWCharacter ww_character;
  int i;

  if (!WonX_IsCreated()) WonX_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : wwc_clear_font() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  for (i = 0; i < 512; i++) {
    ww_character = WWDisplay_GetCharacter(ww_display, i);
    WWCharacter_ClearAllPixels(ww_character);
  }

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : wwc_clear_font() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
