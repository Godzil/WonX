/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonxDisplayP.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

XDisplay WonxDisplay_GetXDisplay(WonxDisplay wonx_display)
{ return (wonx_display->x_display); }
WWDisplay WonxDisplay_GetWWDisplay(WonxDisplay wonx_display)
{ return (wonx_display->ww_display); }

static XDisplay WonxDisplay_SetXDisplay(WonxDisplay wonx_d, XDisplay xd)
{ return (wonx_d->x_display = xd); }
static WWDisplay WonxDisplay_SetWWDisplay(WonxDisplay wonx_d, WWDisplay wd)
{ return (wonx_d->ww_display = wd); }

WonxDisplay WonxDisplay_Create(int x_width, int x_height,
			       int ww_lcd_panel_width, int ww_lcd_panel_height,
			       int ww_screen_width, int ww_screen_height)
{
  WonxDisplay wonx_display;
  WWDisplay ww_display;
  XDisplay x_display;

  wonx_display = (WonxDisplay)malloc(sizeof(_WonxDisplay));
  if (wonx_display == NULL)
    Error("WonxDisplay_Create", "Cannot allocate memory.");

  ww_display = WWDisplay_Create(ww_lcd_panel_width, ww_lcd_panel_height,
				ww_screen_width, ww_screen_height);
  if (ww_display == NULL)
    Error("WonxDisplay_Create", "Cannot create WonderWitch display.");
  WonxDisplay_SetWWDisplay(wonx_display, ww_display);

  x_display = XDisplay_Create(x_width, x_height);
  if (x_display == NULL)
    Error("WonxDisplay_Create", "Cannot create X display.");
  WonxDisplay_SetXDisplay(wonx_display, x_display);

  return (wonx_display);
}

int WonxDisplay_Flush(WonxDisplay wonx_display)
{
  XDisplay x_display;
  WWDisplay ww_display;
  WWLCDPanel ww_lcd_panel;

  x_display = WonxDisplay_GetXDisplay(wonx_display);
  ww_display = WonxDisplay_GetWWDisplay(wonx_display);

  if (XDisplay_GetLCDDraw(x_display)) {
    WWDisplay_DrawLCDPanel(ww_display);
    ww_lcd_panel = WWDisplay_GetLCDPanel(ww_display);
    XDisplay_DrawLCDWindow(x_display, ww_lcd_panel);
  }

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
