/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWLCDPanelP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWLCDPanel_GetWidth( WWLCDPanel p) { return (p->width ); }
int WWLCDPanel_GetHeight(WWLCDPanel p) { return (p->height); }
int WWLCDPanel_SetWidth( WWLCDPanel p, int n) { return (p->width  = n); }
int WWLCDPanel_SetHeight(WWLCDPanel p, int n) { return (p->height = n); }

int WWLCDPanel_ResetCurrent(WWLCDPanel p)
{
  return (p->current = 0);
}

int WWLCDPanel_ReverseCurrent(WWLCDPanel p)
{
  return (p->current = 1 - p->current);
}

int WWLCDPanel_ResetAllDraw(WWLCDPanel p) { return (p->all_draw = 0); }
int WWLCDPanel_SetAllDraw(WWLCDPanel p)   { return (p->all_draw = 1); }
int WWLCDPanel_IsAllDraw(WWLCDPanel p)   { return (p->all_draw); }

unsigned short int * WWLCDPanel_GetPixelMap(WWLCDPanel p)
{
  return (p->pixel[p->current]);
}

/* LCDは１ピクセル4096色(12ビット必要) */
static unsigned short int WWLCDPanel_GetPixelByCurrent(WWLCDPanel lcd_panel,
						       int current,
						       int x, int y)
{
  unsigned short int pixel;

  if ( (x < 0) || (x > WWLCDPanel_GetWidth( lcd_panel) - 1) ||
       (y < 0) || (y > WWLCDPanel_GetHeight(lcd_panel) - 1) )
    return (-1);

  pixel = lcd_panel->pixel[current][y * WWLCDPanel_GetWidth(lcd_panel) + x];
  return ((int)pixel);
}

static unsigned short int WWLCDPanel_GetOldPixel(WWLCDPanel lcd_panel,
						 int x, int y)
{
  return (WWLCDPanel_GetPixelByCurrent(lcd_panel,
				       1 - lcd_panel->current, x, y));
}

unsigned short int WWLCDPanel_GetPixel(WWLCDPanel lcd_panel, int x, int y)
{
  return (WWLCDPanel_GetPixelByCurrent(lcd_panel, lcd_panel->current, x, y));
}

unsigned short int WWLCDPanel_SetPixel(WWLCDPanel lcd_panel, int x, int y,
				       unsigned short int pixel)
{
  unsigned short int p;
  int n;

  if ( (x < 0) || (x > WWLCDPanel_GetWidth( lcd_panel) - 1) ||
       (y < 0) || (y > WWLCDPanel_GetHeight(lcd_panel) - 1) )
    return (-1);

  p = pixel & 0x0fff;
  n = y * WWLCDPanel_GetWidth(lcd_panel) + x;
  lcd_panel->pixel[lcd_panel->current][n] = p;

  return (p);
}

int WWLCDPanel_IsPixelChanged(WWLCDPanel lcd_panel, int x, int y)
{
  unsigned short int old_pixel;
  unsigned short int current_pixel;

  if (WWLCDPanel_IsAllDraw(lcd_panel)) return (1);
  old_pixel = WWLCDPanel_GetOldPixel(lcd_panel, x, y);
  current_pixel = WWLCDPanel_GetPixel(lcd_panel, x, y);

  return (!(old_pixel == current_pixel));
}

WWLCDPanel WWLCDPanel_Create(int width, int height)
{
  WWLCDPanel lcd_panel;
  int x, y, i;
  unsigned short int * p;

  lcd_panel = (WWLCDPanel)malloc(sizeof(_WWLCDPanel));
  if (lcd_panel == NULL)
    WonX_Error("WWLCDPanel_Create", "Cannot allocate memory.");

  WWLCDPanel_SetWidth( lcd_panel, width);
  WWLCDPanel_SetHeight(lcd_panel, height);

  for (i = 0; i < 2; i++) {
    p = (unsigned short int *)malloc(sizeof(unsigned short int) *
				     WWLCDPanel_GetWidth(lcd_panel) *
				     WWLCDPanel_GetHeight(lcd_panel));
    if (p == NULL) WonX_Error("WWLCDPanel_Create", "Cannot allocate memory.");
    lcd_panel->pixel[i] = p;
  }

  for (y = 0; y < lcd_panel->height; y++) {
    for (x = 0; x < lcd_panel->width / 2; x++) {
      WWLCDPanel_SetPixel(lcd_panel, x, y, 0);
    }
  }

  WWLCDPanel_ResetCurrent(lcd_panel);
  WWLCDPanel_SetAllDraw(lcd_panel); /* 初回は全画面を描画する */

  return (lcd_panel);
}

WWLCDPanel WWLCDPanel_Destroy(WWLCDPanel lcd_panel)
{
  int i;
  if (lcd_panel == NULL) return (NULL);
  for (i = 0; i < 2; i++) {
    if (lcd_panel->pixel[i]) free(lcd_panel->pixel[i]);
  }
  free(lcd_panel);
  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
