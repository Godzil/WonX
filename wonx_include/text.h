#ifndef _WONX_SYS_TEXT_H_
#define _WONX_SYS_TEXT_H_

#include "service.h"

#define NUM_PADSPACE    0
#define NUM_ALIGN_RIGHT 0
#define NUM_HEXA        (1 << 0)
#define NUM_PADZERO     (1 << 1)
#define NUM_ALIGN_LEFT  (1 << 2)
#define NUM_SIGNED      (1 << 3)
#define NUM_STORE       (1 << 7)

#define TEXT_MODE_ANK      0
#define TEXT_MODE_ANK_SJIS 1
#define TEXT_MODE_SJIS     2

#define TEXT_SCREEN_WIDTH  28
#define TEXT_SCREEN_HEIGHT 18

void text_screen_init(void);
void text_window_init(int x, int y, int w, int h, unsigned int base);
void text_set_mode(int mode);
int text_get_mode(void);
void text_put_char(int x, int y, unsigned int c);
int text_put_string(int x, int y, char * string);
int text_put_substring(int x, int y, char * s, int length);
void text_put_numeric(int x, int y, int length, int format, int number);
void text_store_numeric(char * buffer, int length, int format, int number);
void text_fill_char(int x, int y, int length, int c);
void text_set_palette(int palette_num);
int text_get_palette(void);
void text_set_ank_font(int base, int color, int count, void * font);
void text_set_sjis_font(void * p);
void text_get_fontdata(int c, void * buffer);
void text_set_screen(int screen);
int text_get_screen(void);
void cursor_display(int flag);
int cursor_status(void);
void cursor_set_location(int x, int y, int w, int h);
unsigned long int cursor_get_location(void);
void cursor_set_type(int palette_num, int interval);
unsigned long int cursor_get_type(void);
int text_printf(int x, int y, const char *format, ...);

#endif
