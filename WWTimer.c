/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWTimerP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWTimer_ON(   WWTimer ww_timer) { return (ww_timer->timer_on =  1); }
int WWTimer_OFF(  WWTimer ww_timer) { return (ww_timer->timer_on =  0); }
int WWTimer_IsON( WWTimer ww_timer) { return (ww_timer->timer_on != 0); }
int WWTimer_IsOFF(WWTimer ww_timer) { return (ww_timer->timer_on == 0); }

int WWTimer_GetAutoPreset(WWTimer ww_timer)
{ return (ww_timer->auto_preset); }
int WWTimer_GetPresetCounter(WWTimer ww_timer)
{ return (ww_timer->preset_counter); }
int WWTimer_GetCounter(WWTimer ww_timer)
{ return (ww_timer->counter); }

int WWTimer_IsAutoPresetOFF(WWTimer ww_timer)
{ return (WWTimer_GetAutoPreset(ww_timer) == 0); }
int WWTimer_IsAutoPresetON(WWTimer ww_timer)
{ return (WWTimer_GetAutoPreset(ww_timer) == 1); }

int WWTimer_SetAutoPreset(WWTimer ww_timer, int auto_preset)
{ return (ww_timer->auto_preset = auto_preset); }
int WWTimer_SetPresetCounter(WWTimer ww_timer, int preset_counter)
{ return (ww_timer->preset_counter = preset_counter); }
int WWTimer_SetCounter(WWTimer ww_timer, int counter)
{ return (ww_timer->counter = counter); }

int WWTimer_SetAutoPresetOFF(WWTimer ww_timer)
{ return (WWTimer_SetAutoPreset(ww_timer, 0)); }
int WWTimer_SetAutoPresetON(WWTimer ww_timer)
{ return (WWTimer_SetAutoPreset(ww_timer, 1)); }

int WWTimer_Reset(WWTimer ww_timer)
{
  int counter;
  counter = WWTimer_GetCounter(ww_timer);
  WWTimer_SetCounter(ww_timer, WWTimer_GetPresetCounter(ww_timer));
  return (counter);
}

int WWTimer_Count(WWTimer ww_timer)
{
  int ret;
  int counter;

  if (WWTimer_IsOFF(ww_timer)) return (0);

  counter = WWTimer_GetCounter(ww_timer);

  counter--;

  if (counter <= 0) {
    ret = 1;
    if (WWTimer_IsAutoPresetON(ww_timer))
      WWTimer_Reset(ww_timer);
    else
      WWTimer_OFF(ww_timer);
  } else {
    ret = 0;
    WWTimer_SetCounter(ww_timer, counter);
  }

  return (ret);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

WWTimer WWTimer_Create(int auto_preset, int preset)
{
  WWTimer ww_timer;

  ww_timer = (WWTimer)malloc(sizeof(_WWTimer));
  if (ww_timer == NULL)
    WonX_Error("WWTimer_Create", "Cannot allocate memory.");

  WWTimer_OFF(ww_timer);
  WWTimer_SetAutoPreset(ww_timer, auto_preset);
  WWTimer_SetPresetCounter(ww_timer, preset);
  WWTimer_Reset(ww_timer);

  return (ww_timer);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

WWTimer WWTimer_Destroy(WWTimer ww_timer)
{
  if (ww_timer == NULL)
    WonX_Error("WWTimer_Destroy", "Object is not created.");

  WWTimer_OFF(ww_timer);

  free(ww_timer);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
