#ifndef _WONX_SYS_LIBWWC_H_
#define _WONX_SYS_LIBWWC_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define COLOR_MODE_GRAYSCALE 0x00
#define COLOR_MODE_4COLOR    0x80
#define COLOR_MODE_16COLOR   0xC0
#define COLOR_MODE_16PACKED  0xE0

#define HARDARCH_WS  0
#define HARDARCH_WSC 1

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

unsigned int wwc_set_color_mode(unsigned int mode);
unsigned int wwc_get_color_mode(void);
void wwc_palette_set_color(unsigned int palette_num, unsigned int color_num, unsigned int rgb);
unsigned int wwc_palette_get_color(unsigned int palette_num, unsigned int color_num);
void wwc_font_set_colordata(unsigned int number, unsigned int count,
			    unsigned long int * data);
void wwc_font_get_colordata(unsigned int number, unsigned int count,
			    unsigned long int * data);
unsigned int wwc_get_hardarch(void);
void wwc_clear_font(void);

#endif
