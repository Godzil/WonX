#ifndef _WWSprite_h_INCLUDED_
#define _WWSprite_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdlib.h>

#include "WWPalette.h"
#include "WWCharacter.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWSprite * WWSprite;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWSprite_GetNumber(WWSprite s);
int WWSprite_GetHorizontal(WWSprite s);
int WWSprite_GetVertical(WWSprite s);
int WWSprite_GetPriority(WWSprite s);
int WWSprite_GetClipping(WWSprite s);
WWPalette WWSprite_GetPalette(WWSprite s);
WWCharacter WWSprite_GetCharacter(WWSprite s);

int WWSprite_SetNumber(WWSprite s, int n);
int WWSprite_SetHorizontal(WWSprite s, int f);
int WWSprite_SetVertical(WWSprite s, int f);
int WWSprite_SetPriority(WWSprite s, int f);
int WWSprite_SetClipping(WWSprite s, int f);
WWPalette WWSprite_SetPalette(WWSprite s, WWPalette p);
WWCharacter WWSprite_SetCharacter(WWSprite s, WWCharacter c);

int WWSprite_GetX(WWSprite sprite);
int WWSprite_GetY(WWSprite sprite);
int WWSprite_SetPosition(WWSprite sprite, int x, int y);

WWSprite WWSprite_Create(int number, int x, int y,
			 int horizontal, int vertical,
			 int priority, int clipping,
			 WWPalette palette, WWCharacter character);
WWSprite WWSprite_Destroy(WWSprite sprite);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/