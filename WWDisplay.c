/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWDisplayP.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* メンバの取得                                                              */
/*===========================================================================*/

WWColorMap WWDisplay_GetColorMap(WWDisplay d) { return (d->color_map); }
WWPalette WWDisplay_GetPalette(WWDisplay d, int n) { return (d->palette[n]); }
WWCharacter WWDisplay_GetCharacter(WWDisplay d, int n)
{ return (d->character[n]); }
WWSprite WWDisplay_GetSprite(WWDisplay d, int n) { return (d->sprite[n]); }
WWScreen WWDisplay_GetScreen(WWDisplay d, int n) { return (d->screen[n]); }
WWLCDPanel WWDisplay_GetLCDPanel(WWDisplay d) { return (d->lcd_panel); }

int WWDisplay_GetSpriteEnable(WWDisplay d) { return (d->sprite_enable); }
int WWDisplay_GetSpriteWindowEnable(WWDisplay d)
{ return (d->sprite_window_enable); }

int WWDisplay_GetSpriteWindowX(WWDisplay d)
{ return (d->sprite_window_x); }
int WWDisplay_GetSpriteWindowY(WWDisplay d)
{ return (d->sprite_window_y); }
int WWDisplay_GetSpriteWindowWidth(WWDisplay d)
{ return (d->sprite_window_width); }
int WWDisplay_GetSpriteWindowHeight(WWDisplay d)
{ return (d->sprite_window_height); }

int WWDisplay_GetBorder(WWDisplay d) { return (d->border); }

int WWDisplay_GetForegroundColor(WWDisplay d) { return (d->foreground_color); }
int WWDisplay_GetBackgroundColor(WWDisplay d) { return (d->background_color); }

int WWDisplay_GetSpriteStart(WWDisplay d) { return (d->sprite_start); }
int WWDisplay_GetSpriteCount(WWDisplay d) { return (d->sprite_count); }

/*===========================================================================*/
/* メンバの設定                                                              */
/*===========================================================================*/

WWColorMap WWDisplay_SetColorMap(WWDisplay d, WWColorMap cm)
{ return (d->color_map = cm); }
WWPalette WWDisplay_SetPalette(WWDisplay d, int n, WWPalette p)
{ return (d->palette[n] = p); }
WWCharacter WWDisplay_SetCharacter(WWDisplay d, int n, WWCharacter c)
{ return (d->character[n] = c); }
WWSprite WWDisplay_SetSprite(WWDisplay d, int n, WWSprite s)
{ return (d->sprite[n] = s); }
WWScreen WWDisplay_SetScreen(WWDisplay d, int n, WWScreen s)
{ return (d->screen[n] = s); }
WWLCDPanel WWDisplay_SetLCDPanel(WWDisplay d, WWLCDPanel p)
{ return (d->lcd_panel = p); }

int WWDisplay_SetSpriteEnable(WWDisplay d, int f)
{ return (d->sprite_enable = f); }
int WWDisplay_SetSpriteWindowEnable(WWDisplay d, int f)
{ return (d->sprite_window_enable = f); }

int WWDisplay_SetSpriteWindowX(WWDisplay d, int n)
{ return (d->sprite_window_x = n); }
int WWDisplay_SetSpriteWindowY(WWDisplay d, int n)
{ return (d->sprite_window_y = n); }
int WWDisplay_SetSpriteWindowWidth(WWDisplay d, int n)
{ return (d->sprite_window_width = n); }
int WWDisplay_SetSpriteWindowHeight(WWDisplay d, int n)
{ return (d->sprite_window_height = n); }

int WWDisplay_SetBorder(WWDisplay d, int b) { return (d->border = b); }

int WWDisplay_SetForegroundColor(WWDisplay d, int c)
{ return (d->foreground_color = c); }
int WWDisplay_SetBackgroundColor(WWDisplay d, int c)
{ return (d->background_color = c); }

int WWDisplay_SetSpriteStart(WWDisplay d, int n)
{ return (d->sprite_start = n); }
int WWDisplay_SetSpriteCount(WWDisplay d, int n)
{ return (d->sprite_count = n); }

/*===========================================================================*/
/* オブジェクトの生成と消去                                                  */
/*===========================================================================*/

