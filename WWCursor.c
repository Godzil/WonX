/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWCursorP.h"
#include "WonX.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

int WWCursor_ON(   WWCursor p) { return (p->on =  1); }
int WWCursor_OFF(  WWCursor p) { return (p->on =  0); }
int WWCursor_IsON( WWCursor p) { return (p->on != 0); }
int WWCursor_IsOFF(WWCursor p) { return (p->on == 0); }

int WWCursor_GetX(       WWCursor p       ) { return (p->x           ); }
int WWCursor_SetX(       WWCursor p, int n) { return (p->x        = n); }
int WWCursor_GetY(       WWCursor p       ) { return (p->y           ); }
int WWCursor_SetY(       WWCursor p, int n) { return (p->y        = n); }
int WWCursor_GetWidth(   WWCursor p       ) { return (p->width       ); }
int WWCursor_SetWidth(   WWCursor p, int n) { return (p->width    = n); }
int WWCursor_GetHeight(  WWCursor p       ) { return (p->height      ); }
int WWCursor_SetHeight(  WWCursor p, int n) { return (p->height   = n); }
int WWCursor_GetInterval(WWCursor p       ) { return (p->interval    ); }
int WWCursor_SetInterval(WWCursor p, int n) { return (p->interval = n); }

WWPalette WWCursor_GetPalette(WWCursor p)
{ return (p->palette      ); }
WWPalette WWCursor_SetPalette(WWCursor p, WWPalette plt)
{ return (p->palette = plt); }

WWCursor WWCursor_Create(WWPalette palette)
{
  WWCursor cursor;

  cursor = (WWCursor)malloc(sizeof(_WWCursor));
  if (cursor == NULL)
    WonX_Error("WWCursor_Create", "Cannot allocate memory");

  WWCursor_OFF(cursor);

  WWCursor_SetX(       cursor,  0);
  WWCursor_SetY(       cursor,  0);
  WWCursor_SetWidth(   cursor,  1);
  WWCursor_SetHeight(  cursor,  1);
  WWCursor_SetInterval(cursor, 30);

  WWCursor_SetPalette(cursor, palette);

  return (cursor);
}

WWCursor WWCursor_Destroy(WWCursor cursor)
{
  if (cursor == NULL)
    WonX_Error("WWCursor_Destroy", "Object is not created.");
  free(cursor);
  return (NULL);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
