#ifndef _XDisplayP_h_INCLUDED_
#define _XDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "XDisplay.h"

#include <signal.h>

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

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
  GC color_gc[16];

  /* �ƥ����ȥ����꡼��ؤ�ʸ��ɽ���ѤΥե���� */
  Font font;
  GC font_gc;

  /* �����ξ��� */
  unsigned int key_press;

  /* LCD����Υե饰 */
  int lcd_draw;

} _XDisplay;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/