/*****************************************************************************/
/* XColorGC GCと色の管理・問い合わせ用のライブラリ                           */
/*****************************************************************************/

#ifndef _XColorGCP_h_INCLUDED_
#define _XColorGCP_h_INCLUDED_

#include "XColorGC.h"

#define RGB_MAX_VALUE 65535

/*===========================================================================*/
/* XFireworks は，描画の高速化のために，描画に必要な色と GC は，起動時に     */
/* すべて確保するのですが，無駄な X サーバへのリクエストとメモリの浪費を     */
/* 減らすために，いったん確保した色と GC はデータベースに記憶しておき，      */
/* 同じ色が必要になったときには，共有するようにします．                      */
/* (XColorGCDatabase はそのためのクラスです)                                 */
/* これにより，XAllocColor() による色の問い合わせ待ちが減るため，            */
/* 起動が格段に高速になります．                                              */
/* データベースの検索には，ハッシュ，キャッシュ，学習機能を使用することが    */
/* できます．                                                                */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/
/* 以下を有効にすると，同じ色のGCがどれくらい共有されているか調べることが    */
/* できます．                                                                */
/*---------------------------------------------------------------------------*/

/* #define HIT_LIST */

/*---------------------------------------------------------------------------*/
/* 以下を有効にすると，キャッシュのヒット率を調べることができます．          */
/*---------------------------------------------------------------------------*/

/* #define HIT_CACHE */

/*===========================================================================*/
/* GC の実体を管理するクラス                                                 */
/*===========================================================================*/

typedef struct _XColorGCInstance * XColorGCInstance;

typedef struct _XColorGCInstance {
  XDisplay x_display;
  GC gc;
  XColor color;
} _XColorGCInstance;

/*===========================================================================*/
/* GC の実体のリストを管理するクラス                                         */
/* 同一の色のGCは共有したいため，GCの実体をリストで管理し，GCの取得要求に    */
/* 対して，適切な XColorGCInstance を返す．                                  */
/* (すでに存在するのならそれを返し，無ければ Create する)                    */
/*===========================================================================*/

typedef struct _XColorGCList * XColorGCList;

typedef struct _XColorGCList { /* GC の管理用 */
  XDisplay x_display;
  int studying_flag; /* 学習機能のON/OFFのフラグ */
  ObjList list; /* XColorGCInstance のリスト */
} _XColorGCList;

/*===========================================================================*/
/* キャッシュ                                                                */
/*===========================================================================*/

typedef struct _XColorGCCacheBuffer * XColorGCCacheBuffer;
typedef struct _XColorGCCache * XColorGCCache;

/* キャッシュ用バッファ */
typedef struct _XColorGCCacheBuffer {
  XColorGCInstance instance;
} _XColorGCCacheBuffer;

/* キャッシュ */
typedef struct _XColorGCCache {
  int size; /* キャッシュサイズ */

  XColorGCList color_gc_list;
  ObjList buffer_list;
} _XColorGCCache;

/*===========================================================================*/
/* ハッシュ                                                                  */
/*===========================================================================*/

typedef struct _XColorGCHash * XColorGCHash;

typedef struct _XColorGCHash {
  int number; /* ハッシュの個数 */
  int cache_flag; /* キャッシュの使用・未使用のフラグ */
  XColorGCCache * color_gc_cache;
  XColorGCList * color_gc_list;
} _XColorGCHash;

/*===========================================================================*/
/* 色の名前とRGB値の対応を管理するためのクラス                               */
/*===========================================================================*/

typedef struct _ColorName * ColorName;
typedef struct _ColorNameList * ColorNameList;

typedef struct _ColorName {
  char * name;
  XColor color;
} _ColorName;

typedef struct _ColorNameList {
  XDisplay x_display;
  ObjList list; /* ColorName のリスト */
} _ColorNameList;

/*===========================================================================*/
/* 色と GC のデータベース                                                    */
/* GC の検索には，ハッシュを用いる．                                         */
/*===========================================================================*/

typedef struct _XColorGCDatabase { /* GC の管理用 */
  XDisplay x_display;
  XColorGCHash hash; /* ハッシュ */

  ColorNameList color_name_list; /* 色名 → RGB値の変換用 */

  /* 背景色．色名で"none"を指定すると，この色が使用される． */
  XColorGC background_color_gc;

  /* 減色数．16階調にするときには16を指定 */
  /* 10階調や20階調も指定可能             */
  int gradation;

} _XColorGCDatabase;

/*===========================================================================*/
/* GC を管理するクラス                                                       */
/* 同じ色の GC が重複しない用に，XColorGCList で GC を管理して，             */
/* 色の要求時には，XColorGCList から GC をもらうようにする．                 */
/*===========================================================================*/

typedef struct _XColorGC {
  XColorGCInstance instance;
} _XColorGC;

#endif

/*****************************************************************************/
/* End of File                                                               */
/*****************************************************************************/
