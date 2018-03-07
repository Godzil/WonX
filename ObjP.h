/*****************************************************************************/
/* ObjP.h - A library for object list.                                       */
/*                                                                           */
/* ObjP.h Copyright (c) 2000 Sakai Hiroaki.                                  */
/* All Rights Reserved.                                                      */
/*****************************************************************************/

#ifndef _SAKAILIB_OBJP_H_INCLUDED_
#define _SAKAILIB_OBJP_H_INCLUDED_

#include "Obj.h"

/* �ǡ�����Ǽ�ѹ�¤�� */
typedef struct _ObjListData {
  struct _ObjListData * prev; /* ���Υǡ��� */
  struct _ObjListData * next; /* ���Υǡ��� */
  Obj obj; /* ���֥������� */
  Obj (*destructor)(Obj); /* ������˸ƤФ��ǥ��ȥ饯�� */
} _ObjListData;

/* �ꥹ�ȹ�¤�δ����� */
typedef struct _ObjList {
  struct _ObjListData * start_edge;
  struct _ObjListData * end_edge;
  int length;
} _ObjList;

#endif
