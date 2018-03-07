/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "wonx_include/disp.h"
#include "wonx_include/text.h"
#include "wonx_include/libwwc.h"

#include "WWDisplayP.h"
#include "WonX.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* ���Фμ���                                                              */
/*===========================================================================*/

WWColorMap WWDisplay_GetColorMap(WWDisplay d) { return (d->color_map); }
WWPalette WWDisplay_GetPalette(WWDisplay d, int n) { return (d->palette[n]); }
WWCharacter WWDisplay_GetCharacter(WWDisplay d, int n)
{ return (d->character[n]); }
WWSprite WWDisplay_GetSprite(WWDisplay d, int n) { return (d->sprite[n]); }
WWScreen WWDisplay_GetScreen(WWDisplay d, int n) { return (d->screen[n]); }
WWLCDPanel WWDisplay_GetLCDPanel(WWDisplay d) { return (d->lcd_panel); }
WWText WWDisplay_GetText(WWDisplay d) { return (d->text); }
WWCursor WWDisplay_GetCursor(WWDisplay d) { return (d->cursor); }

unsigned int WWDisplay_GetColorMode(WWDisplay d) { return (d->color_mode); }

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

WWPalette WWDisplay_GetBorderPalette(WWDisplay d)
{ return (d->border_palette); }
int WWDisplay_GetBorderColor(WWDisplay d)
{ return (d->border_color); }

int WWDisplay_GetForegroundColor(WWDisplay d) { return (d->foreground_color); }
int WWDisplay_GetBackgroundColor(WWDisplay d) { return (d->background_color); }

int WWDisplay_GetSpriteStart(WWDisplay d) { return (d->sprite_start); }
int WWDisplay_GetSpriteCount(WWDisplay d) { return (d->sprite_count); }

/*===========================================================================*/
/* ���Ф�����                                                              */
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
WWText WWDisplay_SetText(WWDisplay d, WWText p)
{ return (d->text = p); }
WWCursor WWDisplay_SetCursor(WWDisplay d, WWCursor p)
{ return (d->cursor = p); }

unsigned int WWDisplay_SetColorMode(WWDisplay d, unsigned int mode)
{ return (d->color_mode = mode); }

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

WWPalette WWDisplay_SetBorderPalette(WWDisplay d, WWPalette p)
{ return (d->border_palette = p); }
int WWDisplay_SetBorderColor(WWDisplay d, int b)
{ return (d->border_color = b); }

int WWDisplay_SetForegroundColor(WWDisplay d, int c)
{ return (d->foreground_color = c); }
int WWDisplay_SetBackgroundColor(WWDisplay d, int c)
{ return (d->background_color = c); }

int WWDisplay_SetSpriteStart(WWDisplay d, int n)
{ return (d->sprite_start = n); }
int WWDisplay_SetSpriteCount(WWDisplay d, int n)
{ return (d->sprite_count = n); }

/*===========================================================================*/
/* ���֥������Ȥ������Ⱦõ�                                                  */
/*===========================================================================*/

