#include "WonxP.h"
#include "etc.h"

#include "sys/disp.h"
#include "sys/text.h"
#include "sys/system.h"

/*****************************************************************************/
/* ディスプレイの確保                                                        */
/*****************************************************************************/

static Wonx wonx = NULL;

int Wonx_IsCreated(void)
{
  return (wonx != NULL);
}

void Wonx_Create(void)
{
  WWScreen screen;
  WWPalette palette;

  wonx = (Wonx)malloc(sizeof(_Wonx));
  if (wonx == NULL) Error("Wonx_Create", "Cannot allocate memory.");

  wonx->wonx_display =
    WonxDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);
  screen =
    WWDisplay_GetScreen(WonxDisplay_GetWWDisplay(wonx->wonx_display), SCREEN2);
  /* デフォルトのテキスト表示用パレットは0 */
  palette =
    WWDisplay_GetPalette(WonxDisplay_GetWWDisplay(wonx->wonx_display), 0);

  wonx->wonx_text =
    WonxText_Create(screen, 0, 0, TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT,
		    palette);

  wonx->wonx_system = WonxSystem_Create();

  return;
}

WonxDisplay Wonx_GetWonxDisplay(void)
{
  return (wonx->wonx_display);
}

WonxText Wonx_GetWonxText(void)
{
  return (wonx->wonx_text);
}

WonxSystem Wonx_GetWonxSystem(void)
{
  return (wonx->wonx_system);
}

