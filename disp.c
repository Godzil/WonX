/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/disp.h>

#include "wonx.h"

#include "WonxDisplay.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

void display_control(unsigned int flags)
{
  printf("display_control(): flags = %ud, ", flags); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  WWDisplay_SetScreenEnable(WonxDisplay_GetWWDisplay(wonx_display),
			    SCREEN1,
			    (flags & DCM_SCR1) ? 1 : 0);

  WWDisplay_SetScreenEnable(WonxDisplay_GetWWDisplay(wonx_display),
			    SCREEN2,
			    (flags & DCM_SCR2) ? 1 : 0);

  WWDisplay_SetSpriteEnable(WonxDisplay_GetWWDisplay(wonx_display),
			    (flags & DCM_SPR) ? 1 : 0);

  WWDisplay_SetSpriteWindowEnable(WonxDisplay_GetWWDisplay(wonx_display),
				  (flags & DCM_SPR_WIN) ? 1 : 0);

  if      ((flags & 0x0030) == DCM_SCR2_WIN_INSIDE)
    WWDisplay_SetScreen2WindowMode(WonxDisplay_GetWWDisplay(wonx_display), 2);
  else if ((flags & 0x0030) == DCM_SCR2_WIN_OUTSIDE)
    WWDisplay_SetScreen2WindowMode(WonxDisplay_GetWWDisplay(wonx_display), 3);

  WWDisplay_SetBorder(WonxDisplay_GetWWDisplay(wonx_display),
		      (flags & DCM_BORDER_COLOR) >> 7);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int display_status()
{
  unsigned short int ret;

  printf("display_status(): "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  ret = 0;

  if (WWDisplay_GetScreenEnable(WonxDisplay_GetWWDisplay(wonx_display),
				SCREEN1))
    ret |= DCM_SCR1;

  if (WWDisplay_GetScreenEnable(WonxDisplay_GetWWDisplay(wonx_display),
				SCREEN2))
    ret |= DCM_SCR2;

  if (WWDisplay_GetSpriteEnable(WonxDisplay_GetWWDisplay(wonx_display)))
    ret |= DCM_SPR;

  if (WWDisplay_GetSpriteWindowEnable(WonxDisplay_GetWWDisplay(wonx_display)))
    ret |= DCM_SPR_WIN;

  switch
    (WWDisplay_GetScreen2WindowMode(WonxDisplay_GetWWDisplay(wonx_display))) {
    case 2:
      ret |= DCM_SCR2_WIN_INSIDE;
      break;
    case 3:
      ret |= DCM_SCR2_WIN_OUTSIDE;
      break;
    default:
  }

  ret |= WWDisplay_GetBorder(WonxDisplay_GetWWDisplay(wonx_display)) << 7;

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ul\n", (unsigned int)ret); fflush(stdout);

  return (ret);
}

void font_set_monodata(unsigned int number,
		       unsigned int count, void * data)
{
  WWCharacter c;
  int i, x, y, n, p;
  int f, b;
  unsigned char * d;

  printf("font_set_monodata(): number = %ud, count = %ud, data = %p, ",
	 number, count, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  n = 0;
  d = (unsigned char *)data; /* ひとつのキャラクタデータは８バイト */
  f = WWDisplay_GetForegroundColor(WonxDisplay_GetWWDisplay(wonx_display));
  b = WWDisplay_GetBackgroundColor(WonxDisplay_GetWWDisplay(wonx_display));

  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display),
			       number + i);
    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {
	p = (d[n] & (1 << (7 - x))) ? f : b; /*これでよいのか？*/
	WWCharacter_SetPixel(c, x, y, p);
      }
      n++;
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void font_set_colordata(unsigned int number,
			unsigned int count, void * data)
{
  WWCharacter c;
  int i, x, y, n, p;
  int f, b;
  unsigned char * d;

  printf("font_set_colordata(): number = %ud, count = %ud, data = %p, ",
	 number, count, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  n = 0;
  d = (unsigned char *)data; /* ひとつのキャラクタデータは16バイト */

  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display),
			       number + i);
    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {

	/*これでよいのか？*/
	p = ((d[n] & (1 << (7-x))) ? 2 : 0) + ((d[n + 1] & (1 << (7-x))) ? 1 : 0);

	WWCharacter_SetPixel(c, x, y, p);
      }
      n++;
      n++;
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void font_get_data(unsigned int number,
		   unsigned int count, void * data)
{
  /* 関数の仕様がわからんので適当に書くぞ */
  WWCharacter c;
  int i, x, y, n, p;
  int f, b;
  unsigned char * d;

  printf("font_get_data(): number = %ud, count = %ud, data = %p, ",
	 number, count, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  n = 0;
  d = (unsigned char *)data; /* ひとつのキャラクタデータは16バイト？ */

  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display),
			       number + i);
    for (y = 0; y < 8; y++) {
      d[n  ] = 0;
      d[n+1] = 0;
      for (x = 0; x < 8; x++) {
	p = WWCharacter_GetPixel(c, x, y);
	/* これでよいのか？ */
	d[n  ] |= (((unsigned char)p & 0x02) ? 1 : 0) << (7-x);
	d[n+1] |= (((unsigned char)p & 0x01) ? 1 : 0) << (7-x);
      }
      n++;
      n++;
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void font_set_color(unsigned int colors)
{
  WWDisplay dis;

  printf("font_set_color(): colors = %ud, ", colors); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  dis = WonxDisplay_GetWWDisplay(wonx_display);
  WWDisplay_SetForegroundColor(dis, colors & 0x03);
  WWDisplay_SetBackgroundColor(dis, (colors >> 2) & 0x03);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int font_get_color(void)
{
  unsigned short int ret;
  WWDisplay dis;

  printf("font_get_color(): "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  dis = WonxDisplay_GetWWDisplay(wonx_display);
  ret = 0;
  ret |= WWDisplay_GetForegroundColor(dis);
  ret |= WWDisplay_GetBackgroundColor(dis) << 2;

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void screen_set_char(int screen, int x, int y, int w, int h, void * data)
{
  int i, j;
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  int palette_num; /* パレット番号 */
  int character_num; /* 表示キャラクタ */
  unsigned short int * d;
  WWScreen s;
  WWPalette p;
  WWCharacter c;

  printf("font_set_char(): screen = %d, x = %d, y = %d, w = %d, h = %d, data = %p",
	 screen, x, y, w, h, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  d = (unsigned short int *)data;
  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx_display), screen);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      horizontal    = (*d & (1 << 15)) ? 1 : 0;
      vertical      = (*d & (1 << 14)) ? 1 : 0;
      palette_num   = (*d >> 9) & 0x0f;
      character_num = *d & 0x1ff;
      p = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx_display),
			       palette_num);
      c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display),
				 character_num);
      WWScreen_SetHorizontal(s, x + i, y + j, horizontal);
      WWScreen_SetVertical(  s, x + i, y + j, vertical);
      WWScreen_SetPalette(   s, x + i, y + j, p);
      WWScreen_SetCharacter( s, x + i, y + j, c);

      d++;
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void screen_get_char(int screen, int x, int y, int w, int h, void * data)
{
  int i, j;
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  int palette_num; /* パレット番号 */
  int character_num; /* 表示キャラクタ */
  unsigned short int * d;
  WWScreen s;
  WWPalette p;
  WWCharacter c;

  printf("font_get_char(): screen = %d, x = %d, y = %d, w = %d, h = %d, data = %p",
	 screen, x, y, w, h, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  d = (unsigned short int *)data;
  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx_display), screen);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      horizontal = WWScreen_GetHorizontal(s, x + i, y + j);
      vertical   = WWScreen_GetVertical(  s, x + i, y + j);
      p          = WWScreen_GetPalette(   s, x + i, y + j);
      c          = WWScreen_GetCharacter( s, x + i, y + j);
      palette_num = WWPalette_GetNumber(p);
      character_num = WWCharacter_GetNumber(c);

      *d = 0;
      *d |= horizontal << 15;
      *d |= vertical << 14;
      *d |= palette_num << 9;
      *d |= character_num;
      d++;
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int screen_get_char1(int screen, int x, int y)
{
  unsigned short int ret;

  printf("screen_get_char1(): screen = %d, x = %d, y = %d, ",
	 screen, x, y); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  screen_get_char(screen, x, y, 1, 1, &ret);

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void screen_fill_char(int screen, int x, int y, int w, int h,
		      unsigned int data)
{
  int i, j;
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  int palette_num; /* パレット番号 */
  int character_num; /* 表示キャラクタ */
  WWScreen s;
  WWPalette p;
  WWCharacter c;

  printf("screen_fill_char(): screen = %d, x = %d, y = %d, w = %d, h = %d, data = %ud",
	 screen, x, y, w, h, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx_display), screen);

  horizontal    = (data & (1 << 15)) ? 1 : 0;
  vertical      = (data & (1 << 14)) ? 1 : 0;
  palette_num   = (data >> 9) & 0x0f;
  character_num = data & 0x1ff;

  p = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx_display),
			   palette_num);
  c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display),
			     character_num);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      WWScreen_SetHorizontal(s, x + i, y + j, horizontal);
      WWScreen_SetVertical(  s, x + i, y + j, vertical);
      WWScreen_SetPalette(   s, x + i, y + j, p);
      WWScreen_SetCharacter( s, x + i, y + j, c);
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void screen_fill_attr(int screen, int x, int y, int w, int h,
		      unsigned int data, unsigned int mask)
{
  int i, j;
  unsigned short int c;

  printf("screen_fill_attr(): screen = %d, x = %d, y = %d, w = %d, h = %d, data = %ud, mask = %ud, ",
	 screen, x, y, w, h, data, mask); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      c = screen_get_char1(screen, x + i, y + j);
      c &= mask;
      c |= data;
      screen_fill_char(screen, x + i, y + j, 1, 1, c);
    }
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void sprite_set_range(unsigned int sprite_start, unsigned int sprite_count)
{
  printf("sprite_set_range(): start = %ud, count = %ud, ",
	 sprite_start, sprite_count); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  WWDisplay_SetSpriteStart(WonxDisplay_GetWWDisplay(wonx_display),
			   sprite_start);
  WWDisplay_SetSpriteCount(WonxDisplay_GetWWDisplay(wonx_display),
			   sprite_count);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void sprite_set_char(unsigned int sprite_num,
		     unsigned int data)
{
  WWSprite s;
  WWPalette p;
  WWCharacter c;

  printf("sprite_set_char(): number = %ud, data = %ud, ",
	 sprite_num, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(wonx_display), sprite_num);

  WWSprite_SetHorizontal(s, (data >> 15) ? 1 : 0);
  WWSprite_SetVertical(  s, (data >> 14) ? 1 : 0);
  WWSprite_SetPriority(  s, (data >> 13) ? 1 : 0);
  WWSprite_SetClipping(  s, (data >> 12) ? 1 : 0);

  p = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx_display),
			   (data >> 9) & 0x07);
  c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(wonx_display), data & 0x1ff);

  WWSprite_SetPalette(s, p);
  WWSprite_SetCharacter(s, c);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int sprite_get_char(unsigned int sprite_num)
{
  WWSprite s;
  WWPalette p;
  WWCharacter c;
  unsigned short int ret;

  printf("sprite_get_char(): number = %ud, ", sprite_num); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(wonx_display), sprite_num);

  ret = 0;

  ret |= (WWSprite_GetHorizontal(s) ? 1 : 0) << 15;
  ret |= (WWSprite_GetVertical(  s) ? 1 : 0) << 14;
  ret |= (WWSprite_GetPriority(  s) ? 1 : 0) << 13;
  ret |= (WWSprite_GetClipping(  s) ? 1 : 0) << 12;

  p = WWSprite_GetPalette(s);

  ret |= (WWPalette_GetNumber(p) & 0x07) << 9;

  c = WWSprite_GetCharacter(s);
  ret |= WWCharacter_GetNumber(c);

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void sprite_set_location(unsigned int sprite_num, int x, int y)
{
  WWSprite s;

  printf("sprite_set_location(): number = %ud, x = %d, y = %d, ",
	 sprite_num, x, y); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(wonx_display), sprite_num);
  WWSprite_SetPosition(s, x, y);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int sprite_get_location(unsigned int sprite_num)
{
  WWSprite s;
  unsigned short int ret;

  printf("sprite_get_location(): number = %ud, ", sprite_num); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(wonx_display), sprite_num);
  ret = 0;

  /* これは本当か？ 逆では？ */
  ret |= WWSprite_GetX(s) << 8;
  ret |= WWSprite_GetY(s);

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void sprite_set_char_location(unsigned int sprite_num,
			      unsigned int data, int x, int y)
{
  if (wonx_display == NULL) Wonx_Create();

  printf("sprite_set_char_location(): number = %ud, data = %ud, x = %d, y = %d, ",
	 sprite_num, data, x, y); fflush(stdout);

  sprite_set_char(sprite_num, data);
  sprite_set_location(sprite_num, x, y);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned long int sprite_get_char_location(unsigned int sprite_num)
{
  unsigned long int ret;

  printf("sprite_get_char_location(): number = %ud, ",
	 sprite_num); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  ret = 0;
  /* これは本当か？ 逆では？ */
  ret |= sprite_get_char(sprite_num) << 16;
  ret |= sprite_get_location(sprite_num);

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ul\n", ret); fflush(stdout);

  return (ret);
}

void sprite_set_data(unsigned sprite_num, unsigned int count, void * data)
{
  int i;
  char * d;
  unsigned long int * n;

  printf("sprite_set_data(): number = %ud, count = %ud, data = %p",
	 sprite_num, count, data); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  n = (unsigned long int *)data;
  for (i = 0; i < count; i++) {
    sprite_set_char_location(sprite_num + i,
			     n[i] >> 16,
			     (n[i] >> 8) & 0xff,
			     n[i] & 0xff);
  }

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

void screen_set_scroll(int screen, int x, int y)
{
  WWScreen s;

  printf("screen_set_scroll(): scsreen = %d, x = %d, y = %d, ",
	 screen, x, y); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx_display), screen);
  WWScreen_SetRollX(s, x);
  WWScreen_SetRollY(s, y);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int screen_get_scroll(int screen)
{
  unsigned short int ret;
  WWScreen s;

  printf("screen_get_scroll(): scsreen = %d, ", screen); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx_display), screen);

  ret = 0;
  ret |= WWScreen_GetRollX(s);
  ret |= WWScreen_GetRollY(s) << 8;

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void screen2_set_window(int x, int y, int w, int h)
{
  if (wonx_display == NULL) Wonx_Create();
  /* あとで書くこと */

  WonxDisplay_Flush(wonx_display);
}

