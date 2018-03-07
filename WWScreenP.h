#ifndef _WWScreenP_h_INCLUDED_
#define _WWScreenP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWScreen.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

/* �����꡼��Υޥ��ܤ��Ȥ˷�ޤ롤ɽ������ */
typedef struct _WWScreenCharacter {
  int horizontal; /* ������ȿž�ե饰 */
  int vertical; /* ������ȿž�ե饰 */
  WWPalette palette; /* �ѥ�å��ֹ桥0��15 �Υѥ�å��ֹ� */
  WWCharacter character; /* ɽ������饯�� */
} _WWScreenCharacter;

typedef struct _WWScreenCharacter * WWScreenCharacter;

typedef struct _WWScreen {
  int number;
  int width;
  int height;
  int roll_x;
  int roll_y;

  WWScreenCharacter * screen_characters;

  int enable; /* ɽ��/��ɽ���Υե饰 */

  int mode; /* ɽ���⡼�� */
  /* WW_SCREEN_DRAW_ALL, WW_SCREEN_INSIDE_ONLY, WW_SCREEN_OUTSIDE_ONLY �� */
  /* �����줫���ͤ���                                                */

  /* ɽ���ΰ�(�����꡼�󣲤Υ�����ɥ���ǽ�ѡ������꡼�󣱤Ǥ�̤����) */
  int draw_x, draw_y;
  int draw_width, draw_height;

} _WWScreen;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
