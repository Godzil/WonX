#ifndef _XDisplay_h_INCLUDED_
#define _XDisplay_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _XDisplay * XDisplay;

/*****************************************************************************/
/* ヘッダファイルのインクルード                                              */
/*****************************************************************************/

#include <X11/Xlib.h>

#include "wonx/key.h"

#include "WWDisplay.h"
#include "WWLCDPanel.h"
#include "XColorGC.h"

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

Display * XDisplay_GetDisplay(XDisplay x_display);
Colormap XDisplay_GetColormap(XDisplay x_display);

XColorGCDatabase XDisplay_GetColorGCDatabase(XDisplay x_display);

unsigned int XDisplay_GetKeyPress(XDisplay x_display);

int XDisplay_GetLCDDrawLevel(XDisplay d);
int XDisplay_SetLCDDrawLevel(XDisplay d, int level);
int XDisplay_LCDDrawLevelDown(XDisplay d);
int XDisplay_LCDDrawLevelUp(  XDisplay d);

int XDisplay_GetColorMapPrint(XDisplay d);
int XDisplay_GetPalettePrint(XDisplay d);
int XDisplay_GetCharacterPrint(XDisplay d);
int XDisplay_GetSpritePrint(XDisplay d);

int XDisplay_SetColorMapPrint(XDisplay d, int f);
int XDisplay_SetPalettePrint(XDisplay d, int f);
int XDisplay_SetCharacterPrint(XDisplay d, int f);
int XDisplay_SetSpritePrint(XDisplay d, int f);

/*===========================================================================*/
/* オブジェクトの生成と消去                                                  */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの生成                                                        */
/*---------------------------------------------------------------------------*/

XDisplay XDisplay_Create(int width, int height);

/*---------------------------------------------------------------------------*/
/* オブジェクトの消去                                                        */
/*---------------------------------------------------------------------------*/

XDisplay XDisplay_Destroy(XDisplay x_display);

/*---------------------------------------------------------------------------*/
/* Xサーバとの同期                                                           */
/*---------------------------------------------------------------------------*/

int XDisplay_Sync(XDisplay x_display);
int XDisplay_Flush(XDisplay x_display);

/*---------------------------------------------------------------------------*/
/* 描画                                                                      */
/*---------------------------------------------------------------------------*/

int XDisplay_DrawLCDWindow(XDisplay x_display, WWDisplay ww_display,
			   WWLCDPanel ww_lcd_panel);

/*---------------------------------------------------------------------------*/
/* GC の作成                                                                 */
/*---------------------------------------------------------------------------*/

GC XDisplay_CreateGC(XDisplay x_display);

/*---------------------------------------------------------------------------*/
/* GC の解放                                                                 */
/*---------------------------------------------------------------------------*/

int XDisplay_DestroyGC(XDisplay x_display, GC gc);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
