#ifndef _WonXDisplay_h_INCLUDED_
#define _WonXDisplay_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "XDisplay.h"
#include "WWDisplay.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonXDisplay * WonXDisplay;

XDisplay WonXDisplay_GetXDisplay(WonXDisplay wonx_display);
WWDisplay WonXDisplay_GetWWDisplay(WonXDisplay wonx_display);
WonXDisplay WonXDisplay_Create(int x_width, int x_height,
			       int ww_lcd_panel_width, int ww_lcd_panel_height,
			       int ww_screen_width, int ww_screen_height);
int WonXDisplay_Sync(WonXDisplay wonx_display);
int WonXDisplay_Flush(WonXDisplay wonx_display);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
