#include <stdlib.h>

#include <sys/text.h>

#include "wonx.h"

#include "WonxDisplay.h"

void text_screen_init(void)
{
  if (wonx_display == NULL) Wonx_Create();
}

void text_window_init(int x, int y, int w, int h, unsigned font_base)
{
  if (wonx_display == NULL) Wonx_Create();
}

void text_set_mode(int mode)
{
  if (wonx_display == NULL) Wonx_Create();
}

int text_get_mode(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

void text_put_char(int x, int y, unsigned int c)
{
  if (wonx_display == NULL) Wonx_Create();
  printf("%c", (unsigned char)c);
}

int text_put_string(int x, int y, char * s)
{
  if (wonx_display == NULL) Wonx_Create();
  printf("%s\n", s);
  return (0);
}

int text_put_substring(int x, int y, char * s, int len)
{
  int i;
  if (wonx_display == NULL) Wonx_Create();
  for (i = 0; i < len; i++)
    printf("%c", s[i]);
  printf("\n");
  return (0);
}

void text_put_numeric(int x, int y, int len, int format, int number)
{
  if (wonx_display == NULL) Wonx_Create();
  printf("%d\n", number);
}

void text_store_numeric(char * buffer, int len, int format, int number)
{
  if (wonx_display == NULL) Wonx_Create();
  sprintf(buffer, "%d", number);
}

void text_fill_char(int x, int y, int len, int code)
{
  if (wonx_display == NULL) Wonx_Create();
  printf("%c\n", (unsigned char)code);
}

void text_set_palette(int palette_num)
{
  if (wonx_display == NULL) Wonx_Create();
}

int text_get_palette(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

void text_set_ank_font(int font_base_num, int is_color, int font_count,
		       void * font)
{
  if (wonx_display == NULL) Wonx_Create();
}

void text_set_sjis_font(void * font_address)
{
  if (wonx_display == NULL) Wonx_Create();
}

void text_get_fontdata(int char_code, void * fontdata_buffer)
{
  if (wonx_display == NULL) Wonx_Create();
}

void text_set_screen(int screen)
{
  if (wonx_display == NULL) Wonx_Create();
}

int text_get_screen(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

void cursor_display(int cursor_enable)
{
  if (wonx_display == NULL) Wonx_Create();
}

int cursor_status(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

void cursor_set_location(int x, int y, int w, int h)
{
  if (wonx_display == NULL) Wonx_Create();
}

unsigned long cursor_get_location(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

void cursor_set_type(int palette_num, int blink_interval)
{
  if (wonx_display == NULL) Wonx_Create();
}

unsigned long cursor_get_type(void)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

int text_printf(int x, int y, const char *format, ...)
{
  if (wonx_display == NULL) Wonx_Create();
  return (0);
}

