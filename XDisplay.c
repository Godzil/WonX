/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "XDisplayP.h"
#include "WonX.h"
#include "WonXDisplay.h"
#include "etc.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

Display * XDisplay_GetDisplay(XDisplay d) { return (d->display); }
Colormap XDisplay_GetColormap(XDisplay d) { return (d->colormap); }

XColorGCDatabase XDisplay_GetColorGCDatabase(XDisplay x_display)
{ return (x_display->color_gc_database); }

unsigned int XDisplay_GetKeyPress(XDisplay d) { return (d->key_press); }

int XDisplay_GetLCDDrawLevel(XDisplay d) { return (d->lcd_draw_level); }
int XDisplay_SetLCDDrawLevel(XDisplay d, int level)
{
  d->lcd_draw_level = level;
  WonXDisplay_Flush(WonX_GetWonXDisplay());
  return (d->lcd_draw_level);
}
int XDisplay_LCDDrawLevelDown(XDisplay d)
{ return (XDisplay_SetLCDDrawLevel(d, d->lcd_draw_level - 1)); }
int XDisplay_LCDDrawLevelUp(  XDisplay d)
{ return (XDisplay_SetLCDDrawLevel(d, d->lcd_draw_level + 1)); }

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
/* 内部で使用する関数などの定義                                              */
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

