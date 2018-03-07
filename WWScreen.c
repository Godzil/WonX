/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWScreenP.h"
#include "WonX.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*===========================================================================*/
/* �ץ饤�١��Ȥʤ��                                                        */
/*===========================================================================*/

static int WWScreenCharacter_GetHorizontal(WWScreenCharacter sc)
{ return (sc->horizontal); }
static int WWScreenCharacter_GetVertical(WWScreenCharacter sc)
{ return (sc->vertical); }
static WWPalette WWScreenCharacter_GetPalette(WWScreenCharacter sc)
{ return (sc->palette); }
static WWCharacter WWScreenCharacter_GetCharacter(WWScreenCharacter sc)
{ return (sc->character); }

static int WWScreenCharacter_SetHorizontal(WWScreenCharacter sc, int f)
{ return (sc->horizontal = f); }
static int WWScreenCharacter_SetVertical(WWScreenCharacter sc, int f)
{ return (sc->vertical = f); }
static WWPalette WWScreenCharacter_SetPalette(WWScreenCharacter sc,
					      WWPalette palette)
{ return (sc->palette = palette); }
static WWCharacter WWScreenCharacter_SetCharacter(WWScreenCharacter sc,
						  WWCharacter c)
{ return (sc->character = c); }

static WWScreenCharacter WWScreenCharacter_Create(int horizontal, int vertical,
						  WWPalette palette,
						  WWCharacter character)
{
  WWScreenCharacter screen_character;

  screen_character = (WWScreenCharacter)malloc(sizeof(_WWScreenCharacter));
  if (screen_character == NULL)
    WonX_Error("WWScreenCharacter", "Cannot allocate memory.");

  WWScreenCharacter_SetHorizontal(screen_character, horizontal);
  WWScreenCharacter_SetVertical(screen_character, vertical);
  WWScreenCharacter_SetPalette(screen_character, palette);
  WWScreenCharacter_SetCharacter(screen_character, character);

  return (screen_character);
}

static WWScreenCharacter WWScreenCharacter_Destroy(WWScreenCharacter
						   screen_character)
{
  if (screen_character == NULL)
    WonX_Error("WWScreenCharacter_Destroy", "Object is not created.");
  free(screen_character);
  return (NULL);
}

static WWScreenCharacter WWScreen_GetScreenCharacter(WWScreen s, int x, int y)
{
  return (s->screen_characters[y * WWScreen_GetWidth(s) + x]);
}

static WWScreenCharacter WWScreen_SetScreenCharacter(WWScreen s, int x, int y,
						     WWScreenCharacter sc)
{
  return (s->screen_characters[y * WWScreen_GetWidth(s) + x] = sc);
}

/*===========================================================================*/
/* �ѥ֥�å��ʤ��                                                          */
/*===========================================================================*/

int WWScreen_GetHorizontal(WWScreen s, int x, int y)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_GetHorizontal(sc));
}

int WWScreen_GetVertical(WWScreen s, int x, int y)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_GetVertical(sc));
}

WWPalette WWScreen_GetPalette(WWScreen s, int x, int y)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_GetPalette(sc));
}

WWCharacter WWScreen_GetCharacter(WWScreen s, int x, int y)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_GetCharacter(sc));
}

int WWScreen_SetHorizontal(WWScreen s, int x, int y, int f)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_SetHorizontal(sc, f));
}

int WWScreen_SetVertical(WWScreen s, int x, int y, int f)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_SetVertical(sc, f));
}

WWPalette WWScreen_SetPalette(WWScreen s, int x, int y, WWPalette palette)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_SetPalette(sc, palette));
}

WWCharacter WWScreen_SetCharacter(WWScreen s, int x, int y, WWCharacter c)
{
  WWScreenCharacter sc;
  sc = WWScreen_GetScreenCharacter(s, x, y);
  return (WWScreenCharacter_SetCharacter(sc, c));
}

int WWScreen_GetNumber(WWScreen s) { return (s->number); }
int WWScreen_GetWidth( WWScreen s) { return (s->width ); }
int WWScreen_GetHeight(WWScreen s) { return (s->height); }
int WWScreen_GetRollX( WWScreen s) { return (s->roll_x); }
int WWScreen_GetRollY( WWScreen s) { return (s->roll_y); }

int WWScreen_GetEnable(WWScreen s) { return (s->enable); }
int WWScreen_GetMode(  WWScreen s) { return (s->mode  ); }

int WWScreen_GetDrawX(     WWScreen s) { return (s->draw_x     ); }
int WWScreen_GetDrawY(     WWScreen s) { return (s->draw_y     ); }
int WWScreen_GetDrawWidth( WWScreen s) { return (s->draw_width ); }
int WWScreen_GetDrawHeight(WWScreen s) { return (s->draw_height); }

int WWScreen_SetNumber(WWScreen s, int n) { return (s->number = n); }
int WWScreen_SetWidth( WWScreen s, int n) { return (s->width  = n); }
int WWScreen_SetHeight(WWScreen s, int n) { return (s->height = n); }
int WWScreen_SetRollX( WWScreen s, int r) { return (s->roll_x = r); }
int WWScreen_SetRollY( WWScreen s, int r) { return (s->roll_y = r); }

