#ifndef _WWCursorP_h_INCLUDED_
#define _WWCursorP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWCursor.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWCursor {
  int on;            /* ɽ��/��ɽ���Υե饰 */
  int x, y;          /* ���������ɸ */
  int width, height; /* ��������Υ����� */
  int interval;      /* ���Ǽ��� */
  WWPalette palette; /* ��������ɽ���ѥѥ�å� */
} _WWCursor;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/