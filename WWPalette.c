/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWPaletteP.h"
#include "WonX.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWPalette_GetNumber(WWPalette p) { return (p->number); }
int WWPalette_SetNumber(WWPalette p, int n) { return (p->number = n); }

/*
 * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
 * WWPalette で透明色を管理する必要は無くなった．一応コードを残しておく．
 */
#if 0
int WWPalette_GetTransparent(WWPalette p) { return (p->transparent); }
int WWPalette_SetTransparent(WWPalette p, int f)
{ return (p->transparent = f); }
#endif

int WWPalette_GetRed(  WWPalette p, int n) { return (p->red[  n]); }
int WWPalette_GetGreen(WWPalette p, int n) { return (p->green[n]); }
int WWPalette_GetBlue( WWPalette p, int n) { return (p->blue[ n]); }
int WWPalette_SetRed(  WWPalette p, int n, int value)
{ return (p->red[  n] = value); }
int WWPalette_SetGreen(WWPalette p, int n, int value)
{ return (p->green[n] = value); }
int WWPalette_SetBlue( WWPalette p, int n, int value)
{ return (p->blue[ n] = value); }

/*
 * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
 * WWPalette で透明色を管理する必要は無くなった．
 * もともとは，
 * WWPalette WWPalette_Create(int number, int * mapped_colors, int transparent)
 * のように，引数 transparent があった．
 */
WWPalette WWPalette_Create(int number, int * mapped_colors)
{
  WWPalette palette;
  int i;

  palette = (WWPalette)malloc(sizeof(_WWPalette));
  if (palette == NULL)
    WonX_Error("WWPalette_Create", "Cannot allocate memory");

  WWPalette_SetNumber(palette, number);

  /*
   * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
   * WWPalette で透明色を管理する必要は無くなった．一応コードを残しておく．
   */
#if 0
  WWPalette_SetTransparent(palette, transparent);
#endif

  for (i = 0; i < 16; i++) {
    WWPalette_SetRed(  palette, i, 0);
    WWPalette_SetGreen(palette, i, 0);
    WWPalette_SetBlue( palette, i, 0);
  }
  WWPalette_SetMappedColors(palette, mapped_colors);

  return (palette);
}

WWPalette WWPalette_Destroy(WWPalette palette)
{
  if (palette == NULL) return (NULL);
  free(palette);
  return (NULL);
}

int * WWPalette_GetMappedColors(WWPalette palette, int * mapped_colors)
{
  int i;

  for (i = 0; i < 4; i++) {
    mapped_colors[i] = WWPalette_GetMappedColor(palette, i);
  }

  return (mapped_colors);
}

int WWPalette_SetMappedColors(WWPalette palette, int * mapped_colors)
{
  int i;

  for (i = 0; i < 4; i++) {
    if (mapped_colors == NULL) {
      WWPalette_SetMappedColor(palette, i, (i * 2) + ((i == 3) ? 1 : 0));
    } else {
      WWPalette_SetMappedColor(palette, i, mapped_colors[i]);
    }
  }

  return (0);
}

int WWPalette_GetMappedColor(WWPalette palette, int color)
{
  int pixel;

  pixel = palette->mapped_color[color];

  /*
   * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
   * WWPalette で透明色を管理する必要は無くなった．一応コードを残しておく．
   */
#if 0
  if (WWPalette_GetTransparent(palette) && (pixel == 0)) {
    pixel = -1;
  }
#endif

  return (pixel);
}

int WWPalette_SetMappedColor(WWPalette palette, int color, int mapped_color)
{
  /*
   * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
   * WWPalette で透明色を管理する必要は無くなった．一応コードを残しておく．
   */
#if 0
  if (mapped_color == -1) mapped_color = 0;
#endif
  return (palette->mapped_color[color] = mapped_color);
}

int WWPalette_PrintData(WWPalette p, WWDisplay display, FILE * f)
{
  int i, n;
  int transparent;
  int red, green, blue;

  n = WWPalette_GetNumber(p);

  fprintf(f, "\n");

  fprintf(f, "palette[%02d] :\tnumber = %d\n", n, WWPalette_GetNumber(p));

  /*
   * WonX-2.0 以降から，透明色の判定は WWDisplay で行うように変更したので，
   * WWPalette で透明色を管理する必要は無くなった．一応コードを残しておく．
   */
#if 1
  transparent = WWDisplay_IsTransparent(display, p, 0);
  fprintf(f, "palette[%02d] :\ttransparent = %s\n",
	  n, wonx_true_false(transparent));
#else
  fprintf(f, "palette[%02d] :\ttransparent = %s\n",
          n, wonx_true_false(WWPalette_GetTransparent(p)));
#endif

  for (i = 0; i < 4; i++) {
    fprintf(f, "palette[%02d] :\tcolor[%01d] = %d\n",
	    n, i, WWPalette_GetMappedColor(p, i));
  }

  for (i = 0; i < 16; i++) {
    red   = WWPalette_GetRed(  p, i);
    green = WWPalette_GetGreen(p, i);
    blue  = WWPalette_GetBlue( p, i);
    fprintf(f, "palette[%02d] :\tRGB[%02d] = 0x%c%c%c\n",
	    n, i,
	    wonx_dec_to_hex(red),
	    wonx_dec_to_hex(green),
	    wonx_dec_to_hex(blue));
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
