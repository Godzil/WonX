/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wonx_include/text.h"

#include "Wonx.h"
#include "WWText.h"

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
  WWText ww_text;
  WWDisplay ww_display;

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetTextWindow(ww_text, x, y, w, h, base, ww_display);

  WWScreen_SetRollX(WWText_GetScreen(ww_text), 0);
  WWScreen_SetRollY(WWText_GetScreen(ww_text), 0);

  return;
}

void text_screen_init(void)
{
  WWDisplay ww_display;
  WWLCDPanel ww_lcd_panel;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_screen_init() : \n");
  fflush(stdout);

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());
  ww_lcd_panel = WWDisplay_GetLCDPanel(ww_display);

  _text_window_init(0, 0, TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT, 8);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_screen_init() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void text_window_init(int x, int y, int w, int h, unsigned int base)
{
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_window_init() : x = %d, y = %d, width = %d, height = %d, base = %u\n", x, y, w, h, (int)base);
  fflush(stdout);

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  _text_window_init(x, y, w, h, base);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_screen_init() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

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
  WWText ww_text;
  WWDisplay ww_display;

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_PutCharacter(ww_text, x, y, c, ww_display);

  return;
}

void text_put_char(int x, int y, unsigned int c)
{
  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_put_char() : x = %d, y = %d, character = %u\n", x, y, (int)c);
  fflush(stdout);

  _text_put_char(x, y, c);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_char() : return value = none\n"); fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static int _text_put_string(int x, int y, char * string)
{
  int i, len, ret;
  WWText ww_text;
  WWDisplay ww_display;

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

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

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_put_string() : x = %d, y = %d, string = %s\n", x, y, string);
  fflush(stdout);

  ret = _text_put_string(x, y, string);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_string() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int text_put_substring(int x, int y, char * s, int length)
{
  int i, ret;
  WWText ww_text;
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_put_substring() : x = %d, y = %d, string = %s, length = %d\n", x, y, s, length);
  fflush(stdout);

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  ret = 0;
  for (i = 0; i < length; i++) {
    if (WWText_PutCharacter(ww_text, x + i, y, s[i], ww_display) >= 0)
      ret++;
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_substring() : return value = %d\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void text_put_numeric(int x, int y, int length, int format, int number)
{
  char buf[20];
  char f[20];

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

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

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_numeric() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void text_store_numeric(char * buffer, int length, int format, int number)
{
}

void text_fill_char(int x, int y, int length, int c)
{
  int i;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_fill_char() : x = %d, y = %d, length = %d, character = %d\n", x, y, length, c);
  fflush(stdout);

  for (i = 0; i < length; i++) {
    _text_put_char(x + i, y, c);
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_fill_char() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void text_set_palette(int palette_num)
{
  WWText ww_text;
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_set_palette() : palette = %d\n", palette_num);
  fflush(stdout);

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetPalette(ww_text, WWDisplay_GetPalette(ww_display, palette_num));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_palette() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

int text_get_palette(void)
{
  WWText ww_text;
  int num;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_get_palette() : \n");
  fflush(stdout);

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());

  num = WWPalette_GetNumber(WWText_GetPalette(ww_text));

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : text_get_palette() : return value = %d\n", num);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

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
  WWText ww_text;
  WWDisplay ww_display;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_set_screen() : screen = %d\n", screen);
  fflush(stdout);

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetScreen(ww_text, WWDisplay_GetScreen(ww_display, screen));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_screen() : return value = none\n");
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

int text_get_screen(void)
{
  WWText ww_text;
  int n;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : text_get_screen() : \n");
  fflush(stdout);

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());

  n = WWScreen_GetNumber(WWText_GetScreen(ww_text));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_screen() : return value = %d\n", n);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (n);
}

void cursor_display(int flag)
{
}

int cursor_status(void)
{
  return (0);
}

void cursor_set_location(int x, int y, int w, int h)
{
}

unsigned long int cursor_get_location(void)
{
  return (0);
}

void cursor_set_type(int palette_num, int interval)
{
}

unsigned long int cursor_get_type(void)
{
  return (0);
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
