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
/* メンバ関数の宣言                                                          */
/*****************************************************************************/

int WWScreen_GetNumber(WWScreen s);
int WWScreen_GetHorizontal(WWScreen s, int x, int y);
int WWScreen_GetVertical(WWScreen s, int x, int y);
WWPalette WWScreen_GetPalette(WWScreen s, int x, int y);
WWCharacter WWScreen_GetCharacter(WWScreen s, int x, int y);

int WWScreen_SetNumber(WWScreen s, int n);
int WWScreen_SetHorizontal(WWScreen s, int x, int y, int f);
int WWScreen_SetVertical(WWScreen s, int x, int y, int f);
WWPalette WWScreen_SetPalette(WWScreen s, int x, int y, WWPalette palette);
WWCharacter WWScreen_SetCharacter(WWScreen s, int x, int y, WWCharacter c);

int WWScreen_GetWidth( WWScreen s);
int WWScreen_GetHeight(WWScreen s);
int WWScreen_GetRollX( WWScreen s);
int WWScreen_GetRollY( WWScreen s);

int WWScreen_SetWidth( WWScreen s, int n);
int WWScreen_SetHeight(WWScreen s, int n);
int WWScreen_SetRollX( WWScreen s, int r);
int WWScreen_SetRollY( WWScreen s, int r);

int WWScreen_GetPixel(WWScreen screen, int x, int y);

WWScreen WWScreen_Create(int number, int width, int height,
			 WWPalette initial_palette,
			 WWCharacter initial_character);
WWScreen WWScreen_Destroy(WWScreen screen);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
