/*****************************************************************************/
/* ObjP.h - A library for object list.                                       */
/*                                                                           */
/* ObjP.h Copyright (c) 2000 Sakai Hiroaki.                                  */
/* All Rights Reserved.                                                      */
/*****************************************************************************/

#ifndef _SAKAILIB_OBJP_H_INCLUDED_
#define _SAKAILIB_OBJP_H_INCLUDED_

#include "Obj.h"

/* データ格納用構造体 */
typedef struct _ObjListData {
  struct _ObjListData * prev; /* 前のデータ */
  struct _ObjListData * next; /* 次のデータ */
  Obj obj; /* オブジェクト */
  Obj (*destructor)(Obj); /* 削除時に呼ばれるデストラクタ */
} _ObjListData;

/* リスト構造の管理用 */
typedef struct _ObjList {
  struct _ObjListData * start_edge;
  struct _ObjListData * end_edge;
  int length;
} _ObjList;

#endif
