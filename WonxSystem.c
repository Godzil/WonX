/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonxSystemP.h"
#include "configure.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWInterrupt WonxSystem_GetWWInterrupt(WonxSystem wonx_system)
{ return (wonx_system->ww_interrupt); }
WWInterrupt WonxSystem_SetWWInterrupt(WonxSystem wonx_system,
				      WWInterrupt ww_interrupt)
{ return (wonx_system->ww_interrupt = ww_interrupt); }

WWTimer WonxSystem_GetWWTimer(WonxSystem wonx_system, int type)
{ return (wonx_system->ww_timer[type]); }
WWTimer WonxSystem_SetWWTimer(WonxSystem wonx_system, int type, WWTimer t)
{ return (wonx_system->ww_timer[type] = t); }

WWTimer WonxSystem_GetWWVBlankTimer(WonxSystem wonx_system)
{ return (WonxSystem_GetWWTimer(wonx_system, 0)); }
WWTimer WonxSystem_SetWWVBlankTimer(WonxSystem wonx_system, WWTimer t)
{ return (WonxSystem_SetWWTimer(wonx_system, 0, t)); }

WWTimer WonxSystem_GetWWVBlankCountUpTimer(WonxSystem wonx_system)
{ return (WonxSystem_GetWWTimer(wonx_system, 1)); }
WWTimer WonxSystem_SetWWVBlankCountUpTimer(WonxSystem wonx_system, WWTimer t)
{ return (WonxSystem_SetWWTimer(wonx_system, 1, t)); }

WWTimer WonxSystem_GetWWHBlankCountUpTimer(WonxSystem wonx_system)
{ return (WonxSystem_GetWWTimer(wonx_system, 2)); }
WWTimer WonxSystem_SetWWHBlankCountUpTimer(WonxSystem wonx_system, WWTimer t)
{ return (WonxSystem_SetWWTimer(wonx_system, 2, t)); }

UNIXTimer WonxSystem_GetUNIXTimer(WonxSystem wonx_system)
{ return (wonx_system->unix_timer); }
UNIXTimer WonxSystem_SetUNIXTimer(WonxSystem wonx_system,
				  UNIXTimer unix_timer)
{ return (wonx_system->unix_timer = unix_timer); }

static int WonxTimer_Callback(WonxSystem wonx_system)
{
  WWTimer ww_timer;
  WWInterrupt ww_interrupt;

  ww_interrupt = WonxSystem_GetWWInterrupt(wonx_system);

  ww_timer = WonxSystem_GetWWVBlankTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteVBlankCallback(ww_interrupt);
  }

  ww_timer = WonxSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteTimerCountUpCallback(ww_interrupt);
  }

  ww_timer = WonxSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteHBlankCountUpCallback(ww_interrupt);
  }

  return (0);
}

WonxSystem WonxSystem_Create()
{
  WonxSystem wonx_system;
  WWInterrupt ww_interrupt;
  WWTimer ww_timer;
  UNIXTimer unix_timer;

  wonx_system = (WonxSystem)malloc(sizeof(_WonxSystem));
  if (wonx_system == NULL)
    Error("WonxSystem_Create", "Cannot allocate memory.");

  ww_interrupt = WWInterrupt_Create();
  if (ww_interrupt == NULL)
    Error("WonxSystem_Create", "Cannot create WonderWitch interrupt.");
  WonxSystem_SetWWInterrupt(wonx_system, ww_interrupt);

  /* VBlank は WONX_VBLANK_INTERVAL * 0.1 秒毎とする */
  ww_timer = WWTimer_Create(1, WONX_VBLANK_INTERVAL);
  if (ww_timer == NULL)
    Error("WonxSystem_Create", "Cannot create WonderWitch VBlank timer.");
  WonxSystem_SetWWVBlankTimer(wonx_system, ww_timer);

  ww_timer = WWTimer_Create(0, WONX_VBLANK_INTERVAL);
  if (ww_timer == NULL)
    Error("WonxSystem_Create",
	  "Cannot create WonderWitch VBlank count up timer.");
  WonxSystem_SetWWVBlankCountUpTimer(wonx_system, ww_timer);

  ww_timer = WWTimer_Create(0, WONX_HBLANK_INTERVAL);
  if (ww_timer == NULL)
    Error("WonxSystem_Create",
	  "Cannot create WonderWitch HBlank count up timer.");
  WonxSystem_SetWWHBlankCountUpTimer(wonx_system, ww_timer);

  WWTimer_Reset(WonxSystem_GetWWVBlankTimer(       wonx_system));
  WWTimer_Reset(WonxSystem_GetWWVBlankCountUpTimer(wonx_system));
  WWTimer_Reset(WonxSystem_GetWWHBlankCountUpTimer(wonx_system));

  WWTimer_ON( WonxSystem_GetWWVBlankTimer(       wonx_system));
  WWTimer_OFF(WonxSystem_GetWWVBlankCountUpTimer(wonx_system));
  WWTimer_OFF(WonxSystem_GetWWHBlankCountUpTimer(wonx_system));

  /* タイマのインターバルは，0.1 秒単位とする */
  unix_timer = UNIXTimer_Create(1, WONX_TIMER_INTERVAL, wonx_system, 
				(UNIXTimerCallBack)WonxTimer_Callback);
  if (unix_timer == NULL)
    Error("WonxSystem_Create", "Cannot create UNIX timer.");
  WonxSystem_SetUNIXTimer(wonx_system, unix_timer);

  UNIXTimer_ON(unix_timer);

  return (wonx_system);
}

WonxSystem WonxSystem_Destroy(WonxSystem wonx_system)
{
  WWInterrupt wi;
  WWTimer wt;
  UNIXTimer unix_timer;

  if (wonx_system == NULL)
    Error("WonxSystem_Destroy", "Object is not created.");

  unix_timer = WonxSystem_GetUNIXTimer(wonx_system);

  if (unix_timer)
    UNIXTimer_OFF(unix_timer);

  wt = WonxSystem_GetWWVBlankTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);
  wt = WonxSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);
  wt = WonxSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);

  if (unix_timer)
    WonxSystem_SetUNIXTimer(wonx_system, UNIXTimer_Destroy(unix_timer));

  wt = WonxSystem_GetWWVBlankTimer(wonx_system);
  if (wt) WonxSystem_SetWWVBlankTimer(wonx_system, WWTimer_Destroy(wt));
  wt = WonxSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (wt) WonxSystem_SetWWVBlankCountUpTimer(wonx_system, WWTimer_Destroy(wt));
  wt = WonxSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (wt) WonxSystem_SetWWHBlankCountUpTimer(wonx_system, WWTimer_Destroy(wt));

  wi = WonxSystem_GetWWInterrupt(wonx_system);
  if (wi) WonxSystem_SetWWInterrupt(wonx_system, WWInterrupt_Destroy(wi));

  free(wonx_system);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
