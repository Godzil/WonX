/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonXDisplayP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

XDisplay WonXDisplay_GetXDisplay(WonXDisplay wonx_display)
{ return (wonx_display->x_display); }
WWDisplay WonXDisplay_GetWWDisplay(WonXDisplay wonx_display)
{ return (wonx_display->ww_display); }

static XDisplay WonXDisplay_SetXDisplay(WonXDisplay wonx_d, XDisplay xd)
{ return (wonx_d->x_display = xd); }
static WWDisplay WonXDisplay_SetWWDisplay(WonXDisplay wonx_d, WWDisplay wd)
{ return (wonx_d->ww_display = wd); }

WonXDisplay WonXDisplay_Create(int x_width, int x_height,
			       int ww_lcd_panel_width, int ww_lcd_panel_height,
			       int ww_screen_width, int ww_screen_height)
{
  WonXDisplay wonx_display;
  WWDisplay ww_display;
  XDisplay x_display;

  wonx_display = (WonXDisplay)malloc(sizeof(_WonXDisplay));
  if (wonx_display == NULL)
    WonX_Error("WonXDisplay_Create", "Cannot allocate memory.");

  ww_display = WWDisplay_Create(ww_lcd_panel_width, ww_lcd_panel_height,
				ww_screen_width, ww_screen_height);
  if (ww_display == NULL)
    WonX_Error("WonXDisplay_Create", "Cannot create WonderWitch display.");
  WonXDisplay_SetWWDisplay(wonx_display, ww_display);

  x_display = XDisplay_Create(x_width, x_height);
  if (x_display == NULL)
    WonX_Error("WonXDisplay_Create", "Cannot create X display.");
  WonXDisplay_SetXDisplay(wonx_display, x_display);

  return (wonx_display);
}

int WonXDisplay_PrintData(WonXDisplay wonx_display)
{
  int i;
  XDisplay x_display;
  WWDisplay ww_display;

  x_display = WonXDisplay_GetXDisplay(wonx_display);
  ww_display = WonXDisplay_GetWWDisplay(wonx_display);

  if (XDisplay_GetColorMapPrint(x_display)) {
    WWColorMap_PrintData(WWDisplay_GetColorMap(ww_display), stdout);
    fflush(stdout);
    XDisplay_SetColorMapPrint(x_display, 0);
  }

  if (XDisplay_GetPalettePrint(x_display)) {
    for (i = 0; i < 16; i++) {
      WWPalette_PrintData(WWDisplay_GetPalette(ww_display, i),
			  ww_display, stdout);
      fflush(stdout);
    }
    XDisplay_SetPalettePrint(x_display, 0);
  }

  if (XDisplay_GetCharacterPrint(x_display)) {
    for (i = 0; i < 512; i++) {
      WWCharacter_PrintData(WWDisplay_GetCharacter(ww_display, i),
			    ww_display, stdout);
      fflush(stdout);
    }
    XDisplay_SetCharacterPrint(x_display, 0);
  }

  if (XDisplay_GetSpritePrint(x_display)) {
    for (i = 0; i < 128; i++) {
      WWSprite_PrintData(WWDisplay_GetSprite(ww_display, i), stdout);
      fflush(stdout);
    }
    XDisplay_SetSpritePrint(x_display, 0);
  }

  return (0);
}

int WonXDisplay_Sync(WonXDisplay wonx_display)
{
  XDisplay x_display;

  WonXDisplay_PrintData(wonx_display);

  x_display = WonXDisplay_GetXDisplay(wonx_display);

  XDisplay_Sync(x_display);

  return (0);
}

int WonXDisplay_Flush(WonXDisplay wonx_display)
{
  XDisplay x_display;
  WWDisplay ww_display;
  WWLCDPanel ww_lcd_panel;

  x_display = WonXDisplay_GetXDisplay(wonx_display);
  ww_display = WonXDisplay_GetWWDisplay(wonx_display);

  if (XDisplay_GetLCDDraw(x_display)) {
    WWDisplay_DrawLCDPanel(ww_display);
    ww_lcd_panel = WWDisplay_GetLCDPanel(ww_display);
    XDisplay_DrawLCDWindow(x_display, ww_display, ww_lcd_panel);
  }

  WonXDisplay_Sync(wonx_display);

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
