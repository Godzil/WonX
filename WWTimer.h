#ifndef _WWTimer_h_INCLUDED_
#define _WWTimer_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWTimer * WWTimer;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/timer.h"

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

int WWTimer_ON(WWTimer ww_timer);
int WWTimer_OFF(WWTimer ww_timer);
int WWTimer_IsON(WWTimer ww_timer);
int WWTimer_IsOFF(WWTimer ww_timer);

int WWTimer_GetAutoPreset(WWTimer ww_timer);
int WWTimer_GetPresetCounter(WWTimer ww_timer);
int WWTimer_GetCounter(WWTimer ww_timer);

int WWTimer_IsAutoPresetOFF(WWTimer ww_timer);
int WWTimer_IsAutoPresetON(WWTimer ww_timer);

int WWTimer_SetAutoPreset(WWTimer ww_timer, int auto_preset);
int WWTimer_SetPresetCounter(WWTimer ww_timer, int preset_counter);
int WWTimer_SetCounter(WWTimer ww_timer, int counter);

int WWTimer_SetAutoPresetOFF(WWTimer ww_timer);
int WWTimer_SetAutoPresetON(WWTimer ww_timer);

int WWTimer_Reset(WWTimer ww_timer);
int WWTimer_Count(WWTimer ww_timer);

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

WWTimer WWTimer_Create(int auto_preset, int preset);

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

WWTimer WWTimer_Destroy(WWTimer ww_timer);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