unsigned long int screen2_get_window(void)
{
  if (wonx_display == NULL) Wonx_Create();
  /* あとで書くこと */

  WonxDisplay_Flush(wonx_display);
}

void sprite_set_window(int x, int y, int w, int h)
{
  if (wonx_display == NULL) Wonx_Create();
  /* あとで書くこと */

  WonxDisplay_Flush(wonx_display);
}

unsigned long int sprite_get_window(void)
{
  if (wonx_display == NULL) Wonx_Create();
  /* あとで書くこと */

  WonxDisplay_Flush(wonx_display);
}

void palette_set_color(unsigned int palette_num,
		       unsigned int colors)
{
  int mapped_colors[4];
  WWPalette palette;

  printf("palette_set_color(): number = %ud, colors = %ud", palette_num,
	 colors); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  mapped_colors[0] = colors & 0x07;
  mapped_colors[1] = (colors >>  4) & 0x07;
  mapped_colors[2] = (colors >>  8) & 0x07;
  mapped_colors[3] = (colors >> 12) & 0x07;

  palette = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx_display), palette_num);

  WWPalette_SetMappedColors(palette, mapped_colors);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned int palette_get_color(unsigned int palette_num)
{
  int mapped_colors[4];
  WWPalette palette;
  unsigned short int ret;

  printf("palette_get_color(): number = %ud, ", palette_num); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  palette = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx_display), palette_num);
  WWPalette_GetMappedColors(palette, mapped_colors);

  ret = 0;
  ret |= mapped_colors[0] & 0x07;
  ret |= (mapped_colors[1] & 0x07) <<  4;
  ret |= (mapped_colors[2] & 0x07) <<  8;
  ret |= (mapped_colors[3] & 0x07) << 12;

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ud\n", ret); fflush(stdout);

  return (ret);
}

