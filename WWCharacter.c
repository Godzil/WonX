/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <string.h>

#include "WWCharacterP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWCharacter_GetNumber(WWCharacter c)
{
  if (c == NULL) WonX_Error("WWCharacter_GetNumber", "WWCharacter is NULL.");

  return (c->number);
}

int WWCharacter_SetNumber(WWCharacter c, int n)
{
  if (c == NULL) WonX_Error("WWCharacter_SetNumber", "WWCharacter is NULL.");

  if ((n < 0) || (n > 512 - 1))
    WonX_Error("WWCharacter_SetNumber", "Invalid range.");

  return (c->number = n);
}

unsigned char WWCharacter_GetBitmap(WWCharacter c, int n)
{
  if (c == NULL) WonX_Error("WWCharacter_GetBitmap", "WWCharacter is NULL.");

  if ((n < 0) || (n > 32 - 1))
    WonX_Error("WWCharacter_GetBitmap", "Invalid range.");

  return (c->bitmap[n]);
}

unsigned char WWCharacter_SetBitmap(WWCharacter c, int n, unsigned char bitmap)
{
  if (c == NULL) WonX_Error("WWCharacter_SetBitmap", "WWCharacter is NULL.");

  if ((n < 0) || (n > 32 - 1))
    WonX_Error("WWCharacter_SetBitmap", "Invalid range.");

  return (c->bitmap[n] = bitmap);
}

WWCharacter WWCharacter_Create(int number)
{
  WWCharacter character;

  character = (WWCharacter)malloc(sizeof(_WWCharacter));
  if (character == NULL)
    WonX_Error("WWCharacter_Create", "Cannot allocate memory.");

  WWCharacter_SetNumber(character, number);
  WWCharacter_ClearAllPixels(character);

  return (character);
}

WWCharacter WWCharacter_Destroy(WWCharacter character)
{
  if (character == NULL)
    WonX_Error("WWCharacter_Destroy", "WWCharacter is NULL.");
  free(character);
  return (NULL);
}

int WWCharacter_GetPixel(WWCharacter character, int x, int y,
			 WWDisplay display)
{
  unsigned short int pixel;

  if (character == NULL)
    WonX_Error("WWCharacter_GetPixel", "WWCharacter is NULL.");

  if ((x < 0) || (x > 7))
    WonX_Error("WWCharacter_GetPixel", "x is out of range.");
  if ((y < 0) || (y > 7))
    WonX_Error("WWCharacter_GetPixel", "y is out of range.");

  /* パレット色を返す */
  pixel = 0;
  switch (WWDisplay_GetColorMode(display)) {
  case COLOR_MODE_GRAYSCALE:
  case COLOR_MODE_4COLOR:
    pixel  = ((character->bitmap[y * 2 + 0] >> (7-x)) & 1) << 0;
    pixel |= ((character->bitmap[y * 2 + 1] >> (7-x)) & 1) << 1;
    break;
  case COLOR_MODE_16COLOR:
    pixel  = ((character->bitmap[y * 4 + 0] >> (7-x)) & 1) << 0;
    pixel |= ((character->bitmap[y * 4 + 1] >> (7-x)) & 1) << 1;
    pixel |= ((character->bitmap[y * 4 + 2] >> (7-x)) & 1) << 2;
    pixel |= ((character->bitmap[y * 4 + 3] >> (7-x)) & 1) << 3;
    break;
  case COLOR_MODE_16PACKED:
    pixel = character->bitmap[y * 4 + (7-x) / 2] >> (((7-x) % 2) * 4);
    pixel &= 0x0f;
    break;
  default:
    WonX_Error("WWCharacter_GetPixel", "Unknown color mode.");
  }

  return (pixel);
}

int WWCharacter_ClearAllPixels(WWCharacter character)
{
  if (character == NULL)
    WonX_Error("WWCharacter_ClearAllPixels", "WWCharacter is NULL.");

  memset(character->bitmap, 0, 32);

  return (0);
}

int WWCharacter_CopyAllPixels(WWCharacter dst, WWCharacter src)
{
  if (dst == NULL)
    WonX_Error("WWCharacter_CopyAllPixel", "dst is NULL.");
  if (src == NULL)
    WonX_Error("WWCharacter_CopyAllPixel", "src is NULL.");

  memcpy(dst->bitmap, src->bitmap, 32);

  return (0);
}

int WWCharacter_PrintData(WWCharacter character, WWDisplay display, FILE * f)
{
  int i, x, y, n;

  if (character == NULL)
    WonX_Error("WWCharacter_PrintData", "WWCharacter is NULL.");

  n = WWCharacter_GetNumber(character);

  fprintf(f, "\n");

  fprintf(f, "character[%d] :\tnumber = %d\n",
	  n, WWCharacter_GetNumber(character));

  for (i = 0; i < 32; i += 8) {
    fprintf(f, "character[%d] :\tbitmap[%d] =", n, i);
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i  ));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+1));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+2));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+3));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+4));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+5));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+6));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmap(character, i+7));
    fprintf(f, "\n");
  }

  fprintf(f, "character[%d] :\tpixels :   01234567\n", n);
  for (y = 0; y < 8; y++) {
    fprintf(f, "character[%d] :\tpixels : %d ", n, y);
    for (x = 0; x < 8; x++) {
      fprintf(f, "%d", WWCharacter_GetPixel(character, x, y, display));
    }
    fprintf(f, "\n");
  }

  fflush(f);

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
