/*****************************************************************************/
/* Obj.c - A library for object list.                                        */
/*                                                                           */
/* Obj.c Copyright (c) 2000 Sakai Hiroaki.                                   */
/* All Rights Reserved.                                                      */
/*****************************************************************************/

#include "ObjP.h"

/*****************************************************************************/
/* ObjListData 型の操作                                                      */
/*****************************************************************************/

static ObjListData ObjListData_Create(Obj obj, Obj (*destructor)())
{
  ObjListData list_data;

  list_data = (ObjListData)malloc(sizeof(_ObjListData));

  list_data->obj = obj;
  list_data->destructor = destructor;

  return (list_data);
}

static ObjListData ObjListData_Destroy(ObjListData list_data)
{
  if (list_data == NULL) return (NULL);

  /* デストラクタの実行 */
  if (list_data->destructor)
    (*(list_data->destructor))(list_data->obj);

  free(list_data);

  return (NULL);
}

/*****************************************************************************/
/* ObjList 型オブジェクトの操作                                              */
/*****************************************************************************/

Obj ObjListData_GetObj(ObjListData data)
{
  if (data == NULL) return (NULL);
  return (data->obj);
}

ObjListData ObjListData_GetPrev(ObjListData data)
{
  if (data == NULL) return (NULL);
  return (data->prev);
}

ObjListData ObjListData_GetNext(ObjListData data)
{
  if (data == NULL) return (NULL);
  return (data->next);
}

int ObjList_GetLength(ObjList list)
{
  if (list == NULL) return (-1);
  return (list->length);
}

ObjListData ObjList_GetStartEdge(ObjList list)
{
  if (list == NULL) return (NULL);
  return (list->start_edge);
}

ObjListData ObjList_GetEndEdge(ObjList list)
{
  if (list == NULL) return (NULL);
  return (list->end_edge);
}

ObjListData ObjList_GetStart(ObjList list)
{
  if (list == NULL) return (NULL);
  return (list->start_edge->next);
}

ObjListData ObjList_GetEnd(ObjList list)
{
  if (list == NULL) return (NULL);
  return (list->end_edge->prev);
}

int ObjList_IsEmpty(ObjList list)
{
  if (list == NULL) return (1);
  return (list->start_edge->next == list->end_edge);
}

int ObjList_IsStartEdge(ObjList list, ObjListData data)
{
  if (list == NULL) return (0);
  return (data == list->start_edge);
}

int ObjList_IsEndEdge(ObjList list, ObjListData data)
{
  if (list == NULL) return (0);
  return (data == list->end_edge);
}

int ObjList_IsStart(ObjList list, ObjListData data)
{
  if (list == NULL) return (0);
  return (data == list->start_edge->next);
}

int ObjList_IsEnd(ObjList list, ObjListData data)
{
  if (list == NULL) return (0);
  return (data == list->end_edge->prev);
}

ObjListData ObjList_InsertObjToPrev(ObjList list, ObjListData current,
				    Obj obj, Obj (*destructor)())
{
  ObjListData data;

  if (list == NULL) return (NULL);
  if (ObjList_IsStartEdge(list, current)) return (NULL);

  data = ObjListData_Create(obj, destructor);
  if (data == NULL) return (NULL);

  data->prev = current->prev;
  data->next = current;
  current->prev->next = data;
  current->prev = data;
  (list->length)++;

  return (data);
}

ObjListData ObjList_InsertObjToNext(ObjList list, ObjListData current,
				    Obj obj, Obj (*destructor)())
{
  ObjListData data;

  if (list == NULL) return (NULL);
  if (ObjList_IsEndEdge(list, current)) return (NULL);

  data = ObjListData_Create(obj, destructor);
  if (data == NULL) return (NULL);

  data->next = current->next;
  data->prev = current;
  current->next->prev = data;
  current->next = data;
  (list->length)++;

  return (data);
}

ObjListData ObjList_InsertObjToStart(ObjList list, Obj obj,
				     Obj (*destructor)())
{
  ObjListData current;
  current = ObjList_GetStart(list);
  return (ObjList_InsertObjToPrev(list, current, obj, destructor));
}

ObjListData ObjList_InsertObjToEnd(ObjList list, Obj obj,
				   Obj (*destructor)())
{
  ObjListData current;
  current = ObjList_GetEnd(list);
  return (ObjList_InsertObjToNext(list, current, obj, destructor));
}

ObjListData ObjList_DeleteObjToPrev(ObjList list, ObjListData current)
{
  ObjListData ret;

  if (list == NULL) return (NULL);
  if (ObjList_IsStartEdge(list, current) || ObjList_IsEndEdge(list, current))
    return (NULL);

  current->prev->next = current->next;
  current->next->prev = current->prev;

  ret = current->prev;
  ObjListData_Destroy(current);
  (list->length)--;

  return (ret);
}

ObjListData ObjList_DeleteObjToNext(ObjList list, ObjListData current)
{
  ObjListData ret;

  if (list == NULL) return (NULL);
  if (ObjList_IsStartEdge(list, current) || ObjList_IsEndEdge(list, current))
    return (NULL);

  current->prev->next = current->next;
  current->next->prev = current->prev;

  ret = current->next;
  ObjListData_Destroy(current);
  (list->length)--;

  return (ret);
}

