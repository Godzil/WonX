/*****************************************************************************/
/* XColorGC GCと色の管理・問い合わせ用のライブラリ                           */
/*****************************************************************************/

#include "XColorGCP.h"

#include "WonX.h"

#include <string.h>

/*===========================================================================*/
/* XColorGCInstance 関連                                                     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCInstance_Create(XDisplay x_display,
						XColor color)
{
  XColorGCInstance instance;

  instance = (XColorGCInstance)malloc(sizeof(_XColorGCInstance));
  if (instance == NULL)
    WonX_Error("XColorGCInstance_Create", "Cannot allocate memory");

  instance->x_display = x_display;
  instance->color = color;

  XAllocColor(XDisplay_GetDisplay(instance->x_display),
	      XDisplay_GetColormap(instance->x_display),
	      &(instance->color));

  /* XAllocColor で instance->color.red などの内容が変わってしまうので，   */
  /* もとに戻す．でないと，あとで同じ色をRGB値で検索しても，違った色として */
  /* 解釈されてしまい，検索できないので，色情報を保存する意味が無くなって  */
  /* しまう．                                                              */
  instance->color.red   = color.red;
  instance->color.green = color.green;
  instance->color.blue  = color.blue;

  instance->gc = XDisplay_CreateGC(instance->x_display);

  XSetForeground(XDisplay_GetDisplay(instance->x_display), instance->gc,
		 instance->color.pixel);
  XSetBackground(XDisplay_GetDisplay(instance->x_display), instance->gc,
		 instance->color.pixel);

  return (instance);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCInstance_Destroy(XColorGCInstance instance)
{
  unsigned long pixel;

  if (instance == NULL) return (NULL);
  if (instance->gc) XDisplay_DestroyGC(instance->x_display, instance->gc);
  pixel = instance->color.pixel;
  XFreeColors(XDisplay_GetDisplay(instance->x_display),
	      XDisplay_GetColormap(instance->x_display),
	      &pixel, 1, 0);
  free(instance);
  return (NULL);
}

/*===========================================================================*/
/* XColorGCList 関連                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの作成                                                        */
/*---------------------------------------------------------------------------*/

