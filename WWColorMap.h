#ifndef _WWColorMap_h_INCLUDED_
#define _WWColorMap_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdlib.h>

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWColorMap * WWColorMap;

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

WWColorMap WWColorMap_Create(int * lcd_colors);
WWColorMap WWColorMap_Destroy(WWColorMap color_map);
int * WWColorMap_GetLCDColors(WWColorMap color_map, int * lcd_colors);
int WWColorMap_SetLCDColors(WWColorMap color_map, int * lcd_colors);
int WWColorMap_GetLCDColor(WWColorMap color_map, int color);
int WWColorMap_SetLCDColor(WWColorMap color_map, int color, int lcd_color);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
