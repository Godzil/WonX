#ifndef _WWText_h_INCLUDED_
#define _WWText_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWDisplay.h"
#include "WWScreen.h"
#include "WWPalette.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWText * WWText;

/*===========================================================================*/
/* ���Фμ���                                                              */
/*===========================================================================*/

WWScreen WWText_GetScreen(WWText t);
int WWText_GetX(WWText t);
int WWText_GetY(WWText t);
int WWText_GetWidth( WWText t);
int WWText_GetHeight(WWText t);
int WWText_GetBase(WWText t);
WWPalette WWText_GetPalette(WWText t);

/*===========================================================================*/
/* ���Ф�����                                                              */
/*===========================================================================*/

WWScreen WWText_SetScreen(WWText t, WWScreen s);
int WWText_SetX(WWText t, int n);
int WWText_SetY(WWText t, int n);
int WWText_SetWidth( WWText t, int n);
int WWText_SetHeight(WWText t, int n);
int WWText_SetBase(WWText t, int n);
WWPalette WWText_SetPalette(WWText t, WWPalette p);

int WWText_SetTextWindow(WWText ww_text, int x, int y,
                         int width, int height, int base,
                         WWDisplay ww_display);
int WWText_PutCharacter(WWText ww_text, int x, int y, int character,
                        WWDisplay ww_display);

/*===========================================================================*/
/* ���֥������Ȥ������Ⱦõ�                                                  */
/*===========================================================================*/

WWText WWText_Create(WWScreen screen, int x, int y, int width, int height,
		     WWPalette palette);
WWText WWText_Destroy(WWText text);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/








/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/