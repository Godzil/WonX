/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWCharacterP.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWCharacter_GetNumber(WWCharacter c)
{
  if (c == NULL) Error("WWCharacter_GetNumber()", "WWCharacter is NULL.");

  return (c->number);
}

int WWCharacter_SetNumber(WWCharacter c, int n)
{
  if ((n < 0) || (n >= 512))
    Error("WWCharacter_SetNumber()", "Invalid range.");

  return (c->number = n);
}

WWCharacter WWCharacter_Create(int number, unsigned char * bitmap)
{
  WWCharacter character;

  character = (WWCharacter)malloc(sizeof(_WWCharacter));
  if (character == NULL)
    Error("WWCharacter_Create", "Cannot allocate memory.");

  WWCharacter_SetNumber(character, number);
  WWCharacter_SetBitmap(character, bitmap);

  return (character);
}

WWCharacter WWCharacter_Destroy(WWCharacter character)
{
  if (character == NULL)
    Error("WWCharacter_Destroy()", "WWCharacter is NULL.");
  free(character);
  return (NULL);
}

int WWCharacter_SetBitmap(WWCharacter character, unsigned char * bitmap)
{
  int i;

  if (character == NULL)
    Error("WWCharacter_SetBitmap()", "WWCharacter is NULL.");

  for (i = 0; i < 16; i++) {
    if (bitmap == NULL) {
      character->bitmap[i] = 0x00;
    } else {
      character->bitmap[i] = bitmap[i];
    }
  }

  return (0);
}

#include <stdio.h>

int WWCharacter_GetPixel(WWCharacter character, int x, int y)
{
  if (character == NULL)
    Error("WWCharacter_GetPixel()", "WWCharacter is NULL.");

  if ((x < 0) || (x > 7))
    Error("WWCharacter_GetPixel()", "x is invalid value.");
  if ((y < 0) || (y > 7))
    Error("WWCharacter_GetPixel()", "y is invalid value.");

  /* ビットマップは2ビットでぴとつのピクセルに対応する．      */
  /* 2ビットの値が，palette の色に対応する．                  */
  /* bitmap は unsigned char bitmap[16]; に定義してある． */

  /* パレット色(0〜3)を返す */
  return ( (character->bitmap[y * 2 + x / 4] >> ((x % 4) * 2)) & 0x03 );
}

int WWCharacter_SetPixel(WWCharacter character, int x, int y, int pixel)
{
  unsigned char p;
  if (character == NULL)
    Error("WWCharacter_SetPixel()", "WWCharacter is NULL.");

  if ((x < 0) || (x > 7))
    Error("WWCharacter_SetPixel()", "x is invalid value.");
  if ((y < 0) || (y > 7))
    Error("WWCharacter_SetPixel()", "y is invalid value.");
  if ((pixel < 0) || (pixel > 3))
    Error("WWCharacter_SetPixel()", "Invalid pixel.");

  p = ((unsigned char)pixel) & 0x03;
  p = p << ((x % 4) * 2);

  character->bitmap[y * 2 + x / 4] &= ~(0x03 << ((x % 4) * 2));
  character->bitmap[y * 2 + x / 4] |= p;

  return (pixel);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