WWDisplay WWDisplay_Create(int lcd_panel_width, int lcd_panel_height,
			   int screen_width, int screen_height)
{
  WWDisplay display;
  int i;

  display = (WWDisplay)malloc(sizeof(_WWDisplay));
  if (display == NULL) Error("WWDisplay_Create", "Cannot allocate memory.");

  WWDisplay_SetColorMap(display, WWColorMap_Create(NULL));

  for (i = 0; i < 16; i++) {
    WWDisplay_SetPalette(display, i,
			 WWPalette_Create(i, NULL, ((i / 4) % 2) ? 1 : 0));
  }

  for (i = 0; i < 512; i++) {
    WWDisplay_SetCharacter(display, i, WWCharacter_Create(i, NULL));
  }

  for (i = 0; i < 128; i++) {
    WWDisplay_SetSprite(display, i,
			WWSprite_Create(i, 0, 0, 0, 0, 0, 0,
					WWDisplay_GetPalette(display, 0),
					WWDisplay_GetCharacter(display, 0)));
  }

  for (i = 0; i < 2; i++) {
    WWDisplay_SetScreen(display, i,
			WWScreen_Create(i, screen_width, screen_height,
					WWDisplay_GetPalette(display, 0),
					WWDisplay_GetCharacter(display, 0),
					0, 0,
					lcd_panel_width, lcd_panel_height));
  }

  WWDisplay_SetLCDPanel(display, WWLCDPanel_Create(lcd_panel_width,
						   lcd_panel_height));

  WWDisplay_SetSpriteEnable(display, 0);
  WWDisplay_SetSpriteWindowEnable(display, 0);

  WWDisplay_SetSpriteWindowX(     display, 0);
  WWDisplay_SetSpriteWindowY(     display, 0);
  WWDisplay_SetSpriteWindowWidth( display, lcd_panel_width);
  WWDisplay_SetSpriteWindowHeight(display, lcd_panel_height);

  WWDisplay_SetBorder(display, 0);

  WWDisplay_SetForegroundColor(display, 3);
  WWDisplay_SetBackgroundColor(display, 0);

  WWDisplay_SetSpriteStart(display, 0);
  WWDisplay_SetSpriteCount(display, 0);

  return (display);
}

WWDisplay WWDisplay_Destroy(WWDisplay display)
{
  int i;

  if (display == NULL) return (NULL);

  if (WWDisplay_GetColorMap(display) != NULL)
    WWDisplay_SetColorMap(display,
			  WWColorMap_Destroy(WWDisplay_GetColorMap(display)));

  for (i = 0; i < 16; i++) {
    if (WWDisplay_GetPalette(display, i) != NULL)
      WWDisplay_SetPalette(display, i,
			   WWPalette_Destroy(WWDisplay_GetPalette(display, i))
			   );
  }

  for (i = 0; i < 512; i++) {
    if (WWDisplay_GetCharacter(display, i) != NULL)
      WWDisplay_SetCharacter(display, i,
			     WWCharacter_Destroy(WWDisplay_GetCharacter(display
									, i)));
  }

  for (i = 0; i < 128; i++) {
    if (WWDisplay_GetSprite(display, i) != NULL)
      WWDisplay_SetSprite(display, i,
			  WWSprite_Destroy(WWDisplay_GetSprite(display, i)));
  }

  for (i = 0; i < 2; i++) {
    if (WWDisplay_GetScreen(display, i) != NULL)
      WWDisplay_SetScreen(display, i,
			  WWScreen_Destroy(WWDisplay_GetScreen(display, i)));
  }

  if (WWDisplay_GetLCDPanel(display) != NULL)
    WWDisplay_SetLCDPanel(display,
			  WWLCDPanel_Destroy(WWDisplay_GetLCDPanel(display)));

  free(display);

  return (NULL);
}

/*===========================================================================*/
/* LCDパネルの描画                                                           */
/*===========================================================================*/

static int WWDisplay_DrawScreen(WWDisplay display, WWScreen screen)
{
  WWLCDPanel lcd_panel;
  int lcd_panel_width;
  int lcd_panel_height;

  int pixel;
  int x, y, px, py;
  int sx, sy, ex, ey;
  int mode;

  if (!WWScreen_GetEnable(screen)) return (0);

  lcd_panel = WWDisplay_GetLCDPanel(display);
  lcd_panel_width  = WWLCDPanel_GetWidth( lcd_panel);
  lcd_panel_height = WWLCDPanel_GetHeight(lcd_panel);

  if ( (WWScreen_GetMode(screen) == WWSCREEN_INSIDE_ONLY) ||
       (WWScreen_GetMode(screen) == WWSCREEN_OUTSIDE_ONLY) ) {
    sx = WWScreen_GetDrawX(screen);
    sy = WWScreen_GetDrawX(screen);

    /*
     * マニュアルの screen2_set_window() の説明には「表示領域の横幅と縦幅」と
     * 書いてあるが，実際には「表示領域の横幅+1と縦幅+1」で動作する
     * みたい？(未確認)なので，-1 しなくてよい？
     * もしくは，WonderWitch での実際の動作は，
     * ex = sx + WWScreen_GetDrawWidth( screen);
     * でなく
     * ex = WWScreen_GetDrawWidth( screen);
     * なのかもしれない．
     */

#if 0
    ex = sx + WWScreen_GetDrawWidth( screen) - 1;
    ey = sy + WWScreen_GetDrawHeight(screen) - 1;
#else
    ex = sx + WWScreen_GetDrawWidth( screen);
    ey = sy + WWScreen_GetDrawHeight(screen);
#endif
  }

  mode = WWScreen_GetMode(screen);

  /* 以下はホットスポットになるので，そのうちループアンローリング */
  /* したほうがいいかも                                           */

  for (y = 0; y < lcd_panel_height; y++) {
    for (x = 0; x < lcd_panel_width; x++) {
      px = x + WWScreen_GetRollX(screen);
      py = y + WWScreen_GetRollY(screen);

      if (mode == WWSCREEN_INSIDE_ONLY) {
	if (y > ey) {
	  x = lcd_panel_width - 1; y = lcd_panel_height - 1; continue;
	}
	if (y < sy) { x = lcd_panel_width - 1; y = sy - 1; continue; }
	if (x > ex) { x = lcd_panel_width - 1; continue; }
	if (x < sx) { x = sx - 1; continue; }
      } else if (mode == WWSCREEN_OUTSIDE_ONLY) {
	if ( (x >= sx) && (x <= ex) && (y >= sy) && (y <= ey) ) {
	  x = ex;
	  continue;
	}
      }

      pixel = WWScreen_GetPixel(screen, px, py);

      /* 透明色の場合 */
      if (pixel == -1) continue;

      pixel = WWColorMap_GetLCDColor(WWDisplay_GetColorMap(display), pixel);
      WWLCDPanel_SetPixel(lcd_panel, x, y, pixel);
    }
  }

  return (0);
}

