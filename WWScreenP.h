#ifndef _WWScreenP_h_INCLUDED_
#define _WWScreenP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWScreen.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

/* スクリーンのマス目ごとに決まる，表示情報 */
typedef struct _WWScreenCharacter {
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  WWPalette palette; /* パレット番号．0〜15 のパレット番号 */
  WWCharacter character; /* 表示キャラクタ */
} _WWScreenCharacter;

typedef struct _WWScreenCharacter * WWScreenCharacter;

typedef struct _WWScreen {
  int number;
  int width;
  int height;
  int roll_x;
  int roll_y;

  WWScreenCharacter * screen_characters;

  int enable; /* 表示/非表示のフラグ */

  int mode; /* 表示モード */
  /* WW_SCREEN_DRAW_ALL, WW_SCREEN_INSIDE_ONLY, WW_SCREEN_OUTSIDE_ONLY の */
  /* いずれかの値を取る                                                */

  /* 表示領域(スクリーン２のウインドウ機能用．スクリーン１では未使用) */
  int draw_x, draw_y;
  int draw_width, draw_height;

} _WWScreen;

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
