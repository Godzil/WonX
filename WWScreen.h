#ifndef _WWScreen_h_INCLUDED_
#define _WWScreen_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdlib.h>

#include "WWPalette.h"
#include "WWCharacter.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WWScreen * WWScreen;

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define WW_SCREEN_DRAW_ALL     0
#define WW_SCREEN_INSIDE_ONLY  1
#define WW_SCREEN_OUTSIDE_ONLY 2

/*****************************************************************************/
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

int WWScreen_GetHorizontal(WWScreen s, int x, int y);
int WWScreen_GetVertical(WWScreen s, int x, int y);
WWPalette WWScreen_GetPalette(WWScreen s, int x, int y);
WWCharacter WWScreen_GetCharacter(WWScreen s, int x, int y);

int WWScreen_SetHorizontal(WWScreen s, int x, int y, int f);
int WWScreen_SetVertical(WWScreen s, int x, int y, int f);
WWPalette WWScreen_SetPalette(WWScreen s, int x, int y, WWPalette palette);
WWCharacter WWScreen_SetCharacter(WWScreen s, int x, int y, WWCharacter c);

int WWScreen_GetNumber(WWScreen s);
int WWScreen_GetWidth( WWScreen s);
int WWScreen_GetHeight(WWScreen s);
int WWScreen_GetRollX( WWScreen s);
int WWScreen_GetRollY( WWScreen s);

int WWScreen_GetEnable(WWScreen s);
int WWScreen_GetMode(  WWScreen s);

int WWScreen_GetDrawX(     WWScreen s);
int WWScreen_GetDrawY(     WWScreen s);
int WWScreen_GetDrawWidth( WWScreen s);
int WWScreen_GetDrawHeight(WWScreen s);

int WWScreen_SetNumber(WWScreen s, int n);
int WWScreen_SetWidth( WWScreen s, int n);
int WWScreen_SetHeight(WWScreen s, int n);
int WWScreen_SetRollX( WWScreen s, int r);
int WWScreen_SetRollY( WWScreen s, int r);

int WWScreen_SetEnable(WWScreen s, int n);
int WWScreen_SetMode(  WWScreen s, int n);

int WWScreen_SetDrawX(     WWScreen s, int n);
int WWScreen_SetDrawY(     WWScreen s, int n);
int WWScreen_SetDrawWidth( WWScreen s, int n);
int WWScreen_SetDrawHeight(WWScreen s, int n);

int WWScreen_GetPixel(WWScreen screen, int x, int y);

WWScreen WWScreen_Create(int number,
			 int width, int height,
			 WWPalette initial_palette,
			 WWCharacter initial_character,
			 int draw_x, int draw_y,
			 int draw_width, int draw_height);
WWScreen WWScreen_Destroy(WWScreen screen);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