WWDisplay WWDisplay_Create(int lcd_panel_width, int lcd_panel_height,
			   int screen_width, int screen_height)
{
  WWDisplay display;
  int i;
  static int default_lcd_colors[] = {
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0f
  };
  static struct palette_colors {
    int colors[4];
  } default_palette_colors[] = {
    {{0, 3, 5, 7}}, {{2, 3, 5, 7}}, {{0, 0, 0, 7}}, {{2, 0, 0, 7}},
    {{0, 0, 3, 7}}, {{0, 7, 7, 7}}, {{0, 7, 7, 7}}, {{0, 0, 2, 7}},
    {{2, 5, 7, 7}}, {{7, 7, 7, 7}}, {{7, 6, 5, 7}}, {{3, 7, 5, 7}},
    {{0, 0, 4, 7}}, {{0, 0, 0, 7}}, {{0, 7, 7, 5}}, {{0, 7, 3, 7}}
  };

  display = (WWDisplay)malloc(sizeof(_WWDisplay));
  if (display == NULL)
    WonX_Error("WWDisplay_Create", "Cannot allocate memory.");

  WWDisplay_SetColorMap(display, WWColorMap_Create(default_lcd_colors));

  for (i = 0; i < 16; i++) {
    /*
     * WonX-2.0 �ʹߤǤϡ�Ʃ������ WWPalette ���饹�Ǥϴ������ʤ��褦��
     * �ѹ������Τǡ�Ʃ�����������ɬ��̵���ʤä���
     */
#if 1
    WWDisplay_SetPalette(display, i,
			 WWPalette_Create(i,default_palette_colors[i].colors));
#else /* WonX-2.0 �����Ǥϡ�Ʃ���������꤬ɬ�פ��ä�����������ɤ�Ĥ��Ƥ��� */
    WWDisplay_SetPalette(display, i,
			 WWPalette_Create(i,
					  default_palette_colors[i].colors,
					  ((i / 4) % 2) ? 1 : 0));
#endif
  }

  for (i = 0; i < 512; i++) {
    WWDisplay_SetCharacter(display, i, WWCharacter_Create(i));
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

  /* �ǥե���ȤΥƥ�����ɽ���ѥѥ�åȤ�0 */
  WWDisplay_SetText(display,
		    WWText_Create(WWDisplay_GetScreen(display, SCREEN2),
				  0, 0,
				  TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT,
				  WWDisplay_GetPalette(display, 0)));

  /*
   * WWDisplay_GetPalette() ��ƤӽФ��Τǡ��ѥ�åȤ����ꤷ�Ƥ���
   * ��������������Ԥ����ȡ�
   * �ǥե���ȤΥ�������ѥ�åȤϣ�
   */
  WWDisplay_SetCursor(display,
		      WWCursor_Create(WWDisplay_GetPalette(display, 1)));

  /* �ǥե���ȤΥ��顼�⡼�ɤ�����⡼�� */
  WWDisplay_SetColorMode(display, COLOR_MODE_GRAYSCALE);

  WWDisplay_SetSpriteEnable(display, 0);
  WWDisplay_SetSpriteWindowEnable(display, 0);

  WWDisplay_SetSpriteWindowX(     display, 0);
  WWDisplay_SetSpriteWindowY(     display, 0);
  WWDisplay_SetSpriteWindowWidth( display, lcd_panel_width);
  WWDisplay_SetSpriteWindowHeight(display, lcd_panel_height);

  WWDisplay_SetBorderPalette(display, WWDisplay_GetPalette(display, 0));
  WWDisplay_SetBorderColor(display, 0);

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

  if (WWDisplay_GetText(display) != NULL)
    WWDisplay_SetText(display,
		      WWText_Destroy(WWDisplay_GetText(display)));

  if (WWDisplay_GetCursor(display) != NULL)
    WWDisplay_SetCursor(display,
			WWCursor_Destroy(WWDisplay_GetCursor(display)));

  free(display);

  return (NULL);
}

/*===========================================================================*/
/* LCD�ѥͥ������                                                           */
/*===========================================================================*/

static int WWDisplay_DrawScreen(WWDisplay display, WWScreen screen,
				WWCursor cursor)
{
  WWLCDPanel lcd_panel;
  int lcd_panel_width;
  int lcd_panel_height;

  int pixel;
  int x, y, px, py;
  int sx = 0, sy = 0, ex = 0, ey = 0;
  int mode;

  if (!WWScreen_GetEnable(screen)) return (0);

  lcd_panel = WWDisplay_GetLCDPanel(display);
  lcd_panel_width  = WWLCDPanel_GetWidth( lcd_panel);
  lcd_panel_height = WWLCDPanel_GetHeight(lcd_panel);

  if ( (WWScreen_GetMode(screen) == WW_SCREEN_INSIDE_ONLY) ||
       (WWScreen_GetMode(screen) == WW_SCREEN_OUTSIDE_ONLY) ) {
    sx = WWScreen_GetDrawX(screen);
    sy = WWScreen_GetDrawX(screen);

    /*
     * �ޥ˥奢��� screen2_set_window() �������ˤϡ�ɽ���ΰ�β����Ƚ����פ�
     * �񤤤Ƥ��뤬���ºݤˤϡ�ɽ���ΰ�β���+1�Ƚ���+1�פ�ư���
     * �ߤ�����(̤��ǧ)�ʤΤǡ�-1 ���ʤ��Ƥ褤��
     * �⤷���ϡ�WonderWitch �Ǥμºݤ�ư��ϡ�
     * ex = sx + WWScreen_GetDrawWidth( screen);
     * �Ǥʤ�
     * ex = WWScreen_GetDrawWidth( screen);
     * �ʤΤ��⤷��ʤ���
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

  /* �ʲ��ϥۥåȥ��ݥåȤˤʤ�Τǡ����Τ����롼�ץ������� */
  /* �����ۤ�����������                                           */

  for (y = 0; y < lcd_panel_height; y++) {

    if (mode == WW_SCREEN_INSIDE_ONLY) {
      if (y > ey) { break; }
      if (y < sy) { y = sy - 1; continue; }
    }

    py = y + WWScreen_GetRollY(screen);

    for (x = 0; x < lcd_panel_width; x++) {

      if (mode == WW_SCREEN_INSIDE_ONLY) {
	if (x > ex) { x = lcd_panel_width - 1; continue; }
	if (x < sx) { x = sx - 1; continue; }
      } else if (mode == WW_SCREEN_OUTSIDE_ONLY) {
	if ( (x >= sx) && (x <= ex) && (y >= sy) && (y <= ey) ) {
	  x = ex;
	  continue;
	}
      }

      px = x + WWScreen_GetRollX(screen);

      /* Ʃ�����ξ��ˤϡ�-1���֤äƤ��� */
      pixel = WWScreen_GetPixel(screen, px, py, display, cursor);

      /* Ʃ�����ξ�� */
      if (pixel == -1) continue;

      /* ���顼�б� */
      switch (WWDisplay_GetColorMode(display)) {
      case COLOR_MODE_GRAYSCALE:
	pixel = WWColorMap_GetLCDColor(WWDisplay_GetColorMap(display), pixel);
	break;
      case COLOR_MODE_4COLOR:
      case COLOR_MODE_16COLOR:
      case COLOR_MODE_16PACKED:
	break;
      default:
	WonX_Error("WWDisplay_DrawSprite", "Unknown color mode.");
      }

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

  /* �ʲ��� WWDisplay_DrawScreen() �˹�碌�� */
#if 0
  ex = sx + WWDisplay_GetSpriteWindowWidth(display) - 1;
  ey = sy + WWDisplay_GetSpriteWindowHeight(display) - 1;
#else
  ex = sx + WWDisplay_GetSpriteWindowWidth(display);
  ey = sy + WWDisplay_GetSpriteWindowHeight(display);
#endif

  for (y = 0; y < 8; y++) {
    for (x = 0; x < 8; x++) {

      /* Ʃ������-1���֤äƤ��� */
      pixel = WWSprite_GetPixel(sprite, x, y, display);

      /* Ʃ�����ξ�� */
      if (pixel == -1) continue;

      lcd_x = WWSprite_GetX(sprite) + x;
      lcd_y = WWSprite_GetY(sprite) + y;

      if (WWDisplay_GetSpriteWindowEnable(display)) {
	if ( (lcd_x < sx) || (lcd_y < sy) || (lcd_x > ex) || (lcd_y > ey) )
	  outside = 1;
	else
	  outside = 0;

	if (WWSprite_GetClipping(sprite)) { /* ������ɥ��γ�¦��ʬ��ɽ�� */
	  if (!outside) continue;
	} else {                            /* ������ɥ�����¦��ʬ��ɽ�� */
	  if (outside) continue;
	}
      }

      /* ���顼�б� */
      switch (WWDisplay_GetColorMode(display)) {
      case COLOR_MODE_GRAYSCALE:
	pixel = WWColorMap_GetLCDColor(WWDisplay_GetColorMap(display), pixel);
	break;
      case COLOR_MODE_4COLOR:
      case COLOR_MODE_16COLOR:
      case COLOR_MODE_16PACKED:
	break;
      default:
	WonX_Error("WWDisplay_DrawSprite", "Unknown color mode.");
      }

      WWLCDPanel_SetPixel(WWDisplay_GetLCDPanel(display), lcd_x, lcd_y, pixel);
    }
  }

  return (0);
}

int WWDisplay_DrawLCDPanel(WWDisplay display)
{
  WWLCDPanel lcd_panel;
  int x, y, i;
  int lcd_panel_width;
  int lcd_panel_height;
  WWColorMap color_map;
  WWPalette border_palette;
  int border_color;
  WWScreen screen;
  WWSprite sprite;
  WWCursor cursor;

  lcd_panel = WWDisplay_GetLCDPanel(display);
  lcd_panel_width  = WWLCDPanel_GetWidth( lcd_panel);
  lcd_panel_height = WWLCDPanel_GetHeight(lcd_panel);
  color_map = WWDisplay_GetColorMap(display);
  border_palette = WWDisplay_GetBorderPalette(display);
  border_color = WWDisplay_GetBorderColor(display);

  /* ���顼�б� */
  switch (WWDisplay_GetColorMode(display)) {
  case COLOR_MODE_GRAYSCALE:
    border_color &= (DCM_BORDER_COLOR >> 8);
    border_color = WWColorMap_GetLCDColor(color_map, border_color);
    break;
  case COLOR_MODE_4COLOR:
    border_color &= 0x03;
    border_color =
      ((unsigned short int)WWPalette_GetRed(  border_palette,border_color)<<8)|
      ((unsigned short int)WWPalette_GetGreen(border_palette,border_color)<<4)|
      ((unsigned short int)WWPalette_GetBlue( border_palette,border_color)<<0);
    break;
  case COLOR_MODE_16COLOR:
  case COLOR_MODE_16PACKED:
    border_color &= 0x0f;
    border_color =
      ((unsigned short int)WWPalette_GetRed(  border_palette,border_color)<<8)|
      ((unsigned short int)WWPalette_GetGreen(border_palette,border_color)<<4)|
      ((unsigned short int)WWPalette_GetBlue( border_palette,border_color)<<0);
    break;
  default:
    WonX_Error("WWDisplay_DrawLCDPanel", "Unknown color mode.");
  }

  /* �ܡ��������顼������ */
  for (x = 0; x < lcd_panel_width; x++) {
    for (y = 0; y < lcd_panel_height; y++) {
      WWLCDPanel_SetPixel(lcd_panel, x, y, border_color);
    }
  }

  /* �����꡼������ */
  screen = WWDisplay_GetScreen(display, 0);
  if (WWText_GetScreen(WWDisplay_GetText(display)) == screen)
    cursor = WWDisplay_GetCursor(display);
  else
    cursor = NULL;
  WWDisplay_DrawScreen(display, screen, cursor);

  /* ���ץ饤������(�����꡼�󣲤��ͥ��Ǥʤ����) */
  /* �Ťʤä����ϡ��ֹ�μ㤤��Τ�������ɽ������� */
  if (WWDisplay_GetSpriteEnable(display)) {
    for (i = WWDisplay_GetSpriteCount(display) - 1; i >= 0; i--) {
      sprite = WWDisplay_GetSprite(display,
				   i + WWDisplay_GetSpriteStart(display));
      if (!WWSprite_GetPriority(sprite)) {
	WWDisplay_DrawSprite(display, sprite);
      }
    }
  }

  /* �����꡼������ */
  screen = WWDisplay_GetScreen(display, 1);
  if (WWText_GetScreen(WWDisplay_GetText(display)) == screen)
    cursor = WWDisplay_GetCursor(display);
  else
    cursor = NULL;
  WWDisplay_DrawScreen(display, screen, cursor);

  /* ���ץ饤������(�����꡼�󣲤��ͥ��ʤ��) */
  /* �Ťʤä����ϡ��ֹ�μ㤤��Τ�������ɽ������� */
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

/*===========================================================================*/
/* Ʃ�������ɤ���Ĵ�٤�                                                      */
/*===========================================================================*/

int WWDisplay_IsTransparent(WWDisplay display, WWPalette palette, int color)
{
  int mode;
  int palette_num;
  int ret;

  if (color != 0) return (0);

  mode = WWDisplay_GetColorMode(display);
  palette_num = WWPalette_GetNumber(palette);

  ret = 0;
  switch (mode) {
  case COLOR_MODE_GRAYSCALE :
  case COLOR_MODE_4COLOR :
    ret = ((palette_num / 4) % 2) ? 1 : 0;
    break;
  case COLOR_MODE_16COLOR :
  case COLOR_MODE_16PACKED :
    ret = 1;
    break;
  default :
    WonX_Error("WWDisplay_IsTransparent", "Unknown color mode.");
  }

  return (ret);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
