#include "WonXP.h"
#include "etc.h"

#include "wonx_include/disp.h"
#include "wonx_include/system.h"
#include "wonx_include/comm.h"

static WonX wonx = NULL;

int WonX_IsCreated(void)
{
  return (wonx != NULL);
}

void WonX_Create(void)
{
  wonx = (WonX)malloc(sizeof(_WonX));
  if (wonx == NULL) WonX_Error("WonX_Create", "Cannot allocate memory.");

  wonx->wonx_display =
    WonXDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);

  wonx->wonx_system = WonXSystem_Create();

  wonx->wonx_serial_port = WonXSerialPort_Create();

  return;
}

WonXDisplay WonX_GetWonXDisplay(void)
{
  return (wonx->wonx_display);
}

WonXSystem WonX_GetWonXSystem(void)
{
  return (wonx->wonx_system);
}

WonXSerialPort WonX_GetWonXSerialPort(void)
{
  return (wonx->wonx_serial_port);
}

/*===========================================================================*/
/* エラー処理                                                                */
/*===========================================================================*/

int WonX_Error(char * funcname, char * message)
{
  fprintf(stderr, "error : %s(): %s\n", funcname, message);
  exit (1);
}

int WonX_Warning(char * funcname, char * message)
{
  fprintf(stderr, "warning : %s(): %s\n", funcname, message);
  return (0);
}

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
