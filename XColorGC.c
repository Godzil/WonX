/*****************************************************************************/
/* XColorGC GC�ȿ��δ������䤤��碌�ѤΥ饤�֥��                           */
/*****************************************************************************/

#include "XColorGCP.h"

#include "WonX.h"

#include <string.h>

/*===========================================================================*/
/* XColorGCInstance ��Ϣ                                                     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ���                                                        */
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

  /* XAllocColor �� instance->color.red �ʤɤ����Ƥ��Ѥ�äƤ��ޤ��Τǡ�   */
  /* ��Ȥ��᤹���Ǥʤ��ȡ����Ȥ�Ʊ������RGB�ͤǸ������Ƥ⡤��ä����Ȥ��� */
  /* ��ᤵ��Ƥ��ޤ��������Ǥ��ʤ��Τǡ����������¸�����̣��̵���ʤä�  */
  /* ���ޤ���                                                              */
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
/* ���֥������Ȥκ��                                                        */
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
/* XColorGCList ��Ϣ                                                         */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ���                                                        */
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
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

static XColorGCList XColorGCList_Destroy(XColorGCList list)
{
  if (list == NULL) return (NULL);

  if (list->list) ObjList_Destroy(list->list);

  free(list);

  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* XColorGCList ��Ǥ� XColorGCInstance �Υ������Ѥ���Ӵؿ�                 */
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
/* �ꥹ�Ȥ��� XColorGCInstance �����롥                                      */
/* GC �μ����׵���Ф��ơ�GC �Υꥹ�Ȥ򸡺������֤���                        */
/* ¸�ߤ��ʤ����ˤϡ��������ƥꥹ�Ȥ��ɲä��롥                            */
/* (��� RGB �ͤǥ����Ȥ��줿���֤��ɲä���)                                 */
/* ����õ���ʤΤǡ�O(n^2)���٤��ʤ롥                                        */
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

    if (cmp == 0) { /* ���Ĥ���С�������֤� */
#ifdef HIT_LIST
      fprintf(stderr, "S");
#endif
      if (list->studying_flag) ObjList_MoveObjToStart(list->list, current);
      return (instance);
    } else if (cmp > 0) {
      if (!list->studying_flag) break;
    }
  }

  /* ���Ĥ���ʤ��ä����ϡ��������ƥꥹ�Ȥ��ɲä��� */
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
/* XColorGCCache ��Ϣ                                                        */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ����å����ѥХåե�                                                      */
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
/* ����å���                                                                */
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
/* ����å��夫�� XColorGCInstance �����롥                                  */
/*---------------------------------------------------------------------------*/

