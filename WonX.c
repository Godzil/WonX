#include "WonXP.h"
#include "etc.h"

#include "wonx/disp.h"
#include "wonx/system.h"
#include "wonx/comm.h"

static WonX wonx = NULL;

int WonX_IsCreated(void)
{
  return (wonx != NULL);
}

void WonX_Create(void)
{
  if (WonX_IsCreated())
    WonX_Error("WonX_Create", "WonX has been already created.");

  wonx = (WonX)malloc(sizeof(_WonX));
  if (wonx == NULL) WonX_Error("WonX_Create", "Cannot allocate memory.");

  /*
   * WonX のタイマからはディスプレイのリフレッシュなどの関数を呼び出すため，
   * WonXSystem_Create() でタイマをスタートさせる前に WonXDisplay_Create() で
   * WonXDisplay オブジェクトを作成しておく必要がある．このため
   * WonXDisplay_Create() を WonXSystem_Create() の後に持っていってはいけない．
   */
  wonx->wonx_display =
    WonXDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);

  /*
   * WonXDisplay と同様のことが WonXSerialPort でも将来的に起きる可能性が
   * あるかもしれないので， WonXSerialPort_Create() もいちおう
   * WonXSystem_Create() の前に置いておく．
   */
  wonx->wonx_serial_port = WonXSerialPort_Create();

  /*
   * WonXSystem_Create() ではタイマを作成するが，タイマからはいろいろな
   * オブジェクトが呼ばれる可能性があるため，タイマの作成は一番最後に行う
   * べきである．このため，WonXSystem_Create() は一番最後に行う．
   * (他のオブジェクトの作成中等にタイマがかかった場合，おかしなことに
   *  なってしまう)
   */
  wonx->wonx_system = WonXSystem_Create();

  return;
}

void WonX_Destroy(void)
{
  if (!WonX_IsCreated())
    WonX_Error("WonX_Destroy", "WonX has not been created yet.");

  /*
   * WonXSystem はタイマを持つが，タイマからはいろいろなオブジェクトが
   * 呼ばれる可能性があるため，一番最初にタイマを停止する必要がある．
   * このため，WonXSystem_Destroy() は一番最初に行う．
   * (他のオブジェクトの削除中等にタイマがかかった場合，おかしなことに
   *  なってしまう)
   */
  if (wonx->wonx_system)
    wonx->wonx_system = WonXSystem_Destroy(wonx->wonx_system);

  /*
   * WonXDisplay と同様のことが WonXSerialPort でも将来的に起きる可能性が
   * あるかもしれないので， WonXSerialPort_Destroy() もいちおう
   * WonXSystem_Destroy() の後に置いておく．
   */
  if (wonx->wonx_serial_port)
    wonx->wonx_serial_port = WonXSerialPort_Destroy(wonx->wonx_serial_port);

  /*
   * WonX のタイマからはディスプレイのリフレッシュなどの関数を呼び出すため，
   * WonXDisplay を消去する前に WonXSystem を消去して，タイマを停止する
   * 必要がある．(でないと WonXDisplay_Destroy() の実行中にタイマがかかった
   * ときに，おかしなことになる)
   * このため，WonXDisplay_Destroy() を WonXSystem_Destroy() の前に
   * 持っていってはいけない．
   */
  if (wonx->wonx_display)
    wonx->wonx_display = WonXDisplay_Destroy(wonx->wonx_display);

  free(wonx);
  wonx = NULL;

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