static void sleep_10(Widget w, XEvent * event, String * params, Cardinal * num)
{
  time_t old_t;
  time_t t;
  int i;
  /* UNIXTimer.c 内部で SIGALRM を使用しているので，sleep() は使用できない */
#if 0
  sleep(10);
#else
  for (i = 0; i < 10; i++) {
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
  {"pause", sleep_10}
};

static char * translations =
"<Message>WM_PROTOCOLS: wm_protocols_proc()\n"
"None<Key>F11: pause()\n"
"Ctrl<Key>i: iconify()\n"
"Ctrl<Key>c: quit()\n"
"None<Key>F12: quit()\n"
"None<Key>q: quit()";

/*===========================================================================*/
/* 色名からピクセル値を取得する                                              */
/*===========================================================================*/

#ifdef USE_X_FONT
static unsigned long XDisplay_GetPixelFromColorName(XDisplay x_display,
						    char * color_name)
{
  XColor c0, c1;
  XAllocNamedColor(x_display->display, x_display->colormap, color_name,
		   &c0, &c1);
  return (c0.pixel);
}
#endif

/*===========================================================================*/
/* イベントハンドラ                                                          */
/*===========================================================================*/

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
    case XK_Up      : press = KEY_UP1;    printf("key : Up1 "   ); break;
    case XK_Right   : press = KEY_RIGHT1; printf("key : Right1 "); break;
    case XK_Down    : press = KEY_DOWN1;  printf("key : Down1 " ); break;
    case XK_Left    : press = KEY_LEFT1;  printf("key : Left1 " ); break;
    case XK_i       : press = KEY_UP2;    printf("key : Up2 "   ); break;
    case XK_l       : press = KEY_RIGHT2; printf("key : Right2 "); break;
    case XK_k       : press = KEY_DOWN2;  printf("key : Down2 " ); break;
    case XK_j       : press = KEY_LEFT2;  printf("key : Left2 " ); break;
    case XK_s       : press = KEY_START;  printf("key : Start " ); break;
    case XK_space   : press = KEY_A;      printf("key : A "     ); break;
    case XK_Shift_L : press = KEY_B;      printf("key : B "     ); break;
    default         : press = 0;          break;
    }

    if (press) {
      if (event->type == KeyPress) {
	x_display->key_press |=  press;
	printf("Pressed\n");
      } else {
	x_display->key_press &= ~press;
	printf("Released\n");
      }
    }

    /* WonX 操作用 */
    if (event->type == KeyPress) {

      switch (key_sym) {

	/* 表示モード変更 */
      case XK_F9        :
      case XK_F10       :

	if (key_sym == XK_F9) {
	  printf("key : F9 Pressed\n");
	  printf("lcd_draw_level : down (%d", x_display->lcd_draw_level);
	  (x_display->lcd_draw_level)--;
	  printf(" -> %d)\n", x_display->lcd_draw_level);
	} else {
	  printf("key : F10 Pressed\n");
	  printf("lcd_draw_level : up (%d", x_display->lcd_draw_level);
	  (x_display->lcd_draw_level)++;
	  printf(" -> %d)\n", x_display->lcd_draw_level);
	}

	if (x_display->lcd_draw_level > 0) {
#if 1
	  /*
	   * WonXDisplay_Flush() を実行すると，XDisplay_Flush() が呼ばれて
	   * イベントのディスパッチが行われてしまうため，イベントの処理中に
	   * 別のイベントのディスパッチを行うことになってしまう．
	   * X サーバが，XtDispatchEvent() によるイベントのディスパッチ時に，
	   * イベントキューからイベントを出してからイベントの処理をするような
	   * 実装になっている場合には問題ないが，イベントの処理をした後に
	   * キューからイベントを取り除くような実装になっている場合には，
	   * XtDispatchEvent() によるイベントのディスパッチ中に再び
	   * XtDispatchEvent() が呼ばれたときに，イベントがキューから
	   * 取り除かれることがなく，イベント処理の無限ループに陥ってしまう
	   * 可能性があるかもしれない．
	   * (ちなみに XFree86 では大丈夫なようであるが，いちおう)
	   * このため WonXDisplay_Flush() は呼び出さずに，
	   * WonXDisplay_DrawLCDWindow() でウインドウの描画のみを行うように
	   * WonX-2.2 で修正した．
	   */
	  WonXDisplay_DrawLCDWindow(WonX_GetWonXDisplay());
#elif 1
	  WonXDisplay_Flush(WonX_GetWonXDisplay());
#else
	  ExposeHandler(w, p, event, dispatch);
#endif
	}
	break;

	/* データのダンプ操作 */
      case XK_F1       :
	printf("key : F1 Pressed\n");
	x_display->color_map_print = 1;
	printf("dump : color_map\n");
	break;
      case XK_F2       :
	printf("key : F2 Pressed\n");
	x_display->palette_print   = 1;
	printf("dump : palette\n");
	break;
      case XK_F3       :
	printf("key : F3 Pressed\n");
	x_display->character_print = 1;
	printf("dump : character\n");
	break;
      case XK_F4       :
	printf("key : F4 Pressed\n");
	x_display->sprite_print    = 1;
	printf("dump : sprite\n");
	break;
      }
    }
  }

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
  if (x_display == NULL)
    WonX_Error("XDisplay_Create", "Cannot allocate memory.");

  x_display->width = width;
  x_display->height = height;

  x_display->toplevel = XtAppInitialize(&(x_display->app_context),
					"WonX",
					NULL, 0, &argc, argv, NULL, NULL, 0);

  XtVaSetValues(x_display->toplevel, XtNinput, True, NULL);
  XtVaSetValues(x_display->toplevel, XtNtitle, "WonX", NULL);
  XtVaSetValues(x_display->toplevel, XtNwidth    , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNminWidth , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNmaxWidth , x_display->width , NULL);
  XtVaSetValues(x_display->toplevel, XtNheight   , x_display->height, NULL);
  XtVaSetValues(x_display->toplevel, XtNminHeight, x_display->height, NULL);
  XtVaSetValues(x_display->toplevel, XtNmaxHeight, x_display->height, NULL);

  x_display->key_press = 0;
  x_display->lcd_draw_level = 1;

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

#ifdef USE_X_FONT
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
#endif

  /* GCのデータベース初期化 */
  /*
   * XColorGCDatabase_Create() の後に XCreateGC() で他の GC の生成を行うと，
   * なぜか XFreeGC() するときに Segmentation Fault を起こす
   * (FreeBSD の場合の話．原因不明．他の OS (ていうか正確にはXライブラリ)
   *  では試してない)ので，XColorGCDatabase_Create() はすべての GC を
   * 作成した後に行う必要がある．
   */
  x_display->color_gc_database =
    XColorGCDatabase_Create(x_display,
			    0,       /* studying_flag */
			    1,       /* cache_flag */
			    3,       /* cache_size */
			    256,     /* hash_number */
			    "black", /* background_color */
			    16       /* gradation */);

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

  if (x_display == NULL)
    WonX_Error("XDisplay_Destroy", "Object is not created.");

  /* Xサーバと同期をとる */
  /* True だと，イベントキュー内のイベントを廃棄する */
  XSync(x_display->display, True);

  /* トランスレーションのアンインストール */
  XtUninstallTranslations(x_display->toplevel);

  /* アクションの削除 */
