#ifndef _WWColorMap_h_INCLUDED_
#define _WWColorMap_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdlib.h>

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWColorMap * WWColorMap;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

WWColorMap WWColorMap_Create(int * lcd_colors);
WWColorMap WWColorMap_Destroy(WWColorMap color_map);
int * WWColorMap_GetLCDColors(WWColorMap color_map, int * lcd_colors);
int WWColorMap_SetLCDColors(WWColorMap color_map, int * lcd_colors);
int WWColorMap_GetLCDColor(WWColorMap color_map, int color);
int WWColorMap_SetLCDColor(WWColorMap color_map, int color, int lcd_color);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
