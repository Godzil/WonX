/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWScreenP.h"

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
    Error("WWScreenCharacter", "Cannot allocate memory.");

  WWScreenCharacter_SetHorizontal(screen_character, horizontal);
  WWScreenCharacter_SetVertical(screen_character, vertical);
  WWScreenCharacter_SetPalette(screen_character, palette);
  WWScreenCharacter_SetCharacter(screen_character, character);

  return (screen_character);
}

static WWScreenCharacter WWScreenCharacter_Destroy(WWScreenCharacter
						   screen_character)
{
  if (screen_character == NULL) return (NULL);
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

int WWScreen_GetNumber(WWScreen s) { return (s->number); }
int WWScreen_GetHorizontal(WWScreen s, int x, int y)
{ return (WWScreen_GetScreenCharacter(s, x, y)->horizontal); }
int WWScreen_GetVertical(WWScreen s, int x, int y)
{ return (WWScreen_GetScreenCharacter(s, x, y)->vertical); }
WWPalette WWScreen_GetPalette(WWScreen s, int x, int y)
{ return (WWScreen_GetScreenCharacter(s, x, y)->palette); }
WWCharacter WWScreen_GetCharacter(WWScreen s, int x, int y)
{ return (WWScreen_GetScreenCharacter(s, x, y)->character); }

int WWScreen_SetNumber(WWScreen s, int n) { return (s->number = n); }
int WWScreen_SetHorizontal(WWScreen s, int x, int y, int f)
{ return (WWScreen_GetScreenCharacter(s, x, y)->horizontal = f); }
int WWScreen_SetVertical(WWScreen s, int x, int y, int f)
{ return (WWScreen_GetScreenCharacter(s, x, y)->vertical = f); }
WWPalette WWScreen_SetPalette(WWScreen s, int x, int y, WWPalette palette)
{ return (WWScreen_GetScreenCharacter(s, x, y)->palette = palette); }
WWCharacter WWScreen_SetCharacter(WWScreen s, int x, int y, WWCharacter c)
{ return (WWScreen_GetScreenCharacter(s, x, y)->character = c); }

int WWScreen_GetWidth( WWScreen s) { return (s->width ); }
int WWScreen_GetHeight(WWScreen s) { return (s->height); }
int WWScreen_GetRollX( WWScreen s) { return (s->roll_x); }
int WWScreen_GetRollY( WWScreen s) { return (s->roll_y); }

int WWScreen_SetWidth( WWScreen s, int n) { return (s->width  = n); }
int WWScreen_SetHeight(WWScreen s, int n) { return (s->height = n); }
int WWScreen_SetRollX( WWScreen s, int r) { return (s->roll_x = r); }
int WWScreen_SetRollY( WWScreen s, int r) { return (s->roll_y = r); }

/* ���顼�ޥåפο�(0��7)���֤�(Ʃ������-1���֤�) */
int WWScreen_GetPixel(WWScreen screen, int x, int y)
{
  int cx, cy, px, py;
  int pixel;
  WWCharacter character;
  WWPalette palette;

  /* x,y ��ɸ���ϰϳ��ΤȤ��ϡ������륪���С����� */
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
  palette = WWScreen_GetPalette(screen, cx, cy);

  pixel = WWCharacter_GetPixel(character, px, py);
  pixel = WWPalette_GetMappedColor(palette, pixel);

  return (pixel);
}

WWScreen WWScreen_Create(int number, int width, int height,
			 WWPalette initial_palette,
			 WWCharacter initial_character)
{
  WWScreen screen;
  WWScreenCharacter sc;
  int x, y;

  screen = (WWScreen)malloc(sizeof(_WWScreen));
  if (screen == NULL) Error("WWScreen_Create", "Cannot allocate memory.");

  WWScreen_SetNumber(screen, number);
  WWScreen_SetWidth( screen, width);
  WWScreen_SetHeight(screen, height);
  WWScreen_SetRollX( screen, 0);
  WWScreen_SetRollY( screen, 0);

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

  if (screen == NULL) return (NULL);

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