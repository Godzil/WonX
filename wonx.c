#include "wonx.h"

/*****************************************************************************/
/* ディスプレイの確保                                                        */
/*****************************************************************************/

WonxDisplay wonx_display = NULL;

void Wonx_Create(void)
{
  wonx_display =
    WonxDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);
  return;
}
