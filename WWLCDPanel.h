#ifndef _WWLCDPanel_h_INCLUDED_
#define _WWLCDPanel_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWLCDPanel * WWLCDPanel;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include <stdlib.h>

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

int WWLCDPanel_GetWidth( WWLCDPanel p);
int WWLCDPanel_GetHeight(WWLCDPanel p);
int WWLCDPanel_SetWidth( WWLCDPanel p, int n);
int WWLCDPanel_SetHeight(WWLCDPanel p, int n);

int WWLCDPanel_ResetCurrent(WWLCDPanel p);
int WWLCDPanel_ReverseCurrent(WWLCDPanel p);
int WWLCDPanel_ResetAllDraw(WWLCDPanel p);
int WWLCDPanel_SetAllDraw(WWLCDPanel p);
int WWLCDPanel_IsAllDraw(WWLCDPanel p);

unsigned short int * WWLCDPanel_GetPixelMap(WWLCDPanel p);
unsigned short int WWLCDPanel_GetPixel(WWLCDPanel lcd_panel, int x, int y);
unsigned short int WWLCDPanel_SetPixel(WWLCDPanel lcd_panel, int x, int y,
				       unsigned short int pixel);
int WWLCDPanel_IsPixelChanged(WWLCDPanel lcd_panel, int x, int y);
WWLCDPanel WWLCDPanel_Create(int width, int height);
WWLCDPanel WWLCDPanel_Destroy(WWLCDPanel lcd_panel);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
