/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WonXTextP.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWText WonXText_GetWWText(WonXText wonx_text)
{ return (wonx_text->ww_text); }
WWText WonXText_SetWWText(WonXText wonx_text, WWText ww_text)
{ return (wonx_text->ww_text = ww_text); }

WonXText WonXText_Create(WWScreen screen, int x, int y, int width, int height,
			 WWPalette palette)
{
  WonXText wonx_text;
  WWText ww_text;

  wonx_text = (WonXText)malloc(sizeof(_WonXText));
  if (wonx_text == NULL)
    WonX_Error("WonXText_Create", "Cannot allocate memory.");

  ww_text = WWText_Create(screen, x, y, width, height, palette);
  if (ww_text == NULL)
    WonX_Error("WonXText_Create", "Cannot create WonderWitch text.");
  WonXText_SetWWText(wonx_text, ww_text);

  return (wonx_text);
}

WonXText WonXText_Destroy(WonXText wonx_text)
{
  if (wonx_text == NULL)
    WonX_Error("WonXText_Destroy", "Object is not created.");

  if (WonXText_GetWWText(wonx_text))
    WonXText_SetWWText(wonx_text,
		       WWText_Destroy(WonXText_GetWWText(wonx_text)));

  free(wonx_text);

  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
