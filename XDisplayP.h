#ifndef _XDisplayP_h_INCLUDED_
#define _XDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "XDisplay.h"

#include <signal.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

/*
 * X のフォントを利用する．
 */
#define USE_X_FONT

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
  GC color_gc[16]; /* 白黒表示用のGC */

  /* 4096色表示用のGCのデータベース(XFireworks から流用) */
  XColorGCDatabase color_gc_database;

#ifdef USE_X_FONT
  /* テキストスクリーンへの文字表示用のフォント */
  Font font;
  GC font_gc;
#endif

  /* キーの状態 */
  unsigned int key_press;

  /* LCD描画のレベル */
  int lcd_draw_level;

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
