/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/disp.h"

#include "Wonx.h"

/*****************************************************************************/
/* 互換関数の定義                                                            */
/*****************************************************************************/

/*
 * void * でデータを渡す関数は，型を間違えるバグが入る可能性があるので，
 * void * を適切な型に置き換えてある．
 */

/*
 * Xサーバとの同期の整合性がとれなくなるなどの問題が考えられるので，
 * 互換関数の内部は UNIXTimer_Pause(), UNIXTimer_Unpause() でくくり，
 * タイマ割り込みを一時停止して処理を行う．また，unpause するまえに，
 * かならず sync するようにする．
 */

/*
 * タイマの一時停止の２重解除の問題が出てくるので，
 * 互換関数から互換関数を呼んではいけない．
 * (一時停止はネストされるが，いちおう)
 * 似たような処理をする関数の場合は，必ず static な別関数に処理をまとめ，
 * そっちを呼び出すようにすること．
 * 引数の表示の問題もあるしね．
 */

void display_control(unsigned int flags)
{
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : display_control() : flags = 0x%04x\n", (int)flags);
  fflush(stdout);

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWScreen_SetEnable(WWDisplay_GetScreen(ww_display, SCREEN1),
		     (flags & DCM_SCR1) ? 1 : 0);

  WWScreen_SetEnable(WWDisplay_GetScreen(ww_display, SCREEN2),
		     (flags & DCM_SCR2) ? 1 : 0);

  WWDisplay_SetSpriteEnable(ww_display, (flags & DCM_SPR) ? 1 : 0);

  WWDisplay_SetSpriteWindowEnable(ww_display, (flags & DCM_SPR_WIN) ? 1 : 0);

  if      ((flags & 0x0030) == DCM_SCR2_WIN_INSIDE)
    WWScreen_SetMode(WWDisplay_GetScreen(ww_display, SCREEN2),
		     WW_SCREEN_INSIDE_ONLY);
  else if ((flags & 0x0030) == DCM_SCR2_WIN_OUTSIDE)
    WWScreen_SetMode(WWDisplay_GetScreen(ww_display, SCREEN2),
		     WW_SCREEN_OUTSIDE_ONLY);

  WWDisplay_SetBorder(ww_display, (flags & DCM_BORDER_COLOR) >> 7);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : display_control() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int display_status(void)
{
  WWDisplay ww_display;
  unsigned short int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : display_status() : \n"); fflush(stdout);

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  ret = 0;

  if (WWScreen_GetEnable(WWDisplay_GetScreen(ww_display, SCREEN1)))
    ret |= DCM_SCR1;

  if (WWScreen_GetEnable(WWDisplay_GetScreen(ww_display, SCREEN2)))
    ret |= DCM_SCR2;

  if (WWDisplay_GetSpriteEnable(ww_display))
    ret |= DCM_SPR;

  if (WWDisplay_GetSpriteWindowEnable(ww_display))
    ret |= DCM_SPR_WIN;

  switch (WWScreen_GetMode(WWDisplay_GetScreen(ww_display, SCREEN2))) {
    case WW_SCREEN_INSIDE_ONLY:
      ret |= DCM_SCR2_WIN_INSIDE;
      break;
    case WW_SCREEN_OUTSIDE_ONLY:
      ret |= DCM_SCR2_WIN_OUTSIDE;
      break;
    default:
  }

  ret |= WWDisplay_GetBorder(ww_display) << 7;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : display_status() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned char * data にした．
 */
void font_set_monodata(unsigned int number, unsigned int count,
		       unsigned char * data)
{
  WWCharacter c;
  int i, x, y, n, p;
  int f, b;
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : font_set_monodata() : number = %u, count = %u, data = %p\n",
	 (int)number, (int)count, (void *)data); fflush(stdout);

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  f = WWDisplay_GetForegroundColor(ww_display);
  b = WWDisplay_GetBackgroundColor(ww_display);

  n = 0;
  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(ww_display, number + i);
    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {
	p = (data[n] & (1 << (7 - x))) ? f : b; /*これでよいのか？*/
	WWCharacter_SetPixel(c, x, y, p);
      }
      n++;
    }
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : font_set_monodata() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned char * data にした．
 */
void font_set_colordata(unsigned int number, unsigned int count,
			unsigned char * data)
{
  WWCharacter c;
  int i, x, y, n, p;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : font_set_colordata() : number = %u, count = %u, data = %p\n",
	 (int)number, (int)count, (void *)data); fflush(stdout);

  n = 0;

  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			       number + i);
    for (y = 0; y < 8; y++) {
      for (x = 0; x < 8; x++) {

	/*これでよいのか？*/
	p = ((data[n] & (1 << (7-x))) ? 2 : 0)
	  + ((data[n + 1] & (1 << (7-x))) ? 1 : 0);

	WWCharacter_SetPixel(c, x, y, p);
      }
      n++;
      n++;
    }
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : font_set_colordata() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned char * data にした．
 */
