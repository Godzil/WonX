/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <string.h>

#include "WWCharacterP.h"
#include "WonX.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* ナンバーの操作                                                            */
/*===========================================================================*/

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

/*===========================================================================*/
/* ビットマップの操作                                                        */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* char 型として操作するための関数                                           */
/*---------------------------------------------------------------------------*/

unsigned char WWCharacter_GetBitmapAsChar(WWCharacter c, int n)
{
  if (c == NULL)
    WonX_Error("WWCharacter_GetBitmapAsChar", "WWCharacter is NULL.");

  if ((n < 0) || (n > 32 - 1))
    WonX_Error("WWCharacter_GetBitmapAsChar", "Invalid range.");

  return (c->bitmap.bitmap_char[n]);
}

unsigned char WWCharacter_SetBitmapAsChar(WWCharacter c, int n,
					  unsigned char bitmap)
{
  if (c == NULL)
    WonX_Error("WWCharacter_SetBitmapAsChar", "WWCharacter is NULL.");

  if ((n < 0) || (n > 32 - 1))
    WonX_Error("WWCharacter_SetBitmapAsChar", "Invalid range.");

  return (c->bitmap.bitmap_char[n] = bitmap);
}

/*---------------------------------------------------------------------------*/
/* short int 型として操作するための関数                                      */
/*---------------------------------------------------------------------------*/

unsigned short int WWCharacter_GetBitmapAsShortInt(WWCharacter c, int n)
{
  if (c == NULL)
    WonX_Error("WWCharacter_GetBitmapAsShortInt", "WWCharacter is NULL.");

  if ((n < 0) || (n > 16 - 1))
    WonX_Error("WWCharacter_GetBitmapAsShortInt", "Invalid range.");

  return (c->bitmap.bitmap_short_int[n]);
}

unsigned short int WWCharacter_SetBitmapAsShortInt(WWCharacter c, int n,
						   unsigned short int bitmap)
{
  if (c == NULL)
    WonX_Error("WWCharacter_SetBitmapAsShortInt", "WWCharacter is NULL.");

  if ((n < 0) || (n > 16 - 1))
    WonX_Error("WWCharacter_SetBitmapAsShortInt", "Invalid range.");

  return (c->bitmap.bitmap_short_int[n] = bitmap);
}

/*---------------------------------------------------------------------------*/
/* long int 型として操作するための関数                                       */
/*---------------------------------------------------------------------------*/

unsigned long int WWCharacter_GetBitmapAsLongInt(WWCharacter c, int n)
{
  if (c == NULL)
    WonX_Error("WWCharacter_GetBitmapAsLongInt", "WWCharacter is NULL.");

  if ((n < 0) || (n > 8 - 1))
    WonX_Error("WWCharacter_GetBitmapAsLongInt", "Invalid range.");

  return (c->bitmap.bitmap_long_int[n]);
}

unsigned long int WWCharacter_SetBitmapAsLongInt(WWCharacter c, int n,
						 unsigned long int bitmap)
{
  if (c == NULL)
    WonX_Error("WWCharacter_SetBitmapAsLongInt", "WWCharacter is NULL.");

  if ((n < 0) || (n > 8 - 1))
    WonX_Error("WWCharacter_SetBitmapAsLongInt", "Invalid range.");

  return (c->bitmap.bitmap_long_int[n] = bitmap);
}

/*===========================================================================*/
/* オブジェクトの生成と削除                                                  */
/*===========================================================================*/

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

/*===========================================================================*/
/* ピクセルの操作                                                            */
/*===========================================================================*/

int WWCharacter_GetPixel(WWCharacter character, int x, int y,
			 WWDisplay display)
{
  unsigned short int pixel;
  unsigned short int spixel;
  unsigned long  int lpixel;

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
    spixel = (character->bitmap.bitmap_short_int[y] >> (7-x)) & 0x0101;
    pixel =
      ((spixel & 0x0001) ? 1 : 0) |
      ((spixel & 0x0100) ? 2 : 0);
#if 0
    pixel  = ((character->bitmap.bitmap_char[y * 2 + 0] >> (7-x)) & 1) << 0;
    pixel |= ((character->bitmap.bitmap_char[y * 2 + 1] >> (7-x)) & 1) << 1;
#endif
    break;
  case COLOR_MODE_16COLOR:
    lpixel = (character->bitmap.bitmap_long_int[y] >> (7-x)) & 0x01010101;
    pixel =
      ((lpixel & 0x00000001) ? 1 : 0) |
      ((lpixel & 0x00000100) ? 2 : 0) |
      ((lpixel & 0x00010000) ? 4 : 0) |
      ((lpixel & 0x01000000) ? 8 : 0);
#if 0
    pixel  = ((character->bitmap[y * 4 + 0] >> (7-x)) & 1) << 0;
    pixel |= ((character->bitmap[y * 4 + 1] >> (7-x)) & 1) << 1;
    pixel |= ((character->bitmap[y * 4 + 2] >> (7-x)) & 1) << 2;
    pixel |= ((character->bitmap[y * 4 + 3] >> (7-x)) & 1) << 3;
#endif
    break;
  case COLOR_MODE_16PACKED:
    lpixel = character->bitmap.bitmap_long_int[y];
    lpixel = lpixel >> (3 - (7-x) / 2) * 8;
    lpixel = lpixel >> ((7-x) % 2) * 4;
    pixel = lpixel & 0x0f;
#if 0
    pixel = character->bitmap[y * 4 + 3 - (7-x) / 2] >> (((7-x) % 2) * 4);
    pixel &= 0x0f;
#endif
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

  memset(character->bitmap.bitmap_char, 0, 32);

  return (0);
}

int WWCharacter_CopyAllPixels(WWCharacter dst, WWCharacter src)
{
  if (dst == NULL)
    WonX_Error("WWCharacter_CopyAllPixel", "dst is NULL.");
  if (src == NULL)
    WonX_Error("WWCharacter_CopyAllPixel", "src is NULL.");

  memcpy(dst->bitmap.bitmap_char, src->bitmap.bitmap_char, 32);

  return (0);
}

/*===========================================================================*/
/* 内部データ出力                                                            */
/*===========================================================================*/

int WWCharacter_PrintData(WWCharacter character, WWDisplay display, FILE * f)
{
  int i, x, y, n;
  int pixel;

  if (character == NULL)
    WonX_Error("WWCharacter_PrintData", "WWCharacter is NULL.");

  n = WWCharacter_GetNumber(character);

  fprintf(f, "\n");

  fprintf(f, "character[%03d] :\tnumber = %d\n",
	  n, WWCharacter_GetNumber(character));

  for (i = 0; i < 32; i += 8) {
    fprintf(f, "character[%03d] :\tbitmap[%02d] =", n, i);
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i  ));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+1));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+2));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+3));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+4));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+5));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+6));
    fprintf(f, " %02x", (int)WWCharacter_GetBitmapAsChar(character, i+7));
    fprintf(f, "\n");
  }

  fprintf(f, "character[%03d] :\tpixels :   01234567\n", n);
  for (y = 0; y < 8; y++) {
    fprintf(f, "character[%03d] :\tpixels : %01d ", n, y);
    for (x = 0; x < 8; x++) {
      pixel = WWCharacter_GetPixel(character, x, y, display);
      fprintf(f, "%c", wonx_dec_to_hex(pixel));
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