#if 0
  /*
   * 一度登録したアクションを削除することはできない．
   * (同じアクション名で新しいアクションを登録して，上書きすることはできる)
   */
#endif

  /* アイコンの削除 */
#if 0
  /* アイコンの削除処理が必要な場合にはここに書く．現状では必要無し */
#endif

  /* イベントハンドラの削除 */
  XtRemoveEventHandler(x_display->toplevel, KeyPressMask | KeyReleaseMask,
		       False, KeyHandler, x_display);
  XtRemoveEventHandler(x_display->toplevel, ExposureMask,
		       False, ExposeHandler, x_display);
  XtRemoveEventHandler(x_display->toplevel, LeaveWindowMask | FocusChangeMask,
		       False, LeaveWindowHandler, x_display);

  /* GCのデータベース終了処理 */
  if (x_display->color_gc_database) {
    x_display->color_gc_database =
      XColorGCDatabase_Destroy(x_display->color_gc_database);
  }

#ifdef USE_X_FONT
  /* フォントの解放 */
  if (x_display->font_gc) {
    XFreeGC(x_display->display, x_display->font_gc);
    x_display->font_gc = 0;
  }
  if (x_display->font) {
    XUnloadFont(x_display->display, x_display->font);
    x_display->font = 0;
  }
#endif

  for (i = 0; i < 16; i++) {
    if (x_display->color_gc[i]) {
      XFreeGC(x_display->display, x_display->color_gc[i]);
      x_display->color_gc[i] = 0;
    }
  }

  if (x_display->copy_gc) {
    XFreeGC(x_display->display, x_display->copy_gc);
    x_display->copy_gc = 0;
  }

  if (x_display->lcd_pixmap) {
    XFreePixmap(x_display->display, x_display->lcd_pixmap);
    x_display->lcd_pixmap = 0;
  }

  x_display->key_press = 0;
  x_display->lcd_draw_level = 0;

#if 0
  if (x_display->app_context) {
    XtDestroyApplicationContext(x_display->app_context);
    x_display->app_context = 0;
  }
#endif

  if (x_display->toplevel) {
    XtDestroyWidget(x_display->toplevel);
    x_display->toplevel = 0;
  }

  free(x_display);

  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* Xサーバとの同期                                                           */
/*---------------------------------------------------------------------------*/

int XDisplay_Sync(XDisplay x_display)
{
  XFlush(x_display->display);

  /* Xサーバと同期をとる */
  /* False だと，イベントキュー内のイベントを廃棄しない */
  XSync(x_display->display, False);

  return (0);
}