static int WWDisplay_DrawSprite(WWDisplay display, WWSprite sprite)
{
  int x, y, lcd_x, lcd_y;
  int sx, sy, ex, ey;
  int pixel, outside;

  sx = WWDisplay_GetSpriteWindowX(display) - 1;
  sy = WWDisplay_GetSpriteWindowY(display) - 1;

  /* 以下は WWDisplay_DrawScreen() に合わせた */
#if 0
  ex = sx + WWDisplay_GetSpriteWindowWidth(display) - 1;
  ey = sy + WWDisplay_GetSpriteWindowHeight(display) - 1;
#else
  ex = sx + WWDisplay_GetSpriteWindowWidth(display);
  ey = sy + WWDisplay_GetSpriteWindowHeight(display);
#endif

  for (y = 0; y < 8; y++) {
    for (x = 0; x < 8; x++) {
      pixel = WWSprite_GetPixel(sprite, x, y);

      /* 透明色の場合 */
      if (pixel == -1) continue;

      lcd_x = WWSprite_GetX(sprite) + x;
      lcd_y = WWSprite_GetY(sprite) + y;

      if (WWDisplay_GetSpriteWindowEnable(display)) {
	if ( (lcd_x < sx) || (lcd_y < sy) || (lcd_x > ex) || (lcd_y > ey) )
	  outside = 1;
	else
	  outside = 0;

	if (WWSprite_GetClipping(sprite)) { /* ウインドウの外側部分を表示 */
	  if (!outside) continue;
	} else {                            /* ウインドウの内側部分を表示 */
	  if (outside) continue;
	}
      }

      pixel = WWColorMap_GetLCDColor(WWDisplay_GetColorMap(display), pixel);
      WWLCDPanel_SetPixel(WWDisplay_GetLCDPanel(display), lcd_x, lcd_y, pixel);
    }
  }

  return (0);
}

int WWDisplay_DrawLCDPanel(WWDisplay display)
{
  WWLCDPanel lcd_panel;
  WWScreen screen;
  int x, y, i;
  int lcd_panel_width;
  int lcd_panel_height;
  WWColorMap color_map;
  int border;
  WWSprite sprite;

  lcd_panel = WWDisplay_GetLCDPanel(display);
  lcd_panel_width = WWLCDPanel_GetWidth(lcd_panel);
  lcd_panel_height = WWLCDPanel_GetHeight(lcd_panel);
  color_map = WWDisplay_GetColorMap(display);
  border = WWDisplay_GetBorder(display);

  /* ボーダーカラーで埋める */
  for (x = 0; x < lcd_panel_width; x++) {
    for (y = 0; y < lcd_panel_height; y++) {
      WWLCDPanel_SetPixel(lcd_panel, x, y,
			  WWColorMap_GetLCDColor(color_map, border));
    }
  }

  /* スクリーン１描画 */
  WWDisplay_DrawScreen(display, WWDisplay_GetScreen(display, 0));

  /* スプライト描画(スクリーン２より優先でないもの) */
  /* 重なった場合は，番号の若いものが手前に表示される */
  if (WWDisplay_GetSpriteEnable(display)) {
    for (i = WWDisplay_GetSpriteCount(display) - 1; i >= 0; i--) {
      sprite = WWDisplay_GetSprite(display,
				   i + WWDisplay_GetSpriteStart(display));
      if (!WWSprite_GetPriority(sprite)) {
	WWDisplay_DrawSprite(display, sprite);
      }
    }
  }

  /* スクリーン２描画 */
  WWDisplay_DrawScreen(display, WWDisplay_GetScreen(display, 1));

  /* スプライト描画(スクリーン２より優先なもの) */
  /* 重なった場合は，番号の若いものが手前に表示される */
  if (WWDisplay_GetSpriteEnable(display)) {
    for (i = WWDisplay_GetSpriteCount(display) - 1; i >= 0; i--) {
      sprite = WWDisplay_GetSprite(display,
				   i + WWDisplay_GetSpriteStart(display));
      if (WWSprite_GetPriority(sprite)) {
	WWDisplay_DrawSprite(display, sprite);
      }
    }
  }

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
