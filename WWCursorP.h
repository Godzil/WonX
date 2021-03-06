#ifndef _WWCursorP_h_INCLUDED_
#define _WWCursorP_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWCursor.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWCursor {
  int on;            /* 表示/非表示のフラグ */
  int x, y;          /* カーソル座標 */
  int width, height; /* カーソルのサイズ */
  int interval;      /* 点滅周期 */
  WWPalette palette; /* カーソル表示用パレット */
} _WWCursor;

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