void lcd_set_color(unsigned int colors0, unsigned int colors1)
{
  WWColorMap color_map;
  int lcd_colors[8];

  printf("lcd_set_color(): colors0 = %ud, colors1 = %ud, ", colors0, colors1); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  lcd_colors[0] =  colors0        & 0x0f;
  lcd_colors[1] = (colors0 >>  4) & 0x0f;
  lcd_colors[2] = (colors0 >>  8) & 0x0f;
  lcd_colors[3] = (colors0 >> 12) & 0x0f;
  lcd_colors[4] =  colors1        & 0x0f;
  lcd_colors[5] = (colors1 >>  4) & 0x0f;
  lcd_colors[6] = (colors1 >>  8) & 0x0f;
  lcd_colors[7] = (colors1 >> 12) & 0x0f;

  color_map = WWDisplay_GetColorMap(WonxDisplay_GetWWDisplay(wonx_display));
  WWColorMap_SetLCDColors(color_map, lcd_colors);

  WonxDisplay_Flush(wonx_display);

  printf("return value = none\n"); fflush(stdout);

  return;
}

unsigned long int lcd_get_color(void)
{
  WWColorMap color_map;
  int lcd_colors[8];
  unsigned long int ret;

  printf("lcd_get_color(): "); fflush(stdout);

  if (wonx_display == NULL) Wonx_Create();

  color_map = WWDisplay_GetColorMap(WonxDisplay_GetWWDisplay(wonx_display));
  WWColorMap_GetLCDColors(color_map, lcd_colors);

  ret = 0;
  ret |=  lcd_colors[0] & 0x0f;
  ret |= (lcd_colors[1] & 0x0f) <<  4;
  ret |= (lcd_colors[2] & 0x0f) <<  8;
  ret |= (lcd_colors[3] & 0x0f) << 12;
  ret |=  lcd_colors[0] & 0x0f;
  ret |= (lcd_colors[1] & 0x0f) <<  4;
  ret |= (lcd_colors[2] & 0x0f) <<  8;
  ret |= (lcd_colors[3] & 0x0f) << 12;

  WonxDisplay_Flush(wonx_display);

  printf("return value = %ul\n", ret); fflush(stdout);

  return (ret);
}

void lcd_set_segments(unsigned segments)
{
  if (wonx_display == NULL) Wonx_Create();
  /* セグメント表示は未サポートか？ */

  WonxDisplay_Flush(wonx_display);
}

unsigned lcd_get_segments(void)
{
  if (wonx_display == NULL) Wonx_Create();
  /* セグメント表示は未サポートか？ */

  WonxDisplay_Flush(wonx_display);
}

void lcd_set_sleep(unsigned sleep)
{
  if (wonx_display == NULL) Wonx_Create();
  /* ? */

  WonxDisplay_Flush(wonx_display);
}

unsigned lcd_get_sleep(void)
{
  if (wonx_display == NULL) Wonx_Create();
  /* ? */

  WonxDisplay_Flush(wonx_display);
}

void screen_set_vram(int screen, int locationID)
{
  if (wonx_display == NULL) Wonx_Create();

  WonxDisplay_Flush(wonx_display);
}

void sprite_set_vram(int locationID)
{
  if (wonx_display == NULL) Wonx_Create();

  WonxDisplay_Flush(wonx_display);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
