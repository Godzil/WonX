#ifndef _WonXText_h_INCLUDED_
#define _WonXText_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWText.h"
#include "WWScreen.h"
#include "WWPalette.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonXText * WonXText;

WWText WonXText_GetWWText(WonXText wonx_text);
WWText WonXText_SetWWText(WonXText wonx_text, WWText ww_text);
WonXText WonXText_Create(WWScreen screen, int x, int y, int width, int height,
			 WWPalette palette);
WonXText WonXText_Destroy(WonXText wonx_text);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
