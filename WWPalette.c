/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWPaletteP.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

int WWPalette_GetNumber(WWPalette p) { return (p->number); }
int WWPalette_SetNumber(WWPalette p, int n) { return (p->number = n); }

int WWPalette_GetTransparent(WWPalette p) { return (p->transparent); }
int WWPalette_SetTransparent(WWPalette p, int f)
{ return (p->transparent = f); }

WWPalette WWPalette_Create(int number, int * mapped_colors, int transparent)
{
  WWPalette palette;

  palette = (WWPalette)malloc(sizeof(_WWPalette));
  if (palette == NULL) Error("WWPalette_Create", "Cannot allocate memory");

  WWPalette_SetNumber(palette, number);
  WWPalette_SetTransparent(palette, transparent);
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
  if (WWPalette_GetTransparent(palette) && (pixel == 0)) {
    pixel = -1;
  }
  return (pixel);
}

int WWPalette_SetMappedColor(WWPalette palette, int color, int mapped_color)
{
  if (mapped_color == -1) mapped_color = 0;
  return (palette->mapped_color[color] = mapped_color);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/