#ifndef _WWCharacter_h_INCLUDED_
#define _WWCharacter_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdlib.h>

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWCharacter * WWCharacter;

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWCharacter_GetNumber(WWCharacter c);
int WWCharacter_SetNumber(WWCharacter c, int n);
WWCharacter WWCharacter_Create(int number, unsigned char * bitmap);
WWCharacter WWCharacter_Destroy(WWCharacter character);
int WWCharacter_SetBitmap(WWCharacter character, unsigned char * bitmap);
int WWCharacter_GetPixel(WWCharacter character, int x, int y);
int WWCharacter_SetPixel(WWCharacter character, int x, int y, int pixel);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
