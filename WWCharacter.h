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

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWCharacter_GetNumber(WWCharacter c);
int WWCharacter_SetNumber(WWCharacter c, int n);
WWCharacter WWCharacter_Create(int number, unsigned char * bitmap);
WWCharacter WWCharacter_Destroy(WWCharacter character);
unsigned char * WWCharacter_GetBitmap(WWCharacter character);
int WWCharacter_SetBitmap(WWCharacter character, unsigned char * bitmap);
int WWCharacter_GetPixel(WWCharacter character, int x, int y);
int WWCharacter_SetPixel(WWCharacter character, int x, int y, int pixel);
int WWCharacter_CopyBitmap(WWCharacter dst, WWCharacter src);
int WWCharacter_PrintData(WWCharacter character, FILE * f);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
