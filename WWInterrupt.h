#ifndef _WWInterrupt_h_INCLUDED_
#define _WWInterrupt_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWInterrupt * WWInterrupt;
typedef void (*WWInterruptCallback)();

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx/system.h"

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* WWInterrupt クラスのもの                                                  */
/*===========================================================================*/

int WWInterrupt_GetNumber(WWInterrupt interrupt, int num);
WWInterruptCallback WWInterrupt_GetCallback(WWInterrupt interrupt, int n);
int WWInterrupt_GetCS(WWInterrupt interrupt, int number);
int WWInterrupt_GetDS(WWInterrupt interrupt, int number);
WWInterruptCallback WWInterrupt_SetCallback(WWInterrupt interrupt, int num,
					    WWInterruptCallback callback);
int WWInterrupt_SetCS(WWInterrupt interrupt, int num, int cs);
int WWInterrupt_SetDS(WWInterrupt interrupt, int num, int ds);
int WWInterrupt_ExecuteCallback(WWInterrupt i, int n);

/*---------------------------------------------------------------------------*/
/* Number の取得                                                             */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyNumber(WWInterrupt interrupt);
int WWInterrupt_GetKeyNumber(WWInterrupt interrupt);
int WWInterrupt_GetCasetteNumber(WWInterrupt interrupt);
int WWInterrupt_GetReceiveReadyNumber(WWInterrupt interrupt);
int WWInterrupt_GetDisplineNumber(WWInterrupt interrupt);
int WWInterrupt_GetTimerCountUpNumber(WWInterrupt interrupt);
int WWInterrupt_GetVBlankNumber(WWInterrupt interrupt);
int WWInterrupt_GetHBlankCountUpNumber(WWInterrupt interrupt);

/*---------------------------------------------------------------------------*/
/* コールバック関数の取得                                                    */
/*---------------------------------------------------------------------------*/

WWInterruptCallback WWInterrupt_GetSendReadyCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetKeyCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetCasetteCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetReceiveReadyCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetDisplineCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetTimerCountUpCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetVBlankCallback(WWInterrupt interrupt);
WWInterruptCallback WWInterrupt_GetHBlankCountUpCallback(WWInterrupt interrupt);

/*---------------------------------------------------------------------------*/
/* CS の取得                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyCS(WWInterrupt interrupt);
int WWInterrupt_GetKeyCS(WWInterrupt interrupt);
int WWInterrupt_GetCasetteCS(WWInterrupt interrupt);
int WWInterrupt_GetReceiveReadyCS(WWInterrupt interrupt);
int WWInterrupt_GetDisplineCS(WWInterrupt interrupt);
int WWInterrupt_GetTimerCountUpCS(WWInterrupt interrupt);
int WWInterrupt_GetVBlankCS(WWInterrupt interrupt);
int WWInterrupt_GetHBlankCountUpCS(WWInterrupt interrupt);

/*---------------------------------------------------------------------------*/
/* DS の取得                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_GetSendReadyDS(WWInterrupt interrupt);
int WWInterrupt_GetKeyDS(WWInterrupt interrupt);
int WWInterrupt_GetCasetteDS(WWInterrupt interrupt);
int WWInterrupt_GetReceiveReadyDS(WWInterrupt interrupt);
int WWInterrupt_GetDisplineDS(WWInterrupt interrupt);
int WWInterrupt_GetTimerCountUpDS(WWInterrupt interrupt);
int WWInterrupt_GetVBlankDS(WWInterrupt interrupt);
int WWInterrupt_GetHBlankCountUpDS(WWInterrupt interrupt);

/*---------------------------------------------------------------------------*/
/* コールバック関数の設定                                                    */
/*---------------------------------------------------------------------------*/

WWInterruptCallback WWInterrupt_SetSendReadyCallback(WWInterrupt interrupt,
						     WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetKeyCallback(WWInterrupt interrupt,
					       WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetCasetteCallback(WWInterrupt interrupt,
						   WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetReceiveReadyCallback(WWInterrupt interrupt,
							WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetDisplineCallback(WWInterrupt interrupt,
						    WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetTimerCountUpCallback(WWInterrupt interrupt,
							WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetVBlankCallback(WWInterrupt interrupt,
						  WWInterruptCallback f);
WWInterruptCallback WWInterrupt_SetHBlankCountUpCallback(WWInterrupt interrupt,
							 WWInterruptCallback f);

/*---------------------------------------------------------------------------*/
/* CS の設定                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_SetSendReadyCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetKeyCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetCasetteCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetReceiveReadyCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetDisplineCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetTimerCountUpCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetVBlankCS(WWInterrupt interrupt, int cs);
int WWInterrupt_SetHBlankCountUpCS(WWInterrupt interrupt, int cs);

/*---------------------------------------------------------------------------*/
/* DS の設定                                                                 */
/*---------------------------------------------------------------------------*/

int WWInterrupt_SetSendReadyDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetKeyDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetCasetteDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetReceiveReadyDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetDisplineDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetTimerCountUpDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetVBlankDS(WWInterrupt interrupt, int ds);
int WWInterrupt_SetHBlankCountUpDS(WWInterrupt interrupt, int ds);

/*---------------------------------------------------------------------------*/
/* コールバック関数の実行                                                    */
/*---------------------------------------------------------------------------*/

int WWInterrupt_ExecuteSendReadyCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteKeyCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteCasetteCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteReceiveReadyCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteDisplineCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteTimerCountUpCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteVBlankCallback(WWInterrupt interrupt);
int WWInterrupt_ExecuteHBlankCountUpCallback(WWInterrupt interrupt);

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

WWInterrupt WWInterrupt_Create();

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

WWInterrupt WWInterrupt_Destroy(WWInterrupt interrupt);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
