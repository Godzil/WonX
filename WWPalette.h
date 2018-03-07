#ifndef _WWPalette_h_INCLUDED_
#define _WWPalette_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWPalette * WWPalette;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWPalette_GetNumber(WWPalette p);
int WWPalette_SetNumber(WWPalette p, int n);
int WWPalette_GetTransparent(WWPalette palette);
int WWPalette_SetTransparent(WWPalette palette, int f);
WWPalette WWPalette_Create(int number, int * mapped_colors, int transparent);
WWPalette WWPalette_Destroy(WWPalette palette);
int * WWPalette_GetMappedColors(WWPalette palette, int * mapped_colors);
int WWPalette_SetMappedColors(WWPalette palette, int * mapped_colors);
int WWPalette_GetMappedColor(WWPalette palette, int color);
int WWPalette_SetMappedColor(WWPalette palette, int color, int mapped_color);
int WWPalette_PrintData(WWPalette p, FILE * f);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