ObjListData ObjList_DeleteObjFromStart(ObjList list)
{
  ObjListData current;
  if (list == NULL) return (NULL);
  current = ObjList_GetStart(list);
  return (ObjList_DeleteObjToNext(list, current));
}

ObjListData ObjList_DeleteObjFromEnd(ObjList list)
{
  ObjListData current;
  if (list == NULL) return (NULL);
  current = ObjList_GetEnd(list);
  return (ObjList_DeleteObjToPrev(list, current));
}

ObjListData ObjList_MoveObjToPrev(ObjList list,
				  ObjListData current,
				  ObjListData to)
{
  if (list == NULL) return (NULL);
  return (ObjList_MoveObjToPrevOfOtherList(list, current, list, to));
}

ObjListData ObjList_MoveObjToNext(ObjList list,
				  ObjListData current,
				  ObjListData to)
{
  if (list == NULL) return (NULL);
  return (ObjList_MoveObjToNextOfOtherList(list, current, list, to));
}

ObjListData ObjList_MoveObjToStart(ObjList list, ObjListData current)
{
  if (list == NULL) return (NULL);
  return (ObjList_MoveObjToStartOfOtherList(list, current, list));
}

ObjListData ObjList_MoveObjToEnd(ObjList list, ObjListData current)
{
  if (list == NULL) return (NULL);
  return (ObjList_MoveObjToEndOfOtherList(list, current, list));
}

ObjList ObjList_Create() /* ObjList 型オブジェクトを作成する */
{
  ObjList list;

  list = (ObjList)malloc(sizeof(_ObjList));
  if (list == NULL) return (NULL);

  list->start_edge   = ObjListData_Create(NULL, NULL);
  list->end_edge     = ObjListData_Create(NULL, NULL);
  list->length  = 0;    /* 現在存在しているデータの数 */

  list->start_edge->prev = NULL;
  list->start_edge->next = list->end_edge;
  list->end_edge->prev   = list->start_edge;
  list->end_edge->next   = NULL;

  return (list);
}

ObjList ObjList_Destroy(ObjList list) /*  */
{
  if (list == NULL) return (NULL);

  while (!ObjList_IsEmpty(list))
    ObjList_DeleteObjFromStart(list);

  if (list->start_edge)
    list->start_edge = ObjListData_Destroy(list->start_edge);
  if (list->end_edge)
    list->end_edge = ObjListData_Destroy(list->end_edge);

  free(list);

  return (NULL);
}

/*===========================================================================*/
/* 複数のリスト間での操作                                                    */
/*===========================================================================*/

ObjListData ObjList_MoveObjToPrevOfOtherList(ObjList list, ObjListData current,
					     ObjList to_list, ObjListData to)
{
  if (list == NULL) return (NULL);
  if (to_list == NULL) return (NULL);
  if (ObjList_IsStartEdge(list, current) || ObjList_IsEndEdge(list, current))
    return (NULL);

  if (ObjList_IsStartEdge(to_list, to)) return (NULL);
  if ((list == to_list) && (current == to)) return (current);

  current->prev->next = current->next;
  current->next->prev = current->prev;

  current->prev = to->prev;
  current->next = to;
  to->prev->next = current;
  to->prev = current;

  (list->length)--;
  (to_list->length)++;

  return (current);
}

ObjListData ObjList_MoveObjToNextOfOtherList(ObjList list, ObjListData current,
					     ObjList to_list, ObjListData to)
{
  if (list == NULL) return (NULL);
  if (ObjList_IsStartEdge(list, current) || ObjList_IsEndEdge(list, current))
    return (NULL);

  if (ObjList_IsEndEdge(to_list, to)) return (NULL);
  if ((list == to_list) && (current == to)) return (current);

  current->prev->next = current->next;
  current->next->prev = current->prev;

  current->next = to->next;
  current->prev = to;
  to->next->prev = current;
  to->next = current;

  (list->length)--;
  (to_list->length)++;

  return (current);
}

ObjListData ObjList_MoveObjToStartOfOtherList(ObjList list,
					      ObjListData current,
					      ObjList to_list)
{
  ObjListData to;
  if (list == NULL) return (NULL);
  if (to_list == NULL) return (NULL);
  to = ObjList_GetStart(to_list);
  return (ObjList_MoveObjToPrevOfOtherList(list, current, to_list, to));
}

ObjListData ObjList_MoveObjToEndOfOtherList(ObjList list,
					    ObjListData current,
					    ObjList to_list)
{
  ObjListData to;
  if (list == NULL) return (NULL);
  if (to_list == NULL) return (NULL);
  to = ObjList_GetEnd(to_list);
  return (ObjList_MoveObjToNextOfOtherList(list, current, to_list, to));
}

ObjList ObjList_Concatenate(ObjList list1, ObjList list2)
{
  ObjListData tmp;

  if (list1 == NULL) {
    list1 = list2;
    return (list1);
  }
  if (list2 == NULL) return (list1);

  list1->end_edge->prev->next = list2->start_edge->next;
  list2->start_edge->next->prev = list1->end_edge->prev;

  tmp = list1->end_edge;
  list1->end_edge = list2->end_edge;
  list2->end_edge = tmp;

  list2->start_edge->next = list2->end_edge;
  list2->end_edge->prev = list2->start_edge;

  list1->length += list2->length;
  list2->length = 0;

  ObjList_Destroy(list2);

  return (list1);
}

/* End of File. */