void font_get_data(unsigned int number, unsigned int count,
		   unsigned char * data)
{
  /* 関数の仕様がわからんので適当に書くぞ */
  WWCharacter c;
  int i, x, y, n, p;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : font_get_data() : number = %u, count = %u, data = %p\n",
	 (int)number, (int)count, (void *)data); fflush(stdout);

  n = 0;

  for (i = 0; i < count; i++) {
    c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			       number + i);
    for (y = 0; y < 8; y++) {
      data[n  ] = 0;
      data[n+1] = 0;
      for (x = 0; x < 8; x++) {
	p = WWCharacter_GetPixel(c, x, y);
	/* これでよいのか？ */
	data[n  ] |= (((unsigned char)p & 0x02) ? 1 : 0) << (7-x);
	data[n+1] |= (((unsigned char)p & 0x01) ? 1 : 0) << (7-x);
      }
      n++;
      n++;
    }
  }

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : font_get_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void font_set_color(unsigned int colors)
{
  WWDisplay dis;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : font_set_color() : colors = 0x%04x\n", (int)colors);
  fflush(stdout);

  dis = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());
  WWDisplay_SetForegroundColor(dis, colors & 0x03);
  WWDisplay_SetBackgroundColor(dis, (colors >> 2) & 0x03);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : font_set_color() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int font_get_color(void)
{
  unsigned short int ret;
  WWDisplay dis;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : font_get_color() : \n"); fflush(stdout);

  dis = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());
  ret = 0;
  ret |= WWDisplay_GetForegroundColor(dis);
  ret |= WWDisplay_GetBackgroundColor(dis) << 2;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : font_get_color() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

static void _screen_set_char1(int screen, int x, int y,
			      unsigned short int data)
{
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  int palette_num; /* パレット番号 */
  int character_num; /* 表示キャラクタ */
  WWDisplay display;
  WWScreen s;
  WWPalette p;
  WWCharacter c;

  display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  s = WWDisplay_GetScreen(display, screen);

  horizontal    = (data & (1 << 15)) ? 1 : 0;
  vertical      = (data & (1 << 14)) ? 1 : 0;
  palette_num   = (data >> 9) & 0x0f;
  character_num = data & 0x1ff;

  p = WWDisplay_GetPalette(display, palette_num);
  c = WWDisplay_GetCharacter(display, character_num);

  WWScreen_SetHorizontal(s, x, y, horizontal);
  WWScreen_SetVertical(  s, x, y, vertical);
  WWScreen_SetPalette(   s, x, y, p);
  WWScreen_SetCharacter( s, x, y, c);

  return;
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned short int * data にした．
 */
void screen_set_char(int screen, int x, int y, int w, int h,
		     unsigned short int * data)
{
  int i, j;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_set_char() : screen = %d, x = %d, y = %d, w = %d, h = %d, data = %p\n",
	 screen, x, y, w, h, (void *)data);
  fflush(stdout);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      _screen_set_char1(screen, x + i, y + j, *data);
      data++;
    }
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : screen_set_char() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static unsigned int _screen_get_char1(int screen, int x, int y)
{
  int horizontal; /* 横方向反転フラグ */
  int vertical; /* 縦方向反転フラグ */
  int palette_num; /* パレット番号 */
  int character_num; /* 表示キャラクタ */
  WWScreen s;
  WWPalette p;
  WWCharacter c;
  unsigned short int ret;

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  screen);

  horizontal    = WWScreen_GetHorizontal(s, x, y);
  vertical      = WWScreen_GetVertical(  s, x, y);
  p             = WWScreen_GetPalette(   s, x, y);
  c             = WWScreen_GetCharacter( s, x, y);
  palette_num   = WWPalette_GetNumber(p);
  character_num = WWCharacter_GetNumber(c);

  ret = 0;
  ret |= horizontal << 15;
  ret |= vertical << 14;
  ret |= palette_num << 9;
  ret |= character_num;

  return (ret);
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned short int * data にした．
 */
