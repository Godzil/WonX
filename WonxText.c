/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonxTextP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWText WonxText_GetWWText(WonxText wonx_text)
{ return (wonx_text->ww_text); }
WWText WonxText_SetWWText(WonxText wonx_text, WWText ww_text)
{ return (wonx_text->ww_text = ww_text); }

WonxText WonxText_Create(WWScreen screen, int x, int y, int width, int height,
			 WWPalette palette)
{
  WonxText wonx_text;
  WWText ww_text;

  wonx_text = (WonxText)malloc(sizeof(_WonxText));
  if (wonx_text == NULL)
    Wonx_Error("WonxText_Create", "Cannot allocate memory.");

  ww_text = WWText_Create(screen, x, y, width, height, palette);
  if (ww_text == NULL)
    Wonx_Error("WonxText_Create", "Cannot create WonderWitch text.");
  WonxText_SetWWText(wonx_text, ww_text);

  return (wonx_text);
}

WonxText WonxText_Destroy(WonxText wonx_text)
{
  if (wonx_text == NULL)
    Wonx_Error("WonxText_Destroy", "Object is not created.");

  if (WonxText_GetWWText(wonx_text))
    WonxText_SetWWText(wonx_text,
		       WWText_Destroy(WonxText_GetWWText(wonx_text)));

  free(wonx_text);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
