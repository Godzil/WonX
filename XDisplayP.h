#ifndef _XDisplayP_h_INCLUDED_
#define _XDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "XDisplay.h"

#include <signal.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

/*
 * X �Υե���Ȥ����Ѥ��롥
 */
#define USE_X_FONT

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _XDisplay {

  XtAppContext app_context;
  Widget toplevel;
  Display * display;
  Window root_window;
  Colormap colormap;
  Cardinal depth;
  Dimension width, height;

  int size;

  Window lcd_window;

  Pixmap lcd_pixmap;

  GC copy_gc;
  GC color_gc[16]; /* ���ɽ���Ѥ�GC */

  /* 4096��ɽ���Ѥ�GC�Υǡ����١���(XFireworks ����ή��) */
  XColorGCDatabase color_gc_database;

#ifdef USE_X_FONT
  /* �ƥ����ȥ����꡼��ؤ�ʸ��ɽ���ѤΥե���� */
  Font font;
  GC font_gc;
#endif

  /* �����ξ��� */
  unsigned int key_press;

  /* LCD����Υ�٥� */
  int lcd_draw_level;

  /* ����׽��ϤΥե饰 */
  int color_map_print;
  int palette_print;
  int character_print;
  int sprite_print;

} _XDisplay;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
