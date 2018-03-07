#ifndef _WWCursor_h_INCLUDED_
#define _WWCursor_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWCursor * WWCursor;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "WWPalette.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWCursor_ON(   WWCursor p);
int WWCursor_OFF(  WWCursor p);
int WWCursor_IsON( WWCursor p);
int WWCursor_IsOFF(WWCursor p);

int WWCursor_GetX(       WWCursor p       );
int WWCursor_SetX(       WWCursor p, int n);
int WWCursor_GetY(       WWCursor p       );
int WWCursor_SetY(       WWCursor p, int n);
int WWCursor_GetWidth(   WWCursor p       );
int WWCursor_SetWidth(   WWCursor p, int n);
int WWCursor_GetHeight(  WWCursor p       );
int WWCursor_SetHeight(  WWCursor p, int n);
int WWCursor_GetInterval(WWCursor p       );
int WWCursor_SetInterval(WWCursor p, int n);

WWPalette WWCursor_GetPalette(WWCursor p);
WWPalette WWCursor_SetPalette(WWCursor p, WWPalette plt);

WWCursor WWCursor_Create(WWPalette palette);
WWCursor WWCursor_Destroy(WWCursor cursor);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