void screen_get_char(int screen, int x, int y, int w, int h,
		     unsigned short int * data)
{
  int i, j;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_get_char() : screen = %d, x = %d, y = %d, w = %d, h = %d, data = %p\n",
	 screen, x, y, w, h, (void *)data);
  fflush(stdout);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      *data = _screen_get_char1(screen, x, y);
      data++;
    }
  }

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : screen_get_char() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int screen_get_char1(int screen, int x, int y)
{
  unsigned short int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_get_char1() : screen = %d, x = %d, y = %d\n",
	 screen, x, y);
  fflush(stdout);

  ret = _screen_get_char1(screen, x, y);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : screen_get_char1() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void screen_fill_char(int screen, int x, int y, int w, int h,
		      unsigned int data)
{
  int i, j;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_fill_char() : screen = %d, x = %d, y = %d, w = %d, h = %d, data = 0x%04x\n",
	 screen, x, y, w, h, (int)data);
  fflush(stdout);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      _screen_set_char1(screen, x + i, y + j, data);
    }
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : screen_fill_char() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void screen_fill_attr(int screen, int x, int y, int w, int h,
		      unsigned int data, unsigned int mask)
{
  int i, j;
  unsigned short int c;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_fill_attr() : screen = %d, x = %d, y = %d, w = %d, h = %d, data = 0x%04x, mask = 0x%04x\n",
	 screen, x, y, w, h, (int)data, (int)mask); fflush(stdout);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      c = _screen_get_char1(screen, x + i, y + j);
      c &= mask;
      c |= data;
      _screen_set_char1(screen, x + i, y + j, c);
    }
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : screen_fill_attr() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void sprite_set_range(unsigned int start, unsigned int number)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_range() : start = %u, number = %u\n",
	 (int)start, (int)number); fflush(stdout);

  WWDisplay_SetSpriteStart(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			   start);
  WWDisplay_SetSpriteCount(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			   number);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_range() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static void _sprite_set_char(unsigned int sprite_num, unsigned int data)
{
  WWSprite s;
  WWPalette p;
  WWCharacter c;

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  sprite_num);

  WWSprite_SetHorizontal(s, (data >> 15) ? 1 : 0);
  WWSprite_SetVertical(  s, (data >> 14) ? 1 : 0);
  WWSprite_SetPriority(  s, (data >> 13) ? 1 : 0);
  WWSprite_SetClipping(  s, (data >> 12) ? 1 : 0);

  /* 8を引いた値でパレット番号が指定されるので，8を足してやる */
  p = WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			   ((data >> 9) & 0x07) + 8);

  c = WWDisplay_GetCharacter(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			     data & 0x1ff);

  WWSprite_SetPalette(s, p);
  WWSprite_SetCharacter(s, c);

  return;
}

void sprite_set_char(unsigned int sprite_num, unsigned int data)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_char() : number = %u, data = 0x%04x\n",
	 (int)sprite_num, (int)data); fflush(stdout);

  _sprite_set_char(sprite_num, data);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_char() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static unsigned int _sprite_get_char(unsigned int sprite_num)
{
  WWSprite s;
  WWPalette p;
  WWCharacter c;
  unsigned short int ret;

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  sprite_num);

  ret = 0;

  ret |= (WWSprite_GetHorizontal(s) ? 1 : 0) << 15;
  ret |= (WWSprite_GetVertical(  s) ? 1 : 0) << 14;
  ret |= (WWSprite_GetPriority(  s) ? 1 : 0) << 13;
  ret |= (WWSprite_GetClipping(  s) ? 1 : 0) << 12;

  p = WWSprite_GetPalette(s);
  c = WWSprite_GetCharacter(s);

  /* 8を引いた値でパレット番号が指定されるので，8を引いてやる */
  ret |= ((WWPalette_GetNumber(p) - 8) & 0x07) << 9;
  ret |= WWCharacter_GetNumber(c);

  return (ret);
}

unsigned int sprite_get_char(unsigned int sprite_num)
{
  unsigned short int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_get_char() : number = %u\n", (int)sprite_num);
  fflush(stdout);

  ret = _sprite_get_char(sprite_num);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : sprite_get_char() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

static void _sprite_set_location(unsigned int sprite_num, int x, int y)
{
  WWSprite s;

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  sprite_num);
  WWSprite_SetPosition(s, x, y);

  return;
}

void sprite_set_location(unsigned int sprite_num, int x, int y)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_location() : number = %u, x = %d, y = %d\n",
	 (int)sprite_num, x, y);
  fflush(stdout);

  _sprite_set_location(sprite_num, x, y);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_location() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static unsigned int _sprite_get_location(unsigned int sprite_num)
{
  WWSprite s;
  unsigned short int ret;

  s = WWDisplay_GetSprite(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  sprite_num);

  ret = (WWSprite_GetY(s) << 8) | WWSprite_GetX(s);

  return (ret);
}

