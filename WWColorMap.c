/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWColorMapP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWColorMap WWColorMap_Create(int * lcd_colors)
{
  WWColorMap color_map;

  color_map = (WWColorMap)malloc(sizeof(_WWColorMap));
  if (color_map == NULL)
    WonX_Error("WWColorMap_Create", "Cannot allocate memory");

  WWColorMap_SetLCDColors(color_map, lcd_colors);

  return (color_map);
}

WWColorMap WWColorMap_Destroy(WWColorMap color_map)
{
  if (color_map == NULL) return (NULL);
  free(color_map);
  return (NULL);
}

int * WWColorMap_GetLCDColors(WWColorMap color_map, int * lcd_colors)
{
  int i;

  for (i = 0; i < 8; i++) {
    lcd_colors[i] = WWColorMap_GetLCDColor(color_map, i);
  }

  return (lcd_colors);
}

int WWColorMap_SetLCDColors(WWColorMap color_map, int * lcd_colors)
{
  int i;

  for (i = 0; i < 8; i++) {
    if (lcd_colors == NULL) {
      WWColorMap_SetLCDColor(color_map, i, (i * 2) + ((i == 7) ? 1 : 0));
    } else {
      WWColorMap_SetLCDColor(color_map, i, lcd_colors[i]);
    }
  }

  return (0);
}

int WWColorMap_GetLCDColor(WWColorMap color_map, int color)
{
  return (color_map->lcd_color[color]);
}

int WWColorMap_SetLCDColor(WWColorMap color_map, int color, int lcd_color)
{
  return (color_map->lcd_color[color] = lcd_color);
}

int WWColorMap_PrintData(WWColorMap c, FILE * f)
{
  int i;

  fprintf(f, "\n");

  for (i = 0; i < 8; i++) {
    fprintf(f, "colormap :\tcolor[%01d] = %d\n",
	    i, WWColorMap_GetLCDColor(c, i));
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