int WWScreen_SetEnable(WWScreen s, int n) { return (s->enable = n); }
int WWScreen_SetMode(  WWScreen s, int n) { return (s->mode   = n); }

int WWScreen_SetDrawX(     WWScreen s, int n) { return (s->draw_x      = n); }
int WWScreen_SetDrawY(     WWScreen s, int n) { return (s->draw_y      = n); }
int WWScreen_SetDrawWidth( WWScreen s, int n) { return (s->draw_width  = n); }
int WWScreen_SetDrawHeight(WWScreen s, int n) { return (s->draw_height = n); }

/* ���顼�ޥåפο�(0��7)���֤�(Ʃ������-1���֤�) */
int WWScreen_GetPixel(WWScreen screen, int x, int y,
		      WWDisplay display, WWCursor cursor)
{
  int cx, cy, px, py;
  int pixel;
  WWCharacter character;
  WWPalette palette;

  /* x,y ��ɸ���ϰϳ��ΤȤ��ϡ����륪���С����� */
  /* (�����꡼���ü��ü�ϡ��Ĥʤ��äƤ���)       */
  while (x < 0) x += WWScreen_GetWidth( screen) * 8;
  while (y < 0) y += WWScreen_GetHeight(screen) * 8;
  x = x % (WWScreen_GetWidth( screen) * 8);
  y = y % (WWScreen_GetHeight(screen) * 8);

  cx = x / 8; cy = y / 8;
  px = x % 8; py = y % 8;

  if (WWScreen_GetHorizontal(screen, cx, cy)) px = 7 - px;
  if (WWScreen_GetVertical(  screen, cx, cy)) py = 7 - py;

  character = WWScreen_GetCharacter(screen, cx, cy);

  /* ��������ɽ���ν��� */
  palette = WWScreen_GetPalette(screen, cx, cy);
  if (cursor != NULL) {
    if ( WWCursor_IsON(cursor) &&
	 (cx >= WWCursor_GetX(cursor)) &&
	 (cx <= WWCursor_GetX(cursor) + WWCursor_GetWidth( cursor) - 1) &&
	 (cy >= WWCursor_GetY(cursor)) &&
	 (cy <= WWCursor_GetY(cursor) + WWCursor_GetHeight(cursor) - 1) ) {
      palette = WWCursor_GetPalette(cursor);
    }
  }

  pixel = WWCharacter_GetPixel(character, px, py, display);

  /* ���顼�б� */
  switch (WWDisplay_GetColorMode(display)) {
  case COLOR_MODE_GRAYSCALE:
    /*
     * WonX-2.0 �ʹߤǤϡ�Ʃ�����ν����� WWDisplay ���饹�ǹԤ��褦��
     * �ѹ������Τǡ�WWPalette_GetMappedColor() �� -1 ���֤����Ȥ�̵����
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
    WonX_Error("WWScreen_GetPixel", "Unknown color mode.");
  }

  /* Ʃ�����ξ��ˤ� -1 ���֤� */
  if (WWDisplay_IsTransparent(display, palette, pixel))
    pixel = -1;

  return (pixel);
}

WWScreen WWScreen_Create(int number,
			 int width, int height,
			 WWPalette initial_palette,
			 WWCharacter initial_character,
			 int draw_x, int draw_y,
			 int draw_width, int draw_height)
{
  WWScreen screen;
  WWScreenCharacter sc;
  int x, y;

  screen = (WWScreen)malloc(sizeof(_WWScreen));
  if (screen == NULL)
    WonX_Error("WWScreen_Create", "Cannot allocate memory.");

  WWScreen_SetNumber(screen, number);
  WWScreen_SetWidth( screen, width);
  WWScreen_SetHeight(screen, height);
  WWScreen_SetRollX( screen, 0);
  WWScreen_SetRollY( screen, 0);

  WWScreen_SetEnable(screen, 1);
  WWScreen_SetMode(  screen, WW_SCREEN_DRAW_ALL);

  WWScreen_SetDrawX( screen, draw_x);
  WWScreen_SetDrawY( screen, draw_y);
  WWScreen_SetDrawWidth( screen, draw_width);
  WWScreen_SetDrawHeight(screen, draw_height);

  screen->screen_characters =
    (WWScreenCharacter *)malloc(sizeof(WWScreenCharacter) *
				screen->width * screen->height);

  for (y = 0; y < screen->height; y++) {
    for (x = 0; x < screen->width; x++) {
      sc = WWScreenCharacter_Create(0, 0, initial_palette, initial_character);
      WWScreen_SetScreenCharacter(screen, x, y, sc);
    }
  }

  return (screen);
}

WWScreen WWScreen_Destroy(WWScreen screen)
{
  int x, y;
  WWScreenCharacter sc;

  if (screen == NULL)
    WonX_Error("WWScreen_Destroy", "Object is not created.");

  for (y = 0; y < screen->height; y++) {
    for (x = 0; x < screen->width; x++) {
      sc = WWScreen_GetScreenCharacter(screen, x, y);
      WWScreen_SetScreenCharacter(screen, x, y, WWScreenCharacter_Destroy(sc));
    }
  }

  if (screen->screen_characters) free(screen->screen_characters);

  free(screen);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
