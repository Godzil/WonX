#ifndef _WonxDisplay_h_INCLUDED_
#define _WonxDisplay_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "XDisplay.h"
#include "WWDisplay.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonxDisplay * WonxDisplay;

XDisplay WonxDisplay_GetXDisplay(WonxDisplay wonx_display);
WWDisplay WonxDisplay_GetWWDisplay(WonxDisplay wonx_display);
WonxDisplay WonxDisplay_Create(int x_width, int x_height,
			       int ww_lcd_panel_width, int ww_lcd_panel_height,
			       int ww_screen_width, int ww_screen_height);
int WonxDisplay_Sync(WonxDisplay wonx_display);
int WonxDisplay_Flush(WonxDisplay wonx_display);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
