#ifndef _WONX_SYS_DISP_H_
#define _WONX_SYS_DISP_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define SCREEN1 0
#define SCREEN2 1

#define LCD_PIXEL_WIDTH     224
#define LCD_PIXEL_HEIGHT    144
#define SCREEN_PIXEL_WIDTH  256
#define SCREEN_PIXEL_HEIGHT 256
#define SCREEN_CHAR_WIDTH    32
#define SCREEN_CHAR_HEIGHT   32

#define DCM_SCR1             (1 << 0)
#define DCM_SCR2             (1 << 1)
#define DCM_SPR              (1 << 2)
#define DCM_SPR_WIN          (1 << 3)
#define DCM_SCR2_WIN_INSIDE  (1 << 5)
#define DCM_SCR2_WIN_OUTSIDE ((1 << 4) | (1 << 5))
#define DCM_BORDER_COLOR     ((1 << 8) | (1 << 9) | (1 << 10))

/* SPRITE_SET_CHAR, SCREEN_SET_CHAR で使用 */
#define CFM_FLIP_V (1 << 15)
#define CFM_FLIP_H (1 << 14)
#define CFM_FONT   0x01FF /* 0〜8ビット目 */

/* SPRITE_SET_CHAR で使用 */
#define CFM_SPR_UPPER   (1 << 13)
#define CFM_SPRWIN_CLIP (1 << 12)
#define CFM_SPR_PALETTE ((1 << 9) | (1 << 10) | (1 << 11))

/* SCREEN_SET_CHAR で使用 */
#define CFM_SCR_PALETTE ((1 << 9) | (1 << 10) | (1 << 11) | (1 << 12))

#define CFSFT_PALETTE 9

/* LCD_SET_SEGMENTS で使用 */
#define LCDSEG_AUX3       (1 << 5) /* 予備マーク３ */
#define LCDSEG_AUX2       (1 << 4) /* 予備マーク２ */
#define LCDSEG_AUX1       (1 << 3) /* 予備マーク１ */
#define LCDSEG_HORIZONTAL (1 << 2) /* 縦モードマーク */
#define LCDSEG_VERTICAL   (1 << 1) /* 横モードマーク */
#define LCDSEG_SLEEP      (1 << 0) /* 省電力マーク */

/* LCD_SET_SLEEP で使用 */
#define LCD_SLEEP_ON  0
#define LCD_SLEEP_OFF 1

#define lcd_on()  lcd_set_sleep(LCD_SLEEP_OFF)
#define lcd_off() lcd_set_sleep(LCD_SLEEP_ON)

/* 未実装 */
void lcd_set_interrupt_line(unsigned char line);
unsigned char lcd_get_display_line();

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

void display_control(unsigned int flags);
unsigned int display_status(void);
void font_set_monodata(unsigned int number, unsigned int count,
		       unsigned char * data);
void font_set_colordata(unsigned int number, unsigned int count,
			unsigned char * data);
void font_get_data(unsigned int number, unsigned int count,
		   unsigned char * data);
void font_set_color(unsigned int colors);
unsigned int font_get_color(void);
void screen_set_char(int screen, int x, int y, int w, int h,
		     unsigned short int * data);
void screen_get_char(int screen, int x, int y, int w, int h,
		     unsigned short int * data);
unsigned int screen_get_char1(int screen, int x, int y);
void screen_fill_char(int screen, int x, int y, int w, int h,
		      unsigned int data);
void screen_fill_attr(int screen, int x, int y, int w, int h,
		      unsigned int data, unsigned int mask);
void sprite_set_range(unsigned int start, unsigned int number);
void sprite_set_char(unsigned int sprite_num, unsigned int data);
unsigned int sprite_get_char(unsigned int sprite_num);
void sprite_set_location(unsigned int sprite_num, int x, int y);
unsigned int sprite_get_location(unsigned int sprite_num);
void sprite_set_char_location(unsigned int sprite_num,
			      unsigned int data, int x, int y);
unsigned long int sprite_get_char_location(unsigned int sprite_num);
void sprite_set_data(unsigned int sprite_num, unsigned int count,
		     unsigned long int * data);
void screen_set_scroll(int screen, int x, int y);
unsigned int screen_get_scroll(int screen);
void screen2_set_window(int x, int y, int w, int h);
unsigned long int screen2_get_window(void);
void sprite_set_window(int x, int y, int w, int h);
unsigned long int sprite_get_window(void);
void palette_set_color(unsigned int palette_num, unsigned int colors);
unsigned int palette_get_color(unsigned int palette_num);
void lcd_set_color(unsigned int colors0, unsigned int colors1);
unsigned long int lcd_get_color(void);
void lcd_set_segments(unsigned int segments);
unsigned int lcd_get_segments(void);
void lcd_set_sleep(unsigned int slp);
unsigned int lcd_get_sleep(void);
void screen_set_vram(int screen, int location_id);
void sprite_set_vram(int location_id);

#endif
