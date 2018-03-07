/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWTextP.h"
#include "etc.h"

/* �ե���ȤΥӥåȥޥåץǡ��� */
#include "WWTextFonts.c"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* ���Фμ���                                                              */
/*===========================================================================*/

WWScreen WWText_GetScreen(WWText t) { return (t->screen); }
int WWText_GetX(WWText t) { return (t->x); }
int WWText_GetY(WWText t) { return (t->y); }
int WWText_GetWidth( WWText t) { return (t->width ); }
int WWText_GetHeight(WWText t) { return (t->height); }
int WWText_GetBase(WWText t) { return (t->base); }
WWPalette WWText_GetPalette(WWText t) { return (t->palette); }
static WWCharacter WWText_GetFont(WWText t, int n) { return (t->font[n]); }

/*===========================================================================*/
/* ���Ф�����                                                              */
/*===========================================================================*/

WWScreen WWText_SetScreen(WWText t, WWScreen s) { return (t->screen = s); }
int WWText_SetX(WWText t, int n) { return (t->x = n); }
int WWText_SetY(WWText t, int n) { return (t->y = n); }
int WWText_SetWidth( WWText t, int n) { return (t->width  = n); }
int WWText_SetHeight(WWText t, int n) { return (t->height = n); }
int WWText_SetBase(WWText t, int n) { return (t->base = n); }
WWPalette WWText_SetPalette(WWText t, WWPalette p) { return (t->palette = p); }
static WWCharacter WWText_SetFont(WWText t, int n, WWCharacter c)
{ return (t->font[n] = c); }

int WWText_SetTextWindow(WWText ww_text, int x, int y,
			 int width, int height, int base,
			 WWDisplay ww_display)
{
  int tx, ty, c;
  WWCharacter ww_character;

  WWText_SetX(ww_text, x);
  WWText_SetY(ww_text, y);
  WWText_SetWidth(ww_text, width);
  WWText_SetHeight(ww_text, height);
  WWText_SetBase(ww_text, base);

  c = WWText_GetBase(ww_text);
  for (ty = 0; ty < WWText_GetHeight(ww_text); ty++) {
    for (tx = 0; tx < WWText_GetWidth(ww_text); tx++) {
      if (c >= 512) Wonx_Error("WWText_SetTextWindow", "Over character.");
      ww_character = WWDisplay_GetCharacter(ww_display, c);
      WWCharacter_SetBitmap(ww_character, NULL);
      WWScreen_SetCharacter(WWText_GetScreen(ww_text),
			    WWText_GetX(ww_text) + tx,
			    WWText_GetY(ww_text) + ty,
			    ww_character);
      c++;
    }
  }
  return (0);
}

int WWText_PutCharacter(WWText ww_text, int x, int y, int character,
			WWDisplay ww_display)
{
  WWCharacter ww_character;

  if ((character < 0) || (character > 127))
    Wonx_Error("WWText_PutCharacter", "Character number is out of range.");

  /*
   * �ƥ�����ɽ���ϡ�text_window_init() �ǻ��ꤷ���ƥ����ȥ�����ɥ���
   * ��ɸ�ϤǹԤ�(�餷��)��(������ɥ���κ��夬(0,0)�ˤʤ�)
   */

  if ( (x < 0) || (x > WWText_GetWidth( ww_text) - 1) ||
       (y < 0) || (y > WWText_GetHeight(ww_text) - 1) )
    Wonx_Error("WWText_PutCharacter", "Position is out of range.");

#if 0
  n = WWText_GetBase(ww_text) +
    (x - WWText_GetX(ww_text)) +
    (y - WWText_GetY(ww_text)) * WWText_GetWidth(ww_text);
  ww_character = WWDisplay_GetCharacter(ww_display, n);
#else
  ww_character = WWScreen_GetCharacter(WWText_GetScreen(ww_text),
				       WWText_GetX(ww_text) + x,
				       WWText_GetY(ww_text) + y);
#endif

  WWCharacter_CopyBitmap(ww_character, WWText_GetFont(ww_text, character));

  /* ɽ�����˥ѥ�åȤ����ꤹ��ΤǤ����Τ��� ���� */
  WWScreen_SetPalette(WWText_GetScreen(ww_text),
		      WWText_GetX(ww_text) + x,
		      WWText_GetY(ww_text) + y,
		      WWText_GetPalette(ww_text));

  return (character);
}

/*===========================================================================*/
/* ���֥������Ȥ������Ⱦõ�                                                  */
/*===========================================================================*/

WWText WWText_Create(WWScreen screen,
		     int x, int y, int width, int height,
		     WWPalette palette)
{
  WWText ww_text;
  int i;

  ww_text = (WWText)malloc(sizeof(_WWText));
  if (ww_text == NULL) Wonx_Error("WWText_Create", "Cannot allocate memory.");

  WWText_SetScreen(ww_text, screen);
  WWText_SetX(ww_text, 0);
  WWText_SetY(ww_text, 0);
  WWText_SetWidth( ww_text, width );
  WWText_SetHeight(ww_text, height);
  WWText_SetPalette(ww_text, palette);

  for (i = 0; i < 128; i++) {
    WWText_SetFont(ww_text, i, WWCharacter_Create(i, &(fonts[i * 16])));
  }

  return (ww_text);
}

WWText WWText_Destroy(WWText ww_text)
{
  int i;

  if (ww_text == NULL) Wonx_Error("WWText_Destroy", "Object is not created.");

  for (i = 0; i < 128; i++) {
    if (WWText_GetFont(ww_text, i))
      WWText_SetFont(ww_text, i,
		     WWCharacter_Destroy(WWText_GetFont(ww_text, i)));
  }

  free(ww_text);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
