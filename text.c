#include <stdlib.h>
#include <string.h>

#include <sys/text.h>

#include "Wonx.h"
#include "WWText.h"

static void _text_window_init(int x, int y, int w, int h, unsigned font_base)
{
  WWText ww_text;
  WWDisplay ww_display;

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetTextWindow(ww_text, x, y, w, h, font_base, ww_display);

  WWScreen_SetRollX(WWText_GetScreen(ww_text), 0);
  WWScreen_SetRollY(WWText_GetScreen(ww_text), 0);

  return;
}

void text_screen_init(void)
{
  WWDisplay ww_display;
  WWLCDPanel ww_lcd_panel;

  printf("call : text_screen_init() : \n");
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());
  ww_lcd_panel = WWDisplay_GetLCDPanel(ww_display);

  _text_window_init(0, 0, TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT, 8);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_screen_init() : return value = none\n"); fflush(stdout);

  return;
}

void text_window_init(int x, int y, int w, int h, unsigned int font_base)
{
  WWDisplay ww_display;

  printf("call : text_window_init() : x = %d, y = %d, width = %d, height = %d, base = %u\n", x, y, w, h, (int)font_base);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  _text_window_init(x, y, w, h, font_base);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_screen_init() : return value = none\n"); fflush(stdout);

  return;
}

void text_set_mode(int mode)
{
}

int text_get_mode(void)
{
  return (0);
}

void _text_put_char(int x, int y, unsigned int c)
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
  printf("call : text_put_char() : x = %d, y = %d, character = %u\n", x, y, (int)c);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  _text_put_char(x, y, c);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_char() : return value = none\n"); fflush(stdout);

  return;
}

static int _text_put_string(int x, int y, char * s)
{
  int i, len, ret;
  WWText ww_text;
  WWDisplay ww_display;

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  len = strlen(s);
  ret = 0;
  for (i = 0; i < len; i++) {
    if (WWText_PutCharacter(ww_text, x + i, y, s[i], ww_display) >= 0)
      ret++;
  }

  return (ret);
}

int text_put_string(int x, int y, char * s)
{
  int ret;

  printf("call : text_put_string() : x = %d, y = %d, string = %s\n", x, y, s);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ret = _text_put_string(x, y, s);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_string() : return value = %d\n", ret);
  fflush(stdout);

  return (ret);
}

int text_put_substring(int x, int y, char * s, int len)
{
  int i, ret;
  WWText ww_text;
  WWDisplay ww_display;

  printf("call : text_put_substring() : x = %d, y = %d, string = %s, length = %d\n", x, y, s, len);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  ret = 0;
  for (i = 0; i < len; i++) {
    if (WWText_PutCharacter(ww_text, x + i, y, s[i], ww_display) >= 0)
      ret++;
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_substring() : return value = %d\n", ret);
  fflush(stdout);

  return (ret);
}

void text_put_numeric(int x, int y, int len, int format, int number)
{
  char buf[20];
  char f[20];

  printf("call : text_put_numeric() : x = %d, y = %d, len = %d, format = %04x, number = %d\n", x, y, len, format, number);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  strcpy(f, "%");

  if (format & NUM_PADZERO) strcat(f, "0");
  sprintf(f + strlen(f), "%d", len);
  if (format & NUM_HEXA) strcat(f, "x");
  else if (format & NUM_SIGNED) strcat(f, "d");
  else strcat(f, "u");
  if (format & NUM_ALIGN_LEFT) { /* Ì¤¼ÂÁõ */ }

  sprintf(buf, f, number);
  _text_put_string(x, y, buf);

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_put_numeric() : return value = none\n");
  fflush(stdout);

  return;
}

void text_store_numeric(char * buffer, int len, int format, int number)
{
}

void text_fill_char(int x, int y, int len, int code)
{
  int i;

  printf("call : text_fill_char() : x = %d, y = %d, length = %d, code = %d\n", x, y, len, code);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  for (i = 0; i < len; i++) {
    _text_put_char(x + i, y, code);
  }

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_fill_char() : return value = none\n");
  fflush(stdout);

  return;
}

void text_set_palette(int palette_num)
{
  WWText ww_text;
  WWDisplay ww_display;

  printf("call : text_set_palette() : palette = %d\n", palette_num);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetPalette(ww_text, WWDisplay_GetPalette(ww_display, palette_num));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_palette() : return value = none\n");
  fflush(stdout);

  return;
}

int text_get_palette(void)
{
  WWText ww_text;
  int num;

  printf("call : text_get_palette() : \n");
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());

  num = WWPalette_GetNumber(WWText_GetPalette(ww_text));

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : text_get_palette() : return value = %d\n", num);
  fflush(stdout);

  return (num);
}

void text_set_ank_font(int font_base_num, int is_color, int font_count,
		       void * font)
{
}

void text_set_sjis_font(void * font_address)
{
}

void text_get_fontdata(int char_code, void * fontdata_buffer)
{
}

void text_set_screen(int screen)
{
  WWText ww_text;
  WWDisplay ww_display;

  printf("call : text_set_screen() : screen = %d\n", screen);
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());
  ww_display = WonxDisplay_GetWWDisplay(Wonx_GetWonxDisplay());

  WWText_SetScreen(ww_text, WWDisplay_GetScreen(ww_display, screen));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_screen() : return value = none\n");
  fflush(stdout);

  return;
}

int text_get_screen(void)
{
  WWText ww_text;
  int n;

  printf("call : text_get_screen() : \n");
  fflush(stdout);

  if (!Wonx_IsCreated()) Wonx_Create();

  ww_text = WonxText_GetWWText(Wonx_GetWonxText());

  n = WWScreen_GetNumber(WWText_GetScreen(ww_text));

  WonxDisplay_Flush(Wonx_GetWonxDisplay());

  printf("call : text_set_screen() : return value = %d\n", n);
  fflush(stdout);

  return (n);
}

void cursor_display(int cursor_enable)
{
}

int cursor_status(void)
{
  return (0);
}

void cursor_set_location(int x, int y, int w, int h)
{
}

unsigned long cursor_get_location(void)
{
  return (0);
}

void cursor_set_type(int palette_num, int blink_interval)
{
}

unsigned long cursor_get_type(void)
{
  return (0);
}

int text_printf(int x, int y, const char *format, ...)
{
  return (0);
}

