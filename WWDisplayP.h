#ifndef _WWDisplayP_h_INCLUDED_
#define _WWDisplayP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWDisplay.h"

/*****************************************************************************/
/* クラスの定義                                                              */
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

  /* ディスプレイの属性情報 */
  unsigned int color_mode; /* カラーモード */

  int sprite_enable; /* スプライト表示イネーブルフラグ */
  int sprite_window_enable; /* スプライトウインドウ機能イネーブルフラグ */
  int sprite_window_x;      /* スプライトウインドウ用 */
  int sprite_window_y;      /* スプライトウインドウ用 */
  int sprite_window_width;  /* スプライトウインドウ用 */
  int sprite_window_height; /* スプライトウインドウ用 */

  /* ボーダーカラーのパレット．カラーで必要 */
  WWPalette border_palette;
  /* ボーダーカラー．白黒の場合には，0〜7のカラーマップ番号 */
  int border_color;

  int foreground_color; /* モノクロフォント展開時の色 */
  int background_color; /* モノクロフォント展開時の色 */

  int sprite_start; /* スプライトの描画の指定 */
  int sprite_count; /* スプライトの描画の指定 */
} _WWDisplay;

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
