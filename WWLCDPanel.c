/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWLCDPanelP.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWLCDPanel_GetWidth( WWLCDPanel p) { return (p->width ); }
int WWLCDPanel_GetHeight(WWLCDPanel p) { return (p->height); }
int WWLCDPanel_SetWidth( WWLCDPanel p, int n) { return (p->width  = n); }
int WWLCDPanel_SetHeight(WWLCDPanel p, int n) { return (p->height = n); }

unsigned char * WWLCDPanel_GetPixelMap(WWLCDPanel p) { return (p->pixel); }

/* LCDは１ピクセル16色(４ビット必要) */
int WWLCDPanel_GetPixel(WWLCDPanel lcd_panel, int x, int y)
{
  unsigned char pixel;

  if ( (x < 0) || (x > WWLCDPanel_GetWidth(lcd_panel) - 1) ||
       (y < 0) || (y > WWLCDPanel_GetHeight(lcd_panel) - 1) )
    return (-1);

  pixel = lcd_panel->pixel[y * (WWLCDPanel_GetWidth(lcd_panel) / 2) + x / 2];
  if (x % 2) pixel = pixel >> 4;
  pixel &= 0x0f;
  return ((int)pixel);
}

int WWLCDPanel_SetPixel(WWLCDPanel lcd_panel, int x, int y, int pixel)
{
  unsigned char p;
  int n;

  if ( (x < 0) || (x > WWLCDPanel_GetWidth(lcd_panel) - 1) ||
       (y < 0) || (y > WWLCDPanel_GetHeight(lcd_panel) - 1) )
    return (-1);

  p = 0x0f;
  if (x % 2) p = p << 4;
  n = y * (WWLCDPanel_GetWidth(lcd_panel) / 2) + x / 2;
  lcd_panel->pixel[n] &= ~p;

  p = ((unsigned char)pixel) & 0x0f;
  if (x % 2) p = p << 4;
  lcd_panel->pixel[n] |= p;

  return (pixel);
}

WWLCDPanel WWLCDPanel_Create(int width, int height)
{
  WWLCDPanel lcd_panel;
  int x, y;

  lcd_panel = (WWLCDPanel)malloc(sizeof(_WWLCDPanel));
  if (lcd_panel == NULL) Error("WWLCDPanel_Create", "Cannot allocate memory.");

  WWLCDPanel_SetWidth( lcd_panel, width);
  WWLCDPanel_SetHeight(lcd_panel, height);
  lcd_panel->pixel =
    (unsigned char *)malloc(sizeof(unsigned char) *
			    (WWLCDPanel_GetWidth(lcd_panel) / 2) *
			    WWLCDPanel_GetHeight(lcd_panel));

  for (y = 0; y < lcd_panel->height; y++) {
    for (x = 0; x < lcd_panel->width / 2; x++) {
      WWLCDPanel_SetPixel(lcd_panel, x, y, 0x00);
    }
  }

  return (lcd_panel);
}

WWLCDPanel WWLCDPanel_Destroy(WWLCDPanel lcd_panel)
{
  if (lcd_panel == NULL) return (NULL);
  if (lcd_panel->pixel) free(lcd_panel->pixel);
  free(lcd_panel);
  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
