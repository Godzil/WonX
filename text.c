/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wonx_include/text.h"

#include "WonX.h"
#include "WWText.h"
#include "WWDisplay.h"
#include "WWCursor.h"
#include "etc.h"

/*****************************************************************************/
/* 互換関数の定義                                                            */
/*****************************************************************************/

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

static void _text_window_init(int x, int y, int w, int h, unsigned int base)
{
  WWDisplay ww_display;
  WWText ww_text;

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  WWText_SetTextWindow(ww_text, x, y, w, h, base, ww_display);

  WWScreen_SetRollX(WWText_GetScreen(ww_text), 0);
  WWScreen_SetRollY(WWText_GetScreen(ww_text), 0);

  return;
}

void text_screen_init(void)
{
  WWDisplay ww_display;
  WWLCDPanel ww_lcd_panel;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_screen_init() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_lcd_panel = WWDisplay_GetLCDPanel(ww_display);

  _text_window_init(0, 0, TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT, 8);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_screen_init() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void text_window_init(int x, int y, int w, int h, unsigned int base)
{
  WWDisplay ww_display;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_window_init() : x = %d, y = %d, width = %d, height = %d, base = %u\n", x, y, w, h, (int)base);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());

  _text_window_init(x, y, w, h, base);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_window_init() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void text_set_mode(int mode)
{
}

int text_get_mode(void)
{
  return (0);
}

static void _text_put_char(int x, int y, unsigned int c)
{
  WWDisplay ww_display;
  WWText ww_text;

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  WWText_PutCharacter(ww_text, x, y, c, ww_display);

  return;
}

void text_put_char(int x, int y, unsigned int c)
{
  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_put_char() : x = %d, y = %d, character = \'", x, y);
  wonx_print_character(stdout, c);
  printf("\'\n");
  fflush(stdout);

  _text_put_char(x, y, c);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_put_char() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

static int _text_put_string(int x, int y, char * string)
{
  int i, len, ret;
  WWDisplay ww_display;
  WWText ww_text;

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  len = strlen(string);
  ret = 0;
  for (i = 0; i < len; i++) {
    if (WWText_PutCharacter(ww_text, x + i, y, string[i], ww_display) >= 0)
      ret++;
  }

  return (ret);
}

int text_put_string(int x, int y, char * string)
{
  int ret;
  char * p;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_put_string() : x = %d, y = %d, string = \"", x, y);
  for (p = string; *p != '\0'; p++) wonx_print_character(stdout, *p);
  printf("\"\n");
  fflush(stdout);

  ret = _text_put_string(x, y, string);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_put_string() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int text_put_substring(int x, int y, char * s, int length)
{
  int i, ret;
  WWDisplay ww_display;
  WWText ww_text;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_put_substring() : x = %d, y = %d, length = %d, string = \"", x, y, length);
  for (i = 0; i < length; i++) wonx_print_character(stdout, s[i]);
  printf("\"\n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  ret = 0;
  for (i = 0; i < length; i++) {
    if (WWText_PutCharacter(ww_text, x + i, y, s[i], ww_display) >= 0)
      ret++;
  }

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_put_substring() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void text_put_numeric(int x, int y, int length, int format, int number)
{
  char buf[20];
  char f[20];

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_put_numeric() : x = %d, y = %d, length = %d, format = %04x, number = %d\n", x, y, length, format, number);
  fflush(stdout);

  strcpy(f, "%");

  if (format & NUM_PADZERO) strcat(f, "0");
  sprintf(f + strlen(f), "%d", length);
  if (format & NUM_HEXA) strcat(f, "x");
  else if (format & NUM_SIGNED) strcat(f, "d");
  else strcat(f, "u");
  if (format & NUM_ALIGN_LEFT) { /* 未実装 */ }

  sprintf(buf, f, number);
  _text_put_string(x, y, buf);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_put_numeric() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void text_store_numeric(char * buffer, int length, int format, int number)
{
}

void text_fill_char(int x, int y, int length, int c)
{
  int i;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_fill_char() : x = %d, y = %d, length = %d, character = %d\n", x, y, length, c);
  fflush(stdout);

  for (i = 0; i < length; i++) {
    _text_put_char(x + i, y, c);
  }

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_fill_char() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

void text_set_palette(int palette_num)
{
  WWDisplay ww_display;
  WWText ww_text;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_set_palette() : palette = %d\n", palette_num);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  WWText_SetPalette(ww_text, WWDisplay_GetPalette(ww_display, palette_num));

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_set_palette() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int text_get_palette(void)
{
  WWDisplay ww_display;
  WWText ww_text;
  int num;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_get_palette() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  num = WWPalette_GetNumber(WWText_GetPalette(ww_text));

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : text_get_palette() : return value = %d\n", num);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (num);
}

void text_set_ank_font(int base, int color, int count, void * font)
{
}

void text_set_sjis_font(void * p)
{
}

void text_get_fontdata(int c, void * buffer)
{
}

void text_set_screen(int screen)
{
  WWDisplay ww_display;
  WWText ww_text;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_set_screen() : screen = %d\n", screen);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  WWText_SetScreen(ww_text, WWDisplay_GetScreen(ww_display, screen));

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_set_screen() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int text_get_screen(void)
{
  WWDisplay ww_display;
  WWText ww_text;
  int n;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : text_get_screen() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_text = WWDisplay_GetText(ww_display);

  n = WWScreen_GetNumber(WWText_GetScreen(ww_text));

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : text_set_screen() : return value = %d\n", n);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (n);
}

void cursor_display(int flag)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_display() : flag = %d\n", flag);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  switch (flag) {
  case 0: WWCursor_OFF(ww_cursor); break;
  case 1: WWCursor_ON( ww_cursor); break;
  default:
    WonX_Warning("cursor_display", "Cursor flag is 0 or 1.");
    WWCursor_ON(ww_cursor); /* 一応 ON にしとく */
  }

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : cursor_display() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

int cursor_status(void)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;
  int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_status() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  ret = WWCursor_IsON(ww_cursor) ? 1 : 0;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : cursor_status() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void cursor_set_location(int x, int y, int w, int h)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_set_location() : x = %d, y = %d, w = %d, h = %d\n",
	 x, y, w, h);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  if (x < 0)
    WonX_Warning("cursor_set_location", "Value of x is too small.");
  if (x > TEXT_SCREEN_WIDTH - 1)
    WonX_Warning("cursor_set_location", "Value of x is too large.");
  if (y < 0)
    WonX_Warning("cursor_set_location", "Value of y is too small.");
  if (y > TEXT_SCREEN_HEIGHT - 1)
    WonX_Warning("cursor_set_location", "Value of y is too large.");
  if (w <= 0)
    WonX_Warning("cursor_set_location", "Value of w is too small.");
  if (h <= 0)
    WonX_Warning("cursor_set_location", "Value of h is too small.");

  WWCursor_SetX(ww_cursor, x);
  WWCursor_SetY(ww_cursor, y);
  WWCursor_SetWidth( ww_cursor, w);
  WWCursor_SetHeight(ww_cursor, h);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : cursor_set_location() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

unsigned long int cursor_get_location(void)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;
  unsigned long int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_get_location() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  ret = 0;
  ret |= (((unsigned long int)WWCursor_GetX(     ww_cursor) & 0xff) <<  0);
  ret |= (((unsigned long int)WWCursor_GetY(     ww_cursor) & 0xff) <<  8);
  ret |= (((unsigned long int)WWCursor_GetWidth( ww_cursor) & 0xff) << 16);
  ret |= (((unsigned long int)WWCursor_GetHeight(ww_cursor) & 0xff) << 24);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : cursor_get_location() : return value = 0x%08x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

void cursor_set_type(int palette_num, int interval)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_set_type() : palette = %d, interval = %d\n",
	 palette_num, interval);
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  if (palette_num < 0)
    WonX_Error("cursor_set_type", "Palette number is too small.");
  if (palette_num > 15)
    WonX_Error("cursor_set_type", "Palette number is too large.");
  if (interval < 0)
    WonX_Warning("cursor_set_type", "Value of interval is too small.");
  if (interval > 255)
    WonX_Warning("cursor_set_type", "Value of interval is too small.");

  WWCursor_SetPalette(ww_cursor,
		      WWDisplay_GetPalette(ww_display, palette_num));
  WWCursor_SetInterval(ww_cursor, interval);

  WonXDisplay_Flush(WonX_GetWonXDisplay());

  printf("call : cursor_set_type() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return;
}

unsigned long int cursor_get_type(void)
{
  WWDisplay ww_display;
  WWCursor ww_cursor;
  unsigned long int ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : cursor_get_type() : \n");
  fflush(stdout);

  ww_display = WonXDisplay_GetWWDisplay(WonX_GetWonXDisplay());
  ww_cursor = WWDisplay_GetCursor(ww_display);

  ret = WWPalette_GetNumber(WWCursor_GetPalette(ww_cursor));
  ret |= (((unsigned long int)WWCursor_GetInterval(ww_cursor) & 0xff) << 8);

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : cursor_get_type() : return value = 0x%08x\n", (int)ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

int text_printf(int x, int y, const char *format, ...)
{
  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