int XDisplay_Flush(XDisplay x_display)
{
  XEvent event;

  XDisplay_Sync(x_display);

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

int XDisplay_DrawLCDWindow(XDisplay x_display, WWDisplay ww_display,
			   WWLCDPanel ww_lcd_panel)
{
  int x, y;
  int px, py, ph;
  int num;
  int n[16];
  XRectangle rectangle;
  XRectangle * rectangles[16];
  unsigned short int pixel;
  int ww_lcd_width, ww_lcd_height;
  int red, green, blue;
  XColorGCDatabase database;
  XColorGC x_color_gc;
  GC gc;

  ww_lcd_width  = WWLCDPanel_GetWidth( ww_lcd_panel);
  ww_lcd_height = WWLCDPanel_GetHeight(ww_lcd_panel);

  switch (WWDisplay_GetColorMode(ww_display)) {

  case COLOR_MODE_GRAYSCALE:

    /* 隣接しているピクセルはまとめて描画するので，ピクセル数の最大値は */
    /* 最悪の場合(縞々模様のとき)で，width * height / 2 になる．        */
    num =
      WWLCDPanel_GetHeight(ww_lcd_panel) *
      WWLCDPanel_GetWidth(ww_lcd_panel) / 2;

    /*
     * この malloc() は，実際にはメモリはほとんど使用されていないので，
     * そのうちなんとかする必要がある
     */
    for (pixel = 0; pixel < 16; pixel++) {
      n[pixel] = 0;
      rectangles[pixel] = (XRectangle *)malloc(sizeof(XRectangle) * num);
    }
    if (rectangles == NULL)
      WonX_Error("XDisplay_DrawLCDWindow", "Cannot allocate memory.");

    /* ここの処理はホットスポットになるので，のちのちにチューニングすること */

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

	/* 隣接してる同色のピクセルは，極力いっしょに描画する */
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

    for (pixel = 0; pixel < 16; pixel++) {
      free(rectangles[pixel]);
    }

    break;

  case COLOR_MODE_4COLOR:
  case COLOR_MODE_16COLOR:
  case COLOR_MODE_16PACKED:

    database = XDisplay_GetColorGCDatabase(x_display);

    for (y = 0; y < ww_lcd_height; y++) {
      py = (y * x_display->height) / ww_lcd_height;
      ph = (y+1) * x_display->height / ww_lcd_height- py;
      for (x = 0; x < ww_lcd_width; x++) {
	if (!WWLCDPanel_IsPixelChanged(ww_lcd_panel, x, y)) {
	  continue;
	}
	pixel = WWLCDPanel_GetPixel(ww_lcd_panel, x, y);
	px = (x * x_display->width ) / ww_lcd_width;
	rectangle.x = px;
	rectangle.y = py;
	rectangle.width  = (x+1) * x_display->width  / ww_lcd_width - px;
	rectangle.height = ph;

	/* 隣接してる同色のピクセルは，極力いっしょに描画する */
	x++;
	while ( (x < ww_lcd_width) &&
		(pixel == WWLCDPanel_GetPixel(ww_lcd_panel, x, y)) &&
		(WWLCDPanel_IsPixelChanged(ww_lcd_panel, x, y)) ) {
	  rectangle.width =
	    (x+1) * x_display->width / ww_lcd_width - px;
	  x++;
	}
	x--;

	red   = (pixel >> 8) & 0xf;
	green = (pixel >> 4) & 0xf;
	blue  = (pixel >> 0) & 0xf;

	red   = (red   == 15) ? 65535 : red   * 4096;
	green = (green == 15) ? 65535 : green * 4096;
	blue  = (blue  == 15) ? 65535 : blue  * 4096;

	x_color_gc = XColorGC_CreateFromRGB(database, red, green, blue);
	gc = XColorGC_GetGC(x_color_gc);

	XFillRectangle(x_display->display,
		       x_display->lcd_pixmap,
		       gc,
		       rectangle.x,
		       rectangle.y,
		       rectangle.width,
		       rectangle.height);
	XColorGC_Destroy(x_color_gc);
      }
    }

    break;

  default:
    WonX_Error("XDisplay_DrawLCDWindow", "Unknown color mode.");
  }

  XCopyArea(x_display->display, x_display->lcd_pixmap,
	    x_display->lcd_window, x_display->copy_gc,
	    0, 0, x_display->width, x_display->height, 0, 0);

  WWLCDPanel_ResetAllDraw(ww_lcd_panel);
  WWLCDPanel_ReverseCurrent(ww_lcd_panel);

  XDisplay_Sync(x_display);

  return (0);
}

/*---------------------------------------------------------------------------*/
/* GC の作成                                                                 */
/*---------------------------------------------------------------------------*/

GC XDisplay_CreateGC(XDisplay x_display)
{
  GC gc;
  gc = XCreateGC(x_display->display, x_display->lcd_window, 0, 0);
  return (gc);
}

/*---------------------------------------------------------------------------*/
/* GC の解放                                                                 */
/*---------------------------------------------------------------------------*/

int XDisplay_DestroyGC(XDisplay x_display, GC gc)
{
  XFreeGC(x_display->display, gc);
  return (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
