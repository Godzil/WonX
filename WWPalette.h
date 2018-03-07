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

#include "WWDisplay.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWPalette_GetNumber(WWPalette p);
int WWPalette_SetNumber(WWPalette p, int n);

/*
 * WonX-2.0 �ʹߤ��顤Ʃ������Ƚ��� WWDisplay �ǹԤ��褦���ѹ������Τǡ�
 * WWPalette ��Ʃ�������������ɬ�פ�̵���ʤä�����������ɤ�Ĥ��Ƥ�����
 */
#if 0
int WWPalette_GetTransparent(WWPalette palette);
int WWPalette_SetTransparent(WWPalette palette, int f);
#endif

int WWPalette_GetRed(  WWPalette p, int n);
int WWPalette_GetGreen(WWPalette p, int n);
int WWPalette_GetBlue( WWPalette p, int n);
int WWPalette_SetRed(  WWPalette p, int n, int value);
int WWPalette_SetGreen(WWPalette p, int n, int value);
int WWPalette_SetBlue( WWPalette p, int n, int value);

/*
 * WonX-2.0 �ʹߤ��顤Ʃ������Ƚ��� WWDisplay �ǹԤ��褦���ѹ������Τǡ�
 * WWPalette ��Ʃ�������������ɬ�פ�̵���ʤä�����������ɤ�Ĥ��Ƥ�����
 */
#if 1
WWPalette WWPalette_Create(int number, int * mapped_colors);
#else
WWPalette WWPalette_Create(int number, int * mapped_colors, int transparent);
#endif
WWPalette WWPalette_Destroy(WWPalette palette);
int * WWPalette_GetMappedColors(WWPalette palette, int * mapped_colors);
int WWPalette_SetMappedColors(WWPalette palette, int * mapped_colors);
int WWPalette_GetMappedColor(WWPalette palette, int color);
int WWPalette_SetMappedColor(WWPalette palette, int color, int mapped_color);
int WWPalette_PrintData(WWPalette p, WWDisplay display, FILE * f);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
