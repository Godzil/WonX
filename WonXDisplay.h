#ifndef _WonXDisplay_h_INCLUDED_
#define _WonXDisplay_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonXDisplay * WonXDisplay;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include "XDisplay.h"
#include "WWDisplay.h"

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

XDisplay WonXDisplay_GetXDisplay(WonXDisplay wonx_display);
WWDisplay WonXDisplay_GetWWDisplay(WonXDisplay wonx_display);
WonXDisplay WonXDisplay_Create(int x_width, int x_height,
			       int ww_lcd_panel_width, int ww_lcd_panel_height,
			       int ww_screen_width, int ww_screen_height);
WonXDisplay WonXDisplay_Destroy(WonXDisplay wonx_display);
int WonXDisplay_PrintData(WonXDisplay wonx_display);
int WonXDisplay_DrawLCDWindow(WonXDisplay wonx_display);
int WonXDisplay_Sync(WonXDisplay wonx_display);
int WonXDisplay_Flush(WonXDisplay wonx_display);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
