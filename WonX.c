#include "WonXP.h"
#include "etc.h"

#include "wonx_include/disp.h"
#include "wonx_include/text.h"
#include "wonx_include/system.h"
#include "wonx_include/comm.h"

/*****************************************************************************/
/* ディスプレイの確保                                                        */
/*****************************************************************************/

static WonX wonx = NULL;

int WonX_IsCreated(void)
{
  return (wonx != NULL);
}

void WonX_Create(void)
{
  WWScreen screen;
  WWPalette palette;

  wonx = (WonX)malloc(sizeof(_WonX));
  if (wonx == NULL) WonX_Error("WonX_Create", "Cannot allocate memory.");

  wonx->wonx_display =
    WonXDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);
  screen =
    WWDisplay_GetScreen(WonXDisplay_GetWWDisplay(wonx->wonx_display), SCREEN2);
  /* デフォルトのテキスト表示用パレットは0 */
  palette =
    WWDisplay_GetPalette(WonXDisplay_GetWWDisplay(wonx->wonx_display), 0);

  wonx->wonx_text =
    WonXText_Create(screen, 0, 0, TEXT_SCREEN_WIDTH, TEXT_SCREEN_HEIGHT,
		    palette);

  wonx->wonx_system = WonXSystem_Create();

  wonx->wonx_serial_port = WonXSerialPort_Create();

  return;
}

WonXDisplay WonX_GetWonXDisplay(void)
{
  return (wonx->wonx_display);
}

WonXText WonX_GetWonXText(void)
{
  return (wonx->wonx_text);
}

WonXSystem WonX_GetWonXSystem(void)
{
  return (wonx->wonx_system);
}

WonXSerialPort WonX_GetWonXSerialPort(void)
{
  return (wonx->wonx_serial_port);
}

