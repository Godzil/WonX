#include <stdio.h>

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "XDisplayP.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

unsigned int XDisplay_GetKeyPress(XDisplay x_display)
{ return (x_display->key_press); }
int XDisplay_GetLCDDraw(XDisplay x_display)
{ return (x_display->lcd_draw); }

/*****************************************************************************/
/* 内部で使用する関数などの定義                                              */
/*****************************************************************************/

static XrmOptionDescRec options[] = {};
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

static void pause(Widget w, XEvent * event, String * params, Cardinal * num)
{
  sleep(3);
}

static XtActionsRec actions[] = {
  {"quit", quit},
  {"wm_protocols_proc", wm_protocols_proc},
  {"iconify", iconify},
  {"pause", pause}
};

static char * translations =
"<Message>WM_PROTOCOLS: wm_protocols_proc()\n"
"None<Key>p: pause()\n"
"Ctrl<Key>i: iconify()\n"
"Ctrl<Key>c: quit()\n"
"None<Key>q: quit()";

/*===========================================================================*/
/* 色名からピクセル値を取得する                                              */
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
/* イベントハンドラ                                                          */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* キーの押下                                                                */
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

      /* WonderSwan用 */
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

      /* Wonx 操作用 */

      /* 表示モード変更 */
    case XK_p       :
      press = 0;
      if (event->type == KeyPress)
	x_display->lcd_draw = !(x_display->lcd_draw);
      break;

    default :         press = 0;          break;
    }

    if (press) {
      if (event->type == KeyPress) x_display->key_press |=  press;
      else                         x_display->key_press &= ~press;
    }
  }

  return;
}

/*---------------------------------------------------------------------------*/
/* イクスポーズ                                                              */
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
/* マウスがウインドウを離れたら，キーを初期化する                            */
/*---------------------------------------------------------------------------*/

static void LeaveWindowHandler(Widget w, XtPointer p, XEvent * event,
			       Boolean * dispatch)
{
  XDisplay x_display = (XDisplay)p;
  x_display->key_press = 0;
  return;
}

/*===========================================================================*/
/* オブジェクトの生成と消去                                                  */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの生成                                                        */
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
  if (x_display == NULL) Error("XDisplay_Create", "Cannot allocate memory.");

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
		color_name[i], &color); /* 色の名前 → RGB値*/
    XAllocColor(x_display->display, x_display->colormap,
		&color); /* 色を確保し，ピクセル値を得る */
    x_display->color_gc[i] = XCreateGC(x_display->display,
				       x_display->lcd_window, 0, 0);
    XSetForeground(x_display->display, x_display->color_gc[i], color.pixel);
    XSetFunction(x_display->display, x_display->color_gc[i], GXcopy);
  }

  /* フォントの確保 */
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

  /* イベントハンドラの登録 */
  XtAddEventHandler(x_display->toplevel, KeyPressMask | KeyReleaseMask,
                    False, KeyHandler, x_display);
  XtAddEventHandler(x_display->toplevel, ExposureMask,
                    False, ExposeHandler, x_display);
  XtAddEventHandler(x_display->toplevel, LeaveWindowMask | FocusChangeMask,
                    False, LeaveWindowHandler, x_display);

  /* アイコンの設定 */
#if 0
  XtVaSetValues(x_display->toplevel, XtNiconPixmap,
		x_display->icon_pixmap, NULL);
  XtVaSetValues(x_display->toplevel, XtNiconMask  ,
		x_display->icon_mask  , NULL);
#endif

  /* アクションの設定 */
  XtAppAddActions(x_display->app_context, actions, XtNumber(actions));

  /* トランスレーションの設定 */
  XtOverrideTranslations(x_display->toplevel,
                         XtParseTranslationTable(translations));

  /* ウィンドウマネージャからの f.delete への対応 */
  wm_delete_window = XInternAtom(x_display->display,
				 "WM_DELETE_WINDOW", False);
  XSetWMProtocols(x_display->display, x_display->lcd_window,
		  &wm_delete_window, 1);

  /* Xサーバと同期をとる */
  /* True だと，イベントキュー内のイベントを廃棄する */
  XSync(x_display->display, True);

  return (x_display);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの消去                                                        */
/*---------------------------------------------------------------------------*/

XDisplay XDisplay_Destroy(XDisplay x_display)
{
  int i;

  if (x_display == NULL) return (NULL);

  /* あとでリソースの解放を追加すること */
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
/* Xサーバとの同期                                                           */
/*---------------------------------------------------------------------------*/

int XDisplay_Sync(XDisplay x_display)
{
  XEvent event;

  XFlush(x_display->display);

  /* Xサーバと同期をとる */
  /* False だと，イベントキュー内のイベントを廃棄しない */
  XSync(x_display->display, False);

  /* イベントの処理 */
  while (XtAppPending(x_display->app_context)) {
    XtAppNextEvent(x_display->app_context, &event);
    XtDispatchEvent(&event);
  }

  return (0);
}

/*---------------------------------------------------------------------------*/
/* 描画                                                                      */
/*---------------------------------------------------------------------------*/

int XDisplay_DrawLCDWindow(XDisplay x_display, WWLCDPanel ww_lcd_panel)
{
  int x, y, n;
  int px, py;
  int num;
  XRectangle * rectangles;
  int pixel;
  int ww_lcd_width, ww_lcd_height;

  num =
    WWLCDPanel_GetHeight(ww_lcd_panel) * WWLCDPanel_GetWidth(ww_lcd_panel);
  rectangles = (XRectangle *)malloc(sizeof(XRectangle) * num);
  if (rectangles == NULL)
    Error("XDisplay_DrawLCDWindow", "Cannot allocate memory.");

  ww_lcd_width  = WWLCDPanel_GetWidth( ww_lcd_panel);
  ww_lcd_height = WWLCDPanel_GetHeight(ww_lcd_panel);

  /* ここの処理はホットスポットになるので，のちのちにチューニングすること */

  for (pixel = 0; pixel < 16; pixel++) {
    n = 0;
    for (y = 0; y < ww_lcd_height; y++) {
      for (x = 0; x < ww_lcd_width; x++) {
	if (pixel == WWLCDPanel_GetPixel(ww_lcd_panel, x, y)) {
	  px = (x * x_display->width ) / ww_lcd_width;
	  py = (y * x_display->height) / ww_lcd_height;
	  rectangles[n].x = px;
	  rectangles[n].y = py;
	  rectangles[n].width  = (x+1) * x_display->width  / ww_lcd_width - px;
	  rectangles[n].height = (y+1) * x_display->height / ww_lcd_height- py;
	  n++;
	}
      }
    }

    if (n > 0) {
      XFillRectangles(x_display->display,
		      x_display->lcd_pixmap,
		      x_display->color_gc[pixel],
		      rectangles, n);
    }
  }

  XCopyArea(x_display->display, x_display->lcd_pixmap,
	    x_display->lcd_window, x_display->copy_gc,
            0, 0, x_display->width, x_display->height, 0, 0);

  XDisplay_Sync(x_display);

  free(rectangles);

  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