static XColorGCInstance XColorGCCache_GetXColorGCInstance(XColorGCCache cache,
							  XColor color)
{
  ObjListData current;
  XColorGCCacheBuffer buffer;
  XColorGCInstance instance;
  int cmp;

  /* ����å������򸡺� */
  for (current = ObjList_GetStart(cache->buffer_list);
       !ObjList_IsEndEdge(cache->buffer_list, current);
       current = ObjListData_GetNext(current)) {

    buffer = (XColorGCCacheBuffer)ObjListData_GetObj(current);
    cmp = XColorGCInstance_CmpToColor(buffer->instance, color);

    if (cmp == 0) { /* ����å�����˸��Ĥ������ */
#ifdef HIT_CACHE
      fprintf(stderr, "H"); /* Hit! */
#endif
      ObjList_MoveObjToStart(cache->buffer_list, current);
      return (buffer->instance);
    }
  }

  /* ����å�����˸��Ĥ����ʤ��ä���� */

  /* �ꥹ�Ȥ��鸡������ */
  instance = XColorGCList_GetXColorGCInstance(cache->color_gc_list, color);

  /* ����å�����ɲä��� */
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
/* XColorGCHash ��Ϣ                                                         */
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
/* �ϥå���ؿ�                                                              */
/* ���򸺿����Ƥ����硤����ΰ��֤������ˤ˻��Ѥ��줿�ꤷ�ʤ��褦����ա�  */
/* (���Ȥ��С�                                                               */
/*  ((int)color.red*3 + (int)color.green*2 + (int)color.blue) % hash->number */
/*  �Τ褦�ʥϥå���ؿ����ȡ�16��Ĵ�˸��������Ȥ��ˡ�4096 ���ܿ��ΰ��֤���  */
/*  ���ˤ˻��Ѥ���Ƥ��ޤ���                                                 */
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
/* �ϥå��夫�� XColorGCInstance �����롥                                    */
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
/* ColorName ��Ϣ                                                            */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥ�����                                                        */
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
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

static ColorName ColorName_Destroy(ColorName color_name)
{
  if (color_name == NULL) return (NULL);
  if (color_name->name) free(color_name->name);
  free(color_name);
  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥ�����                                                        */
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
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

static ColorNameList ColorNameList_Destroy(ColorNameList list)
{
  if (list == NULL) return (NULL);
  if (list->list) ObjList_Destroy(list->list);
  free(list);
  return (NULL);
}

/*---------------------------------------------------------------------------*/
/* ʸ�����Ϳ����줿��̾���顤RGB�ͤ򸡺����롥                             */
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
/* XColorGC ��Ϣ                                                             */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥ�����                                                        */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_Create(XColorGCDatabase database, XColor color)
{
  XColorGC color_gc;

  color_gc = (XColorGC)malloc(sizeof(_XColorGC));

  /* �ϥå��夫�鿧��GC�򸡺� */
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
/* RGB �ͤ����������롥                                                      */
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
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

XColorGC XColorGC_Destroy(XColorGC color_gc)
{
  if (!color_gc) return (NULL);

  free(color_gc);

  return (NULL);
}

/*===========================================================================*/
/* ʸ�����ɤ߹����Ѵؿ�                                                      */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* ��������Τ���Ρ������Ѥδؿ���                                          */
/* ��������ȡ����ζ�ͭ�����ʤߡ�����å��󥰤θ��̤��礭���ʤ롥            */
/* ����Ƥ��ɸ������ʤ��ȡ�������ͭ�Ǥ��ʤ��Τǡ�̵�̤�¿���ʤ롥            */
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
/* ����GC�Υǡ����١������� name ��Ϳ����줿̾���ο��򸡺����롥            */
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

  /* ��������Τ��ᡤ�������� */
  color = DecreaseColor(color, database->gradation);

  return (XColorGC_Create(database, color));
}

/*---------------------------------------------------------------------------*/
/* XColor ��¤�Τμ���                                                       */
/*---------------------------------------------------------------------------*/

XColor XColorGC_GetColor(XColorGC color_gc)
{
  return (color_gc->instance->color);
}

/*---------------------------------------------------------------------------*/
/* �ԥ������ͤμ���                                                          */
/*---------------------------------------------------------------------------*/

unsigned long XColorGC_GetPixel(XColorGC color_gc)
{
  return (color_gc->instance->color.pixel);
}

/*---------------------------------------------------------------------------*/
/* GC �μ���                                                                 */
/*---------------------------------------------------------------------------*/

GC XColorGC_GetGC(XColorGC color_gc)
{
  return (color_gc->instance->gc);
}

/*---------------------------------------------------------------------------*/
/* �������뤵�μ���                                                          */
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
/* GC �Υǡ����١���                                                         */
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

  /* background �� "none" �ξ��ˤ�����ư���褦�ˡ�               */
  /* XColorGC_CreateFromCharacters()��ƤӽФ����ˡ�NULL �ǽ�������롥 */
  database->background_color_gc = NULL;

  /* ������ database ������ƸƤӽФ��Τǡ�ɬ���Ǹ���֤����� */
  database->background_color_gc =
    XColorGC_CreateFromCharacters(database, background);
  /* ����ľ��� return() �����褦�ˤ��뤳�� */

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
/* ���塼�˥���                                                            */
/*---------------------------------------------------------------------------*/

void XColorGCDatabase_OutputHashStatus(XColorGCDatabase database)
{
  XColorGCHash_OutputHashStatus(database->hash);
}

/*****************************************************************************/
/* End of File                                                               */
/*****************************************************************************/
