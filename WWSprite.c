/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWSpriteP.h"
#include "WonX.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int         WWSprite_GetNumber(    WWSprite s) { return (s->number); }
int         WWSprite_GetHorizontal(WWSprite s) { return (s->horizontal); }
int         WWSprite_GetVertical(  WWSprite s) { return (s->vertical); }
int         WWSprite_GetPriority(  WWSprite s) { return (s->priority); }
int         WWSprite_GetClipping(  WWSprite s) { return (s->clipping); }
WWPalette   WWSprite_GetPalette(   WWSprite s) { return (s->palette); }
WWCharacter WWSprite_GetCharacter( WWSprite s) { return (s->character); }

int WWSprite_SetNumber(    WWSprite s, int n) { return (s->number = n); }
int WWSprite_SetHorizontal(WWSprite s, int f) { return (s->horizontal = f); }
int WWSprite_SetVertical(  WWSprite s, int f) { return (s->vertical   = f); }
int WWSprite_SetPriority(  WWSprite s, int f) { return (s->priority   = f); }
int WWSprite_SetClipping(  WWSprite s, int f) { return (s->clipping   = f); }
WWPalette WWSprite_SetPalette(WWSprite s, WWPalette p)
{ return (s->palette = p); }
WWCharacter WWSprite_SetCharacter(WWSprite s, WWCharacter c)
{ return (s->character = c); }

int WWSprite_GetX(WWSprite sprite) { return (sprite->x); }
int WWSprite_GetY(WWSprite sprite) { return (sprite->y); }

int WWSprite_SetPosition(WWSprite sprite, int x, int y)
{
  sprite->x = x;
  sprite->y = y;
  return (0);
}

/* スプライトのピクセル値を返す．(透明色は-1を返す) */
int WWSprite_GetPixel(WWSprite sprite, int x, int y, WWDisplay display)
{
  WWPalette palette;
  WWCharacter character;
  int pixel;

  palette = WWSprite_GetPalette(sprite);
  character = WWSprite_GetCharacter(sprite);

  if (WWSprite_GetHorizontal(sprite)) x = 7 - x;
  if (WWSprite_GetVertical(  sprite)) y = 7 - y;

  pixel = WWCharacter_GetPixel(character, x, y, display);

  /* カラー対応 */
  switch (WWDisplay_GetColorMode(display)) {
  case COLOR_MODE_GRAYSCALE:
    /*
     * WonX-2.0 以降では，透明色の処理は WWDisplay クラスで行うように
     * 変更したので，WWPalette_GetMappedColor() が -1 を返すことは無い．
     */
    pixel = WWPalette_GetMappedColor(palette, pixel);
    break;
  case COLOR_MODE_4COLOR:
  case COLOR_MODE_16COLOR:
  case COLOR_MODE_16PACKED:
    pixel =
      ((unsigned short int)WWPalette_GetRed(  palette, pixel) << 8) |
      ((unsigned short int)WWPalette_GetGreen(palette, pixel) << 4) |
      ((unsigned short int)WWPalette_GetBlue( palette, pixel) << 0);
    break;
  default:
    WonX_Error("WWSprite_GetPixel", "Unknown color mode.");
  }

  /* 透明色の場合には -1 を返す */
  if (WWDisplay_IsTransparent(display, palette, pixel))
    pixel = -1;

  return (pixel);
}

WWSprite WWSprite_Create(int number, int x, int y,
			 int horizontal, int vertical,
			 int priority, int clipping,
			 WWPalette palette, WWCharacter character)
{
  WWSprite sprite;

  sprite = (WWSprite)malloc(sizeof(_WWSprite));
  if (sprite == NULL)
    WonX_Error("WWSprite_Create", "Cannot allocate memory.");

  WWSprite_SetNumber(sprite, number);
  WWSprite_SetHorizontal(sprite, horizontal);
  WWSprite_SetVertical(sprite, vertical);
  WWSprite_SetPriority(sprite, priority);
  WWSprite_SetClipping(sprite, clipping);
  WWSprite_SetPalette(sprite, palette);
  WWSprite_SetCharacter(sprite, character);

  WWSprite_SetPosition(sprite, x, y);

  return (sprite);
}

WWSprite WWSprite_Destroy(WWSprite sprite)
{
  if (sprite == NULL) return (NULL);
  free(sprite);
  return (NULL);
}

int WWSprite_PrintData(WWSprite s, FILE * f)
{
  int n;

  n = WWSprite_GetNumber(s);

  fprintf(f, "\n");

  fprintf(f, "sprite[%03d] :\tnumber     = %d\n", n, WWSprite_GetNumber(s));
  fprintf(f, "sprite[%03d] :\thorizontal = %s\n",
	  n, wonx_true_false(WWSprite_GetHorizontal(s)));
  fprintf(f, "sprite[%03d] :\tvertical   = %s\n",
	  n, wonx_true_false(WWSprite_GetVertical(  s)));
  fprintf(f, "sprite[%03d] :\tpriority   = %s\n",
	  n, wonx_true_false(WWSprite_GetPriority(   s)));
  fprintf(f, "sprite[%03d] :\tclipping   = %s\n",
	  n, wonx_true_false(WWSprite_GetClipping(  s)));
  fprintf(f, "sprite[%03d] :\tpalette number   = %d\n",
	  n, WWPalette_GetNumber(WWSprite_GetPalette(s)));
  fprintf(f, "sprite[%03d] :\tcharacter number = %d\n",
	  n, WWCharacter_GetNumber(WWSprite_GetCharacter(s)));
  fprintf(f, "sprite[%03d] :\tx = %d\n", n, WWSprite_GetX(s));
  fprintf(f, "sprite[%03d] :\ty = %d\n", n, WWSprite_GetY(s));

  fflush(f);

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
