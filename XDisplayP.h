#ifndef _XDisplayP_h_INCLUDED_
#define _XDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
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
/* クラスの定義                                                              */
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

  /* テキストスクリーンへの文字表示用のフォント */
  Font font;
  GC font_gc;

  /* キーの状態 */
  unsigned int key_press;

  /* LCD描画のフラグ */
  int lcd_draw;

  /* ダンプ出力のフラグ */
  int color_map_print;
  int palette_print;
  int character_print;
  int sprite_print;

} _XDisplay;

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
