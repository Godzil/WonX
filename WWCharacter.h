#ifndef _WWCharacter_h_INCLUDED_
#define _WWCharacter_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWCharacter * WWCharacter;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "WWDisplay.h"
#include "wonx_include/libwwc.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWCharacter_GetNumber(WWCharacter c);
int WWCharacter_SetNumber(WWCharacter c, int n);
unsigned char WWCharacter_GetBitmap(WWCharacter c, int n);
unsigned char WWCharacter_SetBitmap(WWCharacter c, int n, unsigned char bitmap);

WWCharacter WWCharacter_Create(int number);
WWCharacter WWCharacter_Destroy(WWCharacter character);

int WWCharacter_GetPixel(WWCharacter character, int x, int y,
			 WWDisplay display);

int WWCharacter_ClearAllPixels(WWCharacter character);
int WWCharacter_CopyAllPixels(WWCharacter dst, WWCharacter src);
int WWCharacter_PrintData(WWCharacter character, WWDisplay display, FILE * f);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
