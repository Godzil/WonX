/*****************************************************************************/
/* Obj.h - A library for object list.                                        */
/*                                                                           */
/* Obj.h Copyright (c) 2000 Sakai Hiroaki.                                   */
/* All Rights Reserved.                                                      */
/*****************************************************************************/

#ifndef _SAKAILIB_OBJ_H_INCLUDED_
#define _SAKAILIB_OBJ_H_INCLUDED_

typedef void * Obj;
typedef struct _ObjListData * ObjListData;
typedef struct _ObjList * ObjList;
typedef Obj (*ObjDestructor)(Obj);

#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* ObjList 型オブジェクトの操作                                              */
/*****************************************************************************/

Obj ObjListData_GetObj(ObjListData data);
Obj ObjListData_GetPrev(ObjListData data);
Obj ObjListData_GetNext(ObjListData data);
int ObjList_GetLength(ObjList list);
ObjListData ObjList_GetStartEdge(ObjList list);
ObjListData ObjList_GetEndEdge(ObjList list);
ObjListData ObjList_GetStart(ObjList list);
ObjListData ObjList_GetEnd(ObjList list);
int ObjList_IsEmpty(ObjList list);
int ObjList_IsStartEdge(ObjList list, ObjListData data);
int ObjList_IsEndEdge(ObjList list, ObjListData data);
int ObjList_IsStart(ObjList list, ObjListData data);
int ObjList_IsEnd(ObjList list, ObjListData data);
ObjListData ObjList_InsertObjToPrev(ObjList list, ObjListData current,
				    Obj obj, Obj (*destructor)());
ObjListData ObjList_InsertObjToNext(ObjList list, ObjListData current,
				    Obj obj, Obj (*destructor)());
ObjListData ObjList_InsertObjToStart(ObjList list, Obj obj,
				     Obj (*destructor)());
ObjListData ObjList_InsertObjToEnd(ObjList list, Obj obj,
				   Obj (*destructor)());
ObjListData ObjList_DeleteObjToPrev(ObjList list, ObjListData current);
ObjListData ObjList_DeleteObjToNext(ObjList list, ObjListData current);
ObjListData ObjList_DeleteObjFromStart(ObjList list);
ObjListData ObjList_DeleteObjFromEnd(ObjList list);
ObjListData ObjList_MoveObjToPrev(ObjList list,
				  ObjListData current,
				  ObjListData to);
ObjListData ObjList_MoveObjToNext(ObjList list,
				  ObjListData current,
				  ObjListData to);
ObjListData ObjList_MoveObjToStart(ObjList list, ObjListData current);
ObjListData ObjList_MoveObjToEnd(ObjList list, ObjListData current);
ObjList ObjList_Create(); /* ObjList 型オブジェクトを作成する */
ObjList ObjList_Destroy(ObjList list); /*  */

/*===========================================================================*/
/* 複数のリスト間での操作                                                    */
/*===========================================================================*/

ObjListData ObjList_MoveObjToPrevOfOtherList(ObjList list, ObjListData current,
					     ObjList to_list, ObjListData to);
ObjListData ObjList_MoveObjToNextOfOtherList(ObjList list, ObjListData current,
					     ObjList to_list, ObjListData to);
ObjListData ObjList_MoveObjToStartOfOtherList(ObjList list,
					      ObjListData current,
					      ObjList to_list);
ObjListData ObjList_MoveObjToEndOfOtherList(ObjList list,
					    ObjListData current,
					    ObjList to_list);
ObjList ObjList_Concatenate(ObjList list1, ObjList list2);

#endif

