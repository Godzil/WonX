#ifndef _WonxText_h_INCLUDED_
#define _WonxText_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWText.h"
#include "WWScreen.h"
#include "WWPalette.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonxText * WonxText;

WWText WonxText_GetWWText(WonxText wonx_text);
WWText WonxText_SetWWText(WonxText wonx_text, WWText ww_text);
WonxText WonxText_Create(WWScreen screen, int x, int y, int width, int height,
			 WWPalette palette);
WonxText WonxText_Destroy(WonxText wonx_text);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
