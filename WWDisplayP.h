#ifndef _WWDisplayP_h_INCLUDED_
#define _WWDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWDisplay.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWDisplay {

  WWColorMap color_map;
  WWPalette palette[16];
  WWCharacter character[512];
  WWSprite sprite[128];
  WWScreen screen[2];
  WWLCDPanel lcd_panel;
  WWText text;
  WWCursor cursor;

  /* �ǥ����ץ쥤��°������ */
  unsigned int color_mode; /* ���顼�⡼�� */

  int sprite_enable; /* ���ץ饤��ɽ�����͡��֥�ե饰 */
  int sprite_window_enable; /* ���ץ饤�ȥ�����ɥ���ǽ���͡��֥�ե饰 */
  int sprite_window_x;      /* ���ץ饤�ȥ�����ɥ��� */
  int sprite_window_y;      /* ���ץ饤�ȥ�����ɥ��� */
  int sprite_window_width;  /* ���ץ饤�ȥ�����ɥ��� */
  int sprite_window_height; /* ���ץ饤�ȥ�����ɥ��� */

  /* �ܡ��������顼�Υѥ�åȡ����顼��ɬ�� */
  WWPalette border_palette;
  /* �ܡ��������顼������ξ��ˤϡ�0��7�Υ��顼�ޥå��ֹ� */
  int border_color;

  int foreground_color; /* ��Υ���ե����Ÿ�����ο� */
  int background_color; /* ��Υ���ե����Ÿ�����ο� */

  int sprite_start; /* ���ץ饤�Ȥ�����λ��� */
  int sprite_count; /* ���ץ饤�Ȥ�����λ��� */
} _WWDisplay;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
