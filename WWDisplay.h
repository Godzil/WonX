#ifndef _WWDisplay_h_INCLUDED_
#define _WWDisplay_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWColorMap.h"
#include "WWPalette.h"
#include "WWCharacter.h"
#include "WWSprite.h"
#include "WWScreen.h"
#include "WWLCDPanel.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWDisplay * WWDisplay;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* ���Фμ���                                                              */
/*===========================================================================*/

WWColorMap WWDisplay_GetColorMap(WWDisplay d);
WWPalette WWDisplay_GetPalette(WWDisplay d, int n);
WWCharacter WWDisplay_GetCharacter(WWDisplay d, int n);
WWSprite WWDisplay_GetSprite(WWDisplay d, int n);
WWScreen WWDisplay_GetScreen(WWDisplay d, int n);
WWLCDPanel WWDisplay_GetLCDPanel(WWDisplay d);
int WWDisplay_GetScreenEnable(WWDisplay d, int n);
int WWDisplay_GetSpriteEnable(WWDisplay d);
int WWDisplay_GetSpriteWindowEnable(WWDisplay d);

int WWDisplay_GetScreen2WindowMode(WWDisplay d);
int WWDisplay_GetBorder(WWDisplay d);

int WWDisplay_GetForegroundColor(WWDisplay d);
int WWDisplay_GetBackgroundColor(WWDisplay d);

int WWDisplay_GetSpriteStart(WWDisplay d);
int WWDisplay_GetSpriteCount(WWDisplay d);

/*===========================================================================*/
/* ���Ф�����                                                              */
/*===========================================================================*/

WWColorMap WWDisplay_SetColorMap(WWDisplay d, WWColorMap cm);
WWPalette WWDisplay_SetPalette(WWDisplay d, int n, WWPalette p);
WWCharacter WWDisplay_SetCharacter(WWDisplay d, int n, WWCharacter c);
WWSprite WWDisplay_SetSprite(WWDisplay d, int n, WWSprite s);
WWScreen WWDisplay_SetScreen(WWDisplay d, int n, WWScreen s);
WWLCDPanel WWDisplay_SetLCDPanel(WWDisplay d, WWLCDPanel p);

int WWDisplay_SetScreenEnable(WWDisplay d, int n, int f);
int WWDisplay_SetSpriteEnable(WWDisplay d, int f);
int WWDisplay_SetSpriteWindowEnable(WWDisplay d, int f);

int WWDisplay_SetScreen2WindowMode(WWDisplay d, int mode);
int WWDisplay_SetBorder(WWDisplay d, int b);

int WWDisplay_SetForegroundColor(WWDisplay d, int c);
int WWDisplay_SetBackgroundColor(WWDisplay d, int c);

int WWDisplay_SetSpriteStart(WWDisplay d, int n);
int WWDisplay_SetSpriteCount(WWDisplay d, int n);

/*===========================================================================*/
/* ���֥������Ȥ������Ⱦõ�                                                  */
/*===========================================================================*/

WWDisplay WWDisplay_Create(int lcd_panel_width, int lcd_panel_height,
			   int screen_width, int screen_height);
WWDisplay WWDisplay_Destroy(WWDisplay display);

/*===========================================================================*/
/* LCD�ѥͥ������                                                           */
/*===========================================================================*/

int WWDisplay_DrawLCDPanel(WWDisplay display);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/