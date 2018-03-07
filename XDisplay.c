/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "XDisplayP.h"
#include "Wonx.h"
#include "etc.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

unsigned int XDisplay_GetKeyPress(XDisplay d) { return (d->key_press); }
int XDisplay_GetLCDDraw(XDisplay d) { return (d->lcd_draw); }

int XDisplay_GetColorMapPrint(XDisplay d) {return (d->color_map_print); }
int XDisplay_GetPalettePrint(XDisplay d) {return (d->palette_print); }
int XDisplay_GetCharacterPrint(XDisplay d) {return (d->character_print); }
int XDisplay_GetSpritePrint(XDisplay d) {return (d->sprite_print); }

int XDisplay_SetColorMapPrint(XDisplay d, int f)
{ return (d->color_map_print = f); }
int XDisplay_SetPalettePrint(XDisplay d, int f)
{ return (d->palette_print = f); }
int XDisplay_SetCharacterPrint(XDisplay d, int f)
{ return(d->character_print = f); }
int XDisplay_SetSpritePrint(XDisplay d, int f)
{ return (d->sprite_print = f); }

/*****************************************************************************/
/* �����ǻ��Ѥ���ؿ��ʤɤ����                                              */
/*****************************************************************************/

#if 0
static XrmOptionDescRec options[] = {};
#endif

static Atom wm_delete_window;

static void die(Widget w)
{
  kill(getpid(), SIGINT);
}

static void quit(Widget w, XEvent * event, String * params, Cardinal * num)
{
  die(w);
}

static void wm_protocols_proc(Widget w, XEvent * event, String * params,
			      Cardinal * num)
{
  if ((event->type == ClientMessage) &&
      (event->xclient.data.l[0] != wm_delete_window)) {
    XBell(XtDisplay(w), 0);
  } else {
    die(w);
  }
}

static void iconify(Widget w, XEvent * event, String * params, Cardinal * num)
{
  XIconifyWindow(XtDisplay(w), XtWindow(w), DefaultScreen(XtDisplay(w)));
}

static void sleep_3(Widget w, XEvent * event, String * params, Cardinal * num)
{
  time_t old_t;
  time_t t;
  int i;
  /* UNIXTimer.c ������ SIGALRM ����Ѥ��Ƥ���Τǡ�sleep() �ϻ��ѤǤ��ʤ� */
#if 0
  sleep(3);
#else
  for (i = 0; i < 3; i++) {
    time(&t);
    old_t = t;
    while (t == old_t)
      time(&t);
  }
#endif
}

static XtActionsRec actions[] = {
  {"quit", quit},
  {"wm_protocols_proc", wm_protocols_proc},
  {"iconify", iconify},
  {"pause", sleep_3}
};

static char * translations =
"<Message>WM_PROTOCOLS: wm_protocols_proc()\n"
"None<Key>p: pause()\n"
"Ctrl<Key>i: iconify()\n"
"Ctrl<Key>c: quit()\n"
"None<Key>q: quit()";

/*===========================================================================*/
/* ��̾����ԥ������ͤ��������                                              */
/*===========================================================================*/

static unsigned long XDisplay_GetPixelFromColorName(XDisplay x_display,
						    char * color_name)
{
  XColor c0, c1;
  XAllocNamedColor(x_display->display, x_display->colormap, color_name,
		   &c0, &c1);
  return (c0.pixel);
}

/*===========================================================================*/
/* ���٥�ȥϥ�ɥ�                                                          */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* �����β���                                                                */
/*---------------------------------------------------------------------------*/

static void KeyHandler(Widget w, XtPointer p, XEvent * event,
		       Boolean * dispatch)
{
  XDisplay x_display = (XDisplay)p;
  KeySym key_sym;
  int press = 0;

  if ((event->type == KeyPress) || (event->type == KeyRelease)) {

    key_sym = XKeycodeToKeysym(x_display->display, event->xkey.keycode, 0);

    switch (key_sym) {

      /* WonderSwan�� */
    case XK_Up      : press = KEY_UP1;    break;
    case XK_Right   : press = KEY_RIGHT1; break;
    case XK_Down    : press = KEY_DOWN1;  break;
    case XK_Left    : press = KEY_LEFT1;  break;
    case XK_i       : press = KEY_UP2;    break;
    case XK_l       : press = KEY_RIGHT2; break;
    case XK_k       : press = KEY_DOWN2;  break;
    case XK_j       : press = KEY_LEFT2;  break;
    case XK_s       : press = KEY_START;  break;
    case XK_space   : press = KEY_A;      break;
    case XK_Shift_L : press = KEY_B;      break;
    default         : press = 0;          break;
    }

    /* Wonx ����� */
    if (event->type == KeyPress) {

      switch (key_sym) {

	/* ɽ���⡼���ѹ� */
      case XK_p       :
	x_display->lcd_draw = !(x_display->lcd_draw);
	if (x_display->lcd_draw)
	  WonxDisplay_Flush(Wonx_GetWonxDisplay());
	break;

	/* �ǡ����Υ������� */
      case XK_F1       : x_display->color_map_print = 1; break;
      case XK_F2       : x_display->palette_print = 1; break;
      case XK_F3       : x_display->character_print = 1; break;
      case XK_F4       : x_display->sprite_print = 1; break;
      }
    }

    if (press) {
      if (event->type == KeyPress) x_display->key_press |=  press;
      else                         x_display->key_press &= ~press;
    }
  }

  return;
}

/*---------------------------------------------------------------------------*/
/* �������ݡ���                                                              */
/*---------------------------------------------------------------------------*/

static void ExposeHandler(Widget w, XtPointer p, XEvent * event,
			  Boolean * dispatch)
{
  XDisplay x_display = (XDisplay)p;

  XCopyArea(x_display->display, x_display->lcd_pixmap,
	    x_display->lcd_window, x_display->copy_gc,
            0, 0, x_display->width, x_display->height, 0, 0);
  return;
}

/*---------------------------------------------------------------------------*/
/* �ޥ�����������ɥ���Υ�줿�顤��������������                            */
/*---------------------------------------------------------------------------*/

static void LeaveWindowHandler(Widget w, XtPointer p, XEvent * event,
			       Boolean * dispatch)
{
  XDisplay x_display = (XDisplay)p;
  x_display->key_press = 0;
  return;
}

/*===========================================================================*/
/* ���֥������Ȥ������Ⱦõ�                                                  */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥ�����                                                        */
/*---------------------------------------------------------------------------*/