static XColorGCList XColorGCList_Create(XDisplay x_display, int studying_flag)
{
  XColorGCList list;

  list = (XColorGCList)malloc(sizeof(_XColorGCList));
  if (list == NULL) WonX_Error("XColorGCList_Create", "Cannot allocate memory");

  list->x_display = x_display;
  list->studying_flag = studying_flag;
  list->list = ObjList_Create();

  return (list);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

static XColorGCList XColorGCList_Destroy(XColorGCList list)
{
  if (list == NULL) return (NULL);

  if (list->list) ObjList_Destroy(list->list);

  free(list);

  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* XColorGCList 中での XColorGCInstance のソート用の比較関数                 */
/*---------------------------------------------------------------------------*/

static int XColorGCInstance_CmpToColor(XColorGCInstance gci, XColor color)
{
  if (gci->color.red   > color.red  ) return ( 1);
  if (gci->color.red   < color.red  ) return (-1);
  if (gci->color.green > color.green) return ( 1);
  if (gci->color.green < color.green) return (-1);
  if (gci->color.blue  > color.blue ) return ( 1);
  if (gci->color.blue  < color.blue ) return (-1);
  return (0);
}

/*---------------------------------------------------------------------------*/
/* リストから XColorGCInstance を得る．                                      */
/* GC の取得要求に対して，GC のリストを検索して返す．                        */
/* 存在しない場合には，作成してリストに追加する．                            */
/* (常に RGB 値でソートされた状態で追加する)                                 */
/* 線形探索なので，O(n^2)で遅くなる．                                        */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCList_GetXColorGCInstance(XColorGCList list,
							 XColor color)
{
  XColorGCInstance instance;
  ObjListData current;
  int cmp;

  for (current = ObjList_GetStart(list->list);
       !ObjList_IsEndEdge(list->list, current);
       current = ObjListData_GetNext(current)) {

    instance = (XColorGCInstance)ObjListData_GetObj(current);
    cmp = XColorGCInstance_CmpToColor(instance, color);

    if (cmp == 0) { /* 見つかれば，それを返す */
#ifdef HIT_LIST
      fprintf(stderr, "S");
#endif
      if (list->studying_flag) ObjList_MoveObjToStart(list->list, current);
      return (instance);
    } else if (cmp > 0) {
      if (!list->studying_flag) break;
    }
  }

  /* 見つからなかった場合は，作成してリストに追加する */
  instance = XColorGCInstance_Create(list->x_display, color);

  if (list->studying_flag)
    ObjList_InsertObjToStart(list->list, instance,
			     (ObjDestructor)XColorGCInstance_Destroy);
  else
    ObjList_InsertObjToPrev(list->list, current, instance,
			    (ObjDestructor)XColorGCInstance_Destroy);

#ifdef HIT_LIST
  fprintf(stderr, "A");
#endif

  return (instance);
}

/*===========================================================================*/
/* XColorGCCache 関連                                                        */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* キャッシュ用バッファ                                                      */
/*---------------------------------------------------------------------------*/

static XColorGCCacheBuffer XColorGCCacheBuffer_Create(XColorGCInstance instance)
{
  XColorGCCacheBuffer buffer;
  buffer = (XColorGCCacheBuffer)malloc(sizeof(_XColorGCCacheBuffer));
  if (buffer == NULL) WonX_Error("XColorGCCacheBuffer_Create",
				 "Cannot allocate memory.");
  buffer->instance = instance;
  return (buffer);
}

static XColorGCCacheBuffer XColorGCCacheBuffer_Destroy(XColorGCCacheBuffer buffer)
{
  if (buffer == NULL) return (NULL);
  free(buffer);
  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* キャッシュ                                                                */
/*---------------------------------------------------------------------------*/

static XColorGCCache XColorGCCache_Create(XColorGCList color_gc_list, int size)
{
  XColorGCCache cache;

  cache = (XColorGCCache)malloc(sizeof(_XColorGCCache));
  if (cache == NULL) WonX_Error("XColorGCCache_Create",
				"Cannot allocate memory.");

  cache->size = size;
  cache->color_gc_list = color_gc_list;
  cache->buffer_list = ObjList_Create();

  return (cache);
}

static XColorGCCache XColorGCCache_Destroy(XColorGCCache cache)
{
  if (cache == NULL) return (NULL);

  if (cache->buffer_list) ObjList_Destroy(cache->buffer_list);
  free(cache);

  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* キャッシュから XColorGCInstance を得る．                                  */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCCache_GetXColorGCInstance(XColorGCCache cache,
							  XColor color)
{
  ObjListData current;
  XColorGCCacheBuffer buffer;
  XColorGCInstance instance;
  int cmp;

  /* キャッシュの中を検索 */
  for (current = ObjList_GetStart(cache->buffer_list);
       !ObjList_IsEndEdge(cache->buffer_list, current);
       current = ObjListData_GetNext(current)) {

    buffer = (XColorGCCacheBuffer)ObjListData_GetObj(current);
    cmp = XColorGCInstance_CmpToColor(buffer->instance, color);

    if (cmp == 0) { /* キャッシュ中に見つけた場合 */
#ifdef HIT_CACHE
      fprintf(stderr, "H"); /* Hit! */
#endif
      ObjList_MoveObjToStart(cache->buffer_list, current);
      return (buffer->instance);
    }
  }

  /* キャッシュ中に見つけられなかった場合 */

  /* リストから検索する */
  instance = XColorGCList_GetXColorGCInstance(cache->color_gc_list, color);

  /* キャッシュに追加する */
  if (ObjList_GetLength(cache->buffer_list) < cache->size) {
    buffer = XColorGCCacheBuffer_Create(instance);
    ObjList_InsertObjToStart(cache->buffer_list, buffer,
			     (ObjDestructor)XColorGCCacheBuffer_Destroy);
  } else {
    current = ObjList_GetEnd(cache->buffer_list);
    buffer = (XColorGCCacheBuffer)ObjListData_GetObj(current);
    buffer->instance = instance;
    ObjList_MoveObjToStart(cache->buffer_list, current);
  }

#ifdef HIT_CACHE
  fprintf(stderr, "F"); /* False! */
#endif

  return (instance);
}

/*===========================================================================*/
/* XColorGCHash 関連                                                         */
/*===========================================================================*/

static XColorGCHash XColorGCHash_Create(XDisplay x_display,
					int studying_flag,
					int cache_flag,
					int cache_size,
					int hash_number)
{
  XColorGCHash hash;
  int i;

  hash = (XColorGCHash)malloc(sizeof(_XColorGCHash));
  if (hash == NULL)
    WonX_Error("XColorGCHash_Create", "Cannot allocate memory.");

  hash->number = hash_number;
  hash->cache_flag = cache_flag;

  if (cache_flag) {
    hash->color_gc_cache =
      (XColorGCCache *)malloc(sizeof(XColorGCCache) * hash->number);
    if (hash->color_gc_cache == NULL)
      WonX_Error("XColorGCHash_Create", "Cannot allocate memory.");
  } else {
    hash->color_gc_cache = NULL;
  }

  hash->color_gc_list =
    (XColorGCList *)malloc(sizeof(XColorGCList) * hash->number);
  if (hash->color_gc_list == NULL)
    WonX_Error("XColorGCHash_Create", "Cannot allocate memory.");

  for (i = 0; i < hash->number; i++) {
    hash->color_gc_list[i] = XColorGCList_Create(x_display, studying_flag);
    if (cache_flag) {
      hash->color_gc_cache[i] = XColorGCCache_Create(hash->color_gc_list[i],
						     cache_size);
    }
  }

  return (hash);
}

static XColorGCHash XColorGCHash_Destroy(XColorGCHash hash)
{
  int i;

  if (hash == NULL) return (NULL);

  if (hash->color_gc_cache) {
    for (i = 0; i < hash->number; i++) {
      if (hash->color_gc_cache[i])
	XColorGCCache_Destroy(hash->color_gc_cache[i]);
    }
    free(hash->color_gc_cache);
  }

  if (hash->color_gc_list) {
    for (i = 0; i < hash->number; i++) {
      if (hash->color_gc_list[i])
	XColorGCList_Destroy(hash->color_gc_list[i]);
    }
    free(hash->color_gc_list);
  }

  free(hash);

  return (NULL);
}

static void XColorGCHash_OutputHashStatus(XColorGCHash hash)
{
  int i;
  printf ("\nHash :");
  for (i = 0; i < hash->number; i++) {
    printf("%d ", ObjList_GetLength(hash->color_gc_list[i]->list));
  }
  printf ("\n");
}

/*---------------------------------------------------------------------------*/
/* ハッシュ関数                                                              */
/* 色を減色している場合，特定の位置だけ頻繁に使用されたりしないように注意．  */
/* (たとえば，                                                               */
/*  ((int)color.red*3 + (int)color.green*2 + (int)color.blue) % hash->number */
/*  のようなハッシュ関数だと，16階調に減色したときに，4096 の倍数の位置だけ  */
/*  頻繁に使用されてしまう．                                                 */
/*---------------------------------------------------------------------------*/

static int HashFunction(XColorGCHash hash, XColor color)
{
  return ((
	   (((int)color.red)   / 3000) * 11 +
	   (((int)color.green) % 3000) / 7 +
	   (((int)color.blue)  % 1000) / 3
	   ) % hash->number);
}

/*---------------------------------------------------------------------------*/
/* ハッシュから XColorGCInstance を得る．                                    */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCHash_GetXColorGCInstance(XColorGCHash hash,
							 XColor color)
{
  int n;

  n = HashFunction(hash, color);

  if (hash->cache_flag)
    return (XColorGCCache_GetXColorGCInstance(hash->color_gc_cache[n], color));
  else
    return (XColorGCList_GetXColorGCInstance(hash->color_gc_list[n], color));
}

/*===========================================================================*/
/* ColorName 関連                                                            */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの生成                                                        */
/*---------------------------------------------------------------------------*/

static ColorName ColorName_Create(XDisplay x_display, char * name)
{
  ColorName color_name;

  color_name = (ColorName)malloc(sizeof(_ColorName));
  if (color_name == NULL)
    WonX_Error("ColorName_Create", "Cannot allocate memory");

  color_name->name = malloc(sizeof(char) * (strlen(name) + 1));
  if (color_name->name == NULL)
    WonX_Error("ColorName_Create", "Cannot allocate memory");

  strcpy(color_name->name, name);

  XParseColor(XDisplay_GetDisplay(x_display),
	      XDisplay_GetColormap(x_display),
	      color_name->name, &(color_name->color));

  return (color_name);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

static ColorName ColorName_Destroy(ColorName color_name)
{
  if (color_name == NULL) return (NULL);
  if (color_name->name) free(color_name->name);
  free(color_name);
  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの生成                                                        */
/*---------------------------------------------------------------------------*/

static ColorNameList ColorNameList_Create(XDisplay x_display)
{
  ColorNameList list;

  list = (ColorNameList)malloc(sizeof(_ColorNameList));
  if (list == NULL)
    WonX_Error("ColorNameList_Create", "Cannot allocate memory");

  list->x_display = x_display;
  list->list = ObjList_Create();

  return (list);
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

static ColorNameList ColorNameList_Destroy(ColorNameList list)
{
  if (list == NULL) return (NULL);
  if (list->list) ObjList_Destroy(list->list);
  free(list);
  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* 文字列で与えられた色名から，RGB値を検索する．                             */
/*---------------------------------------------------------------------------*/

static XColor ColorNameList_GetColor(ColorNameList list, char * name)
{
  ObjListData current;
  ColorName color_name;

  for (current = ObjList_GetStart(list->list);
       !ObjList_IsEndEdge(list->list, current);
       current = ObjListData_GetNext(current)) {
    color_name = (ColorName)ObjListData_GetObj(current);
    if (!strcmp(color_name->name, name)) {
      ObjList_MoveObjToStart(list->list, current);
      return (color_name->color);
    }
  }

  color_name = ColorName_Create(list->x_display, name);
  if (color_name == NULL)
    WonX_Error("ColorNameList_GetColor", "Cannot create ColorName");

  ObjList_InsertObjToStart(list->list, color_name,
			   (ObjDestructor)ColorName_Destroy);

  return (color_name->color);
}

/*===========================================================================*/
/* XColorGC 関連                                                             */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* オブジェクトの生成                                                        */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_Create(XColorGCDatabase database, XColor color)
{
  XColorGC color_gc;

  color_gc = (XColorGC)malloc(sizeof(_XColorGC));

  /* ハッシュから色とGCを検索 */
  color_gc->instance = XColorGCHash_GetXColorGCInstance(database->hash, color);

  return (color_gc);
}

XColorGC XColorGC_CreateFromXColorGC(XColorGCDatabase database, XColorGC c)
{
  XColorGC color_gc;

  color_gc = (XColorGC)malloc(sizeof(_XColorGC));

  color_gc->instance = c->instance;

  return (color_gc);
}

/*---------------------------------------------------------------------------*/
/* RGB 値から生成する．                                                      */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_CreateFromRGB(XColorGCDatabase database,
				int red, int green, int blue)
{
  XColor color;

  color.red   = red;
  color.green = green;
  color.blue  = blue;
  color.flags = DoRed | DoGreen | DoBlue;

  return (XColorGC_Create(database, color));
}

/*---------------------------------------------------------------------------*/
/* オブジェクトの削除                                                        */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_Destroy(XColorGC color_gc)
{
  if (!color_gc) return (NULL);

  free(color_gc);

  return (NULL);
}

/*===========================================================================*/
/* 文字列読み込み用関数                                                      */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* 色の節約のための，減色用の関数．                                          */
/* 減色すると，色の共有化が進み，キャッシングの効果が大きくなる．            */
/* あるていど減色しないと，色が共有できないので，無駄が多くなる．            */
/*---------------------------------------------------------------------------*/

static XColor DecreaseColor(XColor color, int gradation)
{
  int div = RGB_MAX_VALUE / gradation + 1;

  color.red   /= div;
  if (color.red   >= gradation - 1) color.red   = RGB_MAX_VALUE;
  else color.red   *= div;

  color.green /= div;
  if (color.green >= gradation - 1) color.green = RGB_MAX_VALUE;
  else color.green *= div;

  color.blue  /= div;
  if (color.blue  >= gradation - 1) color.blue  = RGB_MAX_VALUE;
  else color.blue  *= div;

  return (color);
}

/*---------------------------------------------------------------------------*/
/* 色とGCのデータベースから name で与えられた名前の色を検索する．            */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_CreateFromCharacters(XColorGCDatabase database, char * name)
{
  XColor color;

  if (!strcmp(name, "none") ||
      !strcmp(name, "None") ||
      !strcmp(name, "NONE") ||
      !strcmp(name, "back") ||
      !strcmp(name, "Back") ||
      !strcmp(name, "BACK") ||
      !strcmp(name, "background") ||
      !strcmp(name, "Background") ||
      !strcmp(name, "BACKGROUND")) {
    if (database->background_color_gc)
      return (XColorGC_CreateFromXColorGC(database,
					  database->background_color_gc));
    else
#if 1
      name = "none";
#else
    name = "black";
#endif
  }

  color = ColorNameList_GetColor(database->color_name_list, name);

  /* 色の節約のため，減色する */
  color = DecreaseColor(color, database->gradation);

  return (XColorGC_Create(database, color));
}

/*---------------------------------------------------------------------------*/
/* XColor 構造体の取得                                                       */
/*---------------------------------------------------------------------------*/

XColor XColorGC_GetColor(XColorGC color_gc)
{
  return (color_gc->instance->color);
}

/*---------------------------------------------------------------------------*/
/* ピクセル値の取得                                                          */
/*---------------------------------------------------------------------------*/

unsigned long XColorGC_GetPixel(XColorGC color_gc)
{
  return (color_gc->instance->color.pixel);
}

/*---------------------------------------------------------------------------*/
/* GC の取得                                                                 */
/*---------------------------------------------------------------------------*/

GC XColorGC_GetGC(XColorGC color_gc)
{
  return (color_gc->instance->gc);
}

/*---------------------------------------------------------------------------*/
/* 色の明るさの取得                                                          */
/*---------------------------------------------------------------------------*/

int GetBrightness(XColor color)
{
  long int br;

#if 0
  br = color.red > color.green ? color.red : color.green;
  br = br > color.blue ? br : color.blue;
  br = br * 100 / RGB_MAX_VALUE;
#else
  br = color.red + color.green + color.blue;
  br = br * 100 / RGB_MAX_VALUE;
#endif

  if (br > 100) br = 100;

  return ((int)br);
}

/*===========================================================================*/
/* GC のデータベース                                                         */
/*===========================================================================*/

XColorGCDatabase XColorGCDatabase_Create(XDisplay x_display,
					 int studying_flag,
					 int cache_flag,
					 int cache_size,
					 int hash_number,
					 char * background,
					 int gradation)
{
  XColorGCDatabase database;

  database = (XColorGCDatabase)malloc(sizeof(_XColorGCDatabase));
  if (database == NULL)
    WonX_Error("XColorGCDatabase_Create", "Cannot allocate memory.");

  database->x_display = x_display;
  database->gradation = gradation;

  database->hash = XColorGCHash_Create(database->x_display,
				       studying_flag,
				       cache_flag,
				       cache_size,
				       hash_number);
  database->color_name_list = ColorNameList_Create(database->x_display);

  /* background が "none" の場合にも正常動作するように，               */
  /* XColorGC_CreateFromCharacters()を呼び出す前に，NULL で初期化する． */
  database->background_color_gc = NULL;

  /* 引数に database を入れて呼び出すので，必ず最後に置くこと */
  database->background_color_gc =
    XColorGC_CreateFromCharacters(database, background);
  /* この直後に return() が来るようにすること */

  return (database);
}

XColorGCDatabase XColorGCDatabase_Destroy(XColorGCDatabase database)
{
  if (database == NULL) return (NULL);

  if (database->background_color_gc)
    XColorGC_Destroy(database->background_color_gc);

  if (database->color_name_list)
    ColorNameList_Destroy(database->color_name_list);
  if (database->hash) XColorGCHash_Destroy(database->hash);
  free(database);

  return (NULL);
}

XColorGC XColorGCDatabase_GetBackgroundXColorGC(XColorGCDatabase database)
{
  return (database->background_color_gc);
}

/*---------------------------------------------------------------------------*/
/* チューニング用                                                            */
/*---------------------------------------------------------------------------*/

void XColorGCDatabase_OutputHashStatus(XColorGCDatabase database)
{
  XColorGCHash_OutputHashStatus(database->hash);
}

/*****************************************************************************/
/* End of File                                                               */
/*****************************************************************************/