unsigned int sprite_get_location(unsigned int sprite_num)
{
  unsigned short int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_get_location() : number = %u\n", (int)sprite_num);
  fflush(stdout);

  ret = _sprite_get_location(sprite_num);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : sprite_get_location() : return value = 0x%04x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

static void _sprite_set_char_location(unsigned int sprite_num,
				      unsigned int data, int x, int y)
{
  _sprite_set_char(sprite_num, data);
  _sprite_set_location(sprite_num, x, y);

  return;
}

void sprite_set_char_location(unsigned int sprite_num,
			      unsigned int data, int x, int y)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_char_location() : number = %u, data = 0x%04x, x = %d, y = %d\n",
	 (int)sprite_num, (int)data, x, y);
  fflush(stdout);

  _sprite_set_char_location(sprite_num, data, x, y);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_char_location() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned long int sprite_get_char_location(unsigned int sprite_num)
{
  unsigned long int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_get_char_location() : number = %u\n", (int)sprite_num);
  fflush(stdout);

  ret = 0;
  ret |= ((unsigned long int)_sprite_get_char(sprite_num));
  ret |= (unsigned long int)_sprite_get_location(sprite_num) << 16;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : sprite_get_char_location() : return value = 0x%08x\n",
	 (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

/*
 * void * data だと，まちがって int * でデータを指定するようなバグが
 * 入る可能性があるので，unsigned long int * data にした．
 */
void sprite_set_data(unsigned int sprite_num, unsigned int count,
		     unsigned long int * data)
{
  int i;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_data() : number = %u, count = %u, data = %p\n",
	 (int)sprite_num, (int)count, (void *)data);
  fflush(stdout);

  for (i = 0; i < count; i++) {
    _sprite_set_char_location(sprite_num + i,
			      data[i] >> 16,
			      (data[i] >> 8) & 0xff,
			      data[i] & 0xff);
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_data() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void screen_set_scroll(int screen, int x, int y)
{
  WWScreen s;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_set_scroll() : screen = %d, x = %d, y = %d\n",
	 screen, x, y);
  fflush(stdout);

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  screen);
  WWScreen_SetRollX(s, x);
  WWScreen_SetRollY(s, y);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : screen_set_scroll() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int screen_get_scroll(int screen)
{
  unsigned short int ret;
  WWScreen s;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen_get_scroll() : screen = %d\n", screen); fflush(stdout);

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  screen);

  ret = 0;
  ret |= WWScreen_GetRollX(s);
  ret |= WWScreen_GetRollY(s) << 8;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : screen_get_scroll() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void screen2_set_window(int x, int y, int w, int h)
{
  WWScreen s;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen2_set_window() : x = %d, y = %d, width = %d, height = %d\n",
	 x, y, w, h); fflush(stdout);

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  SCREEN2);
  WWScreen_SetDrawX(s, x);
  WWScreen_SetDrawY(s, y);
  WWScreen_SetDrawWidth( s, w);
  WWScreen_SetDrawHeight(s, h);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : screen2_set_window() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned long int screen2_get_window(void)
{
  WWScreen s;
  unsigned short int xy;
  unsigned short int wh;
  unsigned long int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : screen2_get_window() : \n"); fflush(stdout);

  s = WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			  SCREEN2);

  xy =
    (((unsigned short int)WWScreen_GetDrawY(s) << 8) & 0xff00) |
    ((unsigned short int)WWScreen_GetDrawX(s) & 0x00ff);
  wh =
    (((unsigned short int)WWScreen_GetDrawHeight(s) << 8) & 0xff00) |
    ((unsigned short int)WWScreen_GetDrawWidth(s) & 0x00ff);
  ret = ((unsigned long int)wh) << 16 | xy;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : screen2_get_window() : return value = 0x%08x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void sprite_set_window(int x, int y, int w, int h)
{
  WWDisplay d;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_set_window() : x = %d, y = %d, w = %d, h = %d\n",
	 x, y, w, h);
  fflush(stdout);

  d = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWDisplay_SetSpriteWindowX(d, x);
  WWDisplay_SetSpriteWindowY(d, y);
  WWDisplay_SetSpriteWindowWidth(d, w);
  WWDisplay_SetSpriteWindowHeight(d, h);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : sprite_set_window() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned long int sprite_get_window(void)
{
  WWDisplay d;
  unsigned short int xy;
  unsigned short int wh;
  unsigned long int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : sprite_get_window() : \n");
  fflush(stdout);

  d = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  xy =
    (((unsigned short int)WWDisplay_GetSpriteWindowY(d) << 8) & 0xff00) |
    ((unsigned short int)WWDisplay_GetSpriteWindowX(d) & 0x00ff);
  wh =
    (((unsigned short int)WWDisplay_GetSpriteWindowHeight(d) << 8) & 0xff00) |
    ((unsigned short int)WWDisplay_GetSpriteWindowWidth(d) & 0x00ff);
  ret = ((unsigned long int)wh) << 16 | xy;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : sprite_get_window() : return value = 0x%08x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void palette_set_color(unsigned int palette_num, unsigned int colors)
{
  int mapped_colors[4];
  WWPalette palette;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : palette_set_color() : number = %u, colors = 0x%04x\n",
	 (int)palette_num, (int)colors); fflush(stdout);

  mapped_colors[0] = colors & 0x07;
  mapped_colors[1] = (colors >>  4) & 0x07;
  mapped_colors[2] = (colors >>  8) & 0x07;
  mapped_colors[3] = (colors >> 12) & 0x07;

  palette =
    WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			 palette_num);

  WWPalette_SetMappedColors(palette, mapped_colors);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : palette_set_color() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int palette_get_color(unsigned int palette_num)
{
  int mapped_colors[4];
  WWPalette palette;
  unsigned short int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : palette_get_color() : number = %u\n", (int)palette_num);
  fflush(stdout);

  palette =
    WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()),
			 palette_num);
  WWPalette_GetMappedColors(palette, mapped_colors);

  ret = 0;
  ret |= mapped_colors[0] & 0x07;
  ret |= (mapped_colors[1] & 0x07) <<  4;
  ret |= (mapped_colors[2] & 0x07) <<  8;
  ret |= (mapped_colors[3] & 0x07) << 12;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : palette_get_color() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void lcd_set_color(unsigned int colors0, unsigned int colors1)
{
  WWColorMap color_map;
  int lcd_colors[8];

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : lcd_set_color() : colors0 = 0x%04x, colors1 = 0x%04x\n",
	 (int)colors0, (int)colors1); fflush(stdout);

  lcd_colors[0] =  colors0        & 0x0f;
  lcd_colors[1] = (colors0 >>  4) & 0x0f;
  lcd_colors[2] = (colors0 >>  8) & 0x0f;
  lcd_colors[3] = (colors0 >> 12) & 0x0f;
  lcd_colors[4] =  colors1        & 0x0f;
  lcd_colors[5] = (colors1 >>  4) & 0x0f;
  lcd_colors[6] = (colors1 >>  8) & 0x0f;
  lcd_colors[7] = (colors1 >> 12) & 0x0f;

  color_map =
    WWDisplay_GetColorMap(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()));
  WWColorMap_SetLCDColors(color_map, lcd_colors);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : lcd_set_color() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned long int lcd_get_color(void)
{
  WWColorMap color_map;
  int lcd_colors[8];
  unsigned long int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : lcd_get_color() : \n"); fflush(stdout);

  color_map =
    WWDisplay_GetColorMap(WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay()));
  WWColorMap_GetLCDColors(color_map, lcd_colors);

  ret = 0;
  ret |=  (unsigned long int)lcd_colors[0] & 0x0f;
  ret |= ((unsigned long int)lcd_colors[1] & 0x0f) <<  4;
  ret |= ((unsigned long int)lcd_colors[2] & 0x0f) <<  8;
  ret |= ((unsigned long int)lcd_colors[3] & 0x0f) << 12;
  ret |=  (unsigned long int)lcd_colors[0] & 0x0f;
  ret |= ((unsigned long int)lcd_colors[1] & 0x0f) <<  4;
  ret |= ((unsigned long int)lcd_colors[2] & 0x0f) <<  8;
  ret |= ((unsigned long int)lcd_colors[3] & 0x0f) << 12;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : lcd_get_color() : return value = 0x%08x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void lcd_set_segments(unsigned int segments)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* セグメント表示は未サポートか？ */

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int lcd_get_segments(void)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* セグメント表示は未サポートか？ */

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (0);
}

void lcd_set_sleep(unsigned int slp)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* ? */

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int lcd_get_sleep(void)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* ? */

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (0);
}

void screen_set_vram(int screen, int location_id)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* 未サポート */

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void sprite_set_vram(int location_id)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  /* 未サポート */

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