XDisplay XDisplay_Create(int width, int height)
{
  XDisplay x_display;
  int argc = 0;
  char ** argv = NULL;
  XColor color;
  char * color_name[] = {"white", "gray84", "gray78", "gray72",
			 "gray66", "gray60", "gray54", "gray48",
			 "gray42", "gray36", "gray30", "gray24",
			 "gray18", "gray12", "gray6", "black"};
  int i;

  x_display = (XDisplay)malloc(sizeof(_XDisplay));
  if (x_display == NULL)
    Wonx_Error("XDisplay_Create", "Cannot allocate memory.");

  x_display->width = width;
  x_display->height = height;

  x_display->toplevel = XtAppInitialize(&(x_display->app_context),
					"Wonx",
					NULL, 0, &argc, argv, NULL, NULL, 0);

  XtVaSetValues(x_display->toplevel, XtNinput, True, NULL);
  XtVaSetValues(x_display->toplevel, XtNtitle, "Wonx", NULL);
  XtVaSetValues(x_display->toplevel, XtNwidth    , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNminWidth , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNmaxWidth , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNheight   , x_display->height, NULL);
  XtVaSetValues(x_display->toplevel, XtNminHeight, x_display->height, NULL);
  XtVaSetValues(x_display->toplevel, XtNmaxHeight, x_display->height, NULL);

  x_display->key_press = 0;
  x_display->lcd_draw = 1;

  XtRealizeWidget(x_display->toplevel);
  while (!XtIsRealized(x_display->toplevel)) { /* None */ }

  x_display->display = XtDisplay(x_display->toplevel);
  x_display->root_window = DefaultRootWindow(x_display->display);
  x_display->lcd_window = XtWindow(x_display->toplevel);
  x_display->colormap = DefaultColormap(x_display->display,
					DefaultScreen(x_display->display));
  x_display->depth = DefaultDepth(x_display->display,
				  DefaultScreen(x_display->display));

  x_display->lcd_pixmap = XCreatePixmap(x_display->display,
					x_display->lcd_window,
					x_display->width,
					x_display->height,
					x_display->depth);

  x_display->copy_gc = XCreateGC(x_display->display, x_display->lcd_window,
				 0, 0);
  XSetFunction(x_display->display, x_display->copy_gc, GXcopy);

  for (i = 0; i < 16; i++) {
    XParseColor(x_display->display, x_display->colormap,
		color_name[i], &color); /* ����̾�� �� RGB��*/
    XAllocColor(x_display->display, x_display->colormap,
		&color); /* ������ݤ����ԥ������ͤ����� */
    x_display->color_gc[i] = XCreateGC(x_display->display,
				       x_display->lcd_window, 0, 0);
    XSetForeground(x_display->display, x_display->color_gc[i], color.pixel);
    XSetFunction(x_display->display, x_display->color_gc[i], GXcopy);
  }

  /* �ե���Ȥγ��� */
  x_display->font = XLoadFont(x_display->display, "8x16");
  x_display->font_gc = XCreateGC(x_display->display,
				 x_display->lcd_window, 0, 0);
  XSetFont(x_display->display, x_display->font_gc, x_display->font);
  XSetFunction(x_display->display, x_display->font_gc, GXcopy);
  XSetForeground(x_display->display, x_display->font_gc,
		 XDisplay_GetPixelFromColorName(x_display, "white"));
  XSetBackground(x_display->display, x_display->font_gc,
		 XDisplay_GetPixelFromColorName(x_display, "black"));

  XFillRectangle(x_display->display, x_display->lcd_window,
		 x_display->color_gc[0],
		 0, 0, x_display->width, x_display->height);

  /* ���٥�ȥϥ�ɥ����Ͽ */
  XtAddEventHandler(x_display->toplevel, KeyPressMask | KeyReleaseMask,
                    False, KeyHandler, x_display);
  XtAddEventHandler(x_display->toplevel, ExposureMask,
                    False, ExposeHandler, x_display);
  XtAddEventHandler(x_display->toplevel, LeaveWindowMask | FocusChangeMask,
                    False, LeaveWindowHandler, x_display);

  /* ������������� */
#if 0
  XtVaSetValues(x_display->toplevel, XtNiconPixmap,
		x_display->icon_pixmap, NULL);
  XtVaSetValues(x_display->toplevel, XtNiconMask  ,
		x_display->icon_mask  , NULL);
#endif

  /* �������������� */
  XtAppAddActions(x_display->app_context, actions, XtNumber(actions));

  /* �ȥ�󥹥졼���������� */
  XtOverrideTranslations(x_display->toplevel,
                         XtParseTranslationTable(translations));

  /* ������ɥ��ޥ͡����㤫��� f.delete �ؤ��б� */
  wm_delete_window = XInternAtom(x_display->display,
				 "WM_DELETE_WINDOW", False);
  XSetWMProtocols(x_display->display, x_display->lcd_window,
		  &wm_delete_window, 1);

  /* X�����Ф�Ʊ����Ȥ� */
  /* True ���ȡ����٥�ȥ��塼��Υ��٥�Ȥ��Ѵ����� */
  XSync(x_display->display, True);

  return (x_display);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥξõ�                                                        */
/*---------------------------------------------------------------------------*/

XDisplay XDisplay_Destroy(XDisplay x_display)
{
  int i;

  if (x_display == NULL) return (NULL);

  /* ���Ȥǥ꥽�����β������ɲä��뤳�� */
  if (x_display->color_gc != NULL) {
    for (i = 0; i < 16; i++) {
      if (x_display->color_gc[i])
	XFreeGC(x_display->display, x_display->color_gc[i]);
      x_display->color_gc[i] = 0;
    }
  }

  free(x_display);

  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* X�����ФȤ�Ʊ��                                                           */
/*---------------------------------------------------------------------------*/

int XDisplay_Sync(XDisplay x_display)
{
  XEvent event;

  XFlush(x_display->display);

  /* X�����Ф�Ʊ����Ȥ� */
  /* False ���ȡ����٥�ȥ��塼��Υ��٥�Ȥ��Ѵ����ʤ� */
  XSync(x_display->display, False);

  /* ���٥�Ȥν��� */
  while (XtAppPending(x_display->app_context)) {
    XtAppNextEvent(x_display->app_context, &event);
    XtDispatchEvent(&event);
  }

  return (0);
}

/*---------------------------------------------------------------------------*/
/* ����                                                                      */
/*---------------------------------------------------------------------------*/

int XDisplay_DrawLCDWindow(XDisplay x_display, WWLCDPanel ww_lcd_panel)
{
  int x, y;
  int px, py, ph;
  int num;
  int n[16];
  XRectangle * rectangles[16];
  int pixel;
  int ww_lcd_width, ww_lcd_height;

  /* ���ܤ��Ƥ���ԥ�����ϤޤȤ�����褹��Τǡ��ԥ�������κ����ͤ� */
  /* �ǰ��ξ��(�ʡ����ͤΤȤ�)�ǡ�width * height / 2 �ˤʤ롥        */
  num =
    WWLCDPanel_GetHeight(ww_lcd_panel) * WWLCDPanel_GetWidth(ww_lcd_panel) / 2;

  /*
   * ���� malloc() �ϡ��ºݤˤϥ���ϤۤȤ�ɻ��Ѥ���Ƥ��ʤ��Τǡ�
   * ���Τ����ʤ�Ȥ�����ɬ�פ�����
   */
  for (pixel = 0; pixel < 16; pixel++) {
    n[pixel] = 0;
    rectangles[pixel] = (XRectangle *)malloc(sizeof(XRectangle) * num);
  }
  if (rectangles == NULL)
    Wonx_Error("XDisplay_DrawLCDWindow", "Cannot allocate memory.");

  ww_lcd_width  = WWLCDPanel_GetWidth( ww_lcd_panel);
  ww_lcd_height = WWLCDPanel_GetHeight(ww_lcd_panel);

  /* �����ν����ϥۥåȥ��ݥåȤˤʤ�Τǡ��Τ��Τ��˥��塼�˥󥰤��뤳�� */

  for (y = 0; y < ww_lcd_height; y++) {
    py = (y * x_display->height) / ww_lcd_height;
    ph = (y+1) * x_display->height / ww_lcd_height- py;
    for (x = 0; x < ww_lcd_width; x++) {
      if (!WWLCDPanel_IsPixelChanged(ww_lcd_panel, x, y)) {
	continue;
      }
      pixel = WWLCDPanel_GetPixel(ww_lcd_panel, x, y);
      px = (x * x_display->width ) / ww_lcd_width;
      rectangles[pixel][n[pixel]].x = px;
      rectangles[pixel][n[pixel]].y = py;
      rectangles[pixel][n[pixel]].width  =
	(x+1) * x_display->width  / ww_lcd_width - px;
      rectangles[pixel][n[pixel]].height = ph;

      /* ���ܤ��Ƥ�Ʊ���Υԥ�����ϡ����Ϥ��ä�������褹�� */
      x++;
      while ( (x < ww_lcd_width) &&
	      (pixel == WWLCDPanel_GetPixel(ww_lcd_panel, x, y)) &&
	      (WWLCDPanel_IsPixelChanged(ww_lcd_panel, x, y)) ) {
	rectangles[pixel][n[pixel]].width =
	  (x+1) * x_display->width / ww_lcd_width - px;
	x++;
      }
      x--;

      n[pixel]++;
    }
  }

  for (pixel = 0; pixel < 16; pixel++) {
    if (n[pixel] > 0) {
      XFillRectangles(x_display->display,
		      x_display->lcd_pixmap,
		      x_display->color_gc[pixel],
		      rectangles[pixel], n[pixel]);
    }
  }

  XCopyArea(x_display->display, x_display->lcd_pixmap,
	    x_display->lcd_window, x_display->copy_gc,
            0, 0, x_display->width, x_display->height, 0, 0);

  WWLCDPanel_ResetAllDraw(ww_lcd_panel);
  WWLCDPanel_ReverseCurrent(ww_lcd_panel);

  XDisplay_Sync(x_display);

  for (pixel = 0; pixel < 16; pixel++) {
    free(rectangles[pixel]);
  }

  return (0);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
