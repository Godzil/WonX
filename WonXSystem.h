#ifndef _WonXSystem_h_INCLUDED_
#define _WonXSystem_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WonXSystem * WonXSystem;

/*****************************************************************************/
/* �إå��ե�����Υ��󥯥롼��                                              */
/*****************************************************************************/

#include "WWInterrupt.h"
#include "WWTimer.h"
#include "UNIXTimer.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

WWInterrupt WonXSystem_GetWWInterrupt(WonXSystem wonx_system);
WWInterrupt WonXSystem_SetWWInterrupt(WonXSystem wonx_system,
				      WWInterrupt ww_interrupt);

WWTimer WonXSystem_GetWWTimer(WonXSystem wonx_system, int type);
WWTimer WonXSystem_SetWWTimer(WonXSystem wonx_system, int type, WWTimer t);

WWTimer WonXSystem_GetWWVBlankTimer(WonXSystem wonx_system);
WWTimer WonXSystem_SetWWVBlankTimer(WonXSystem wonx_system, WWTimer t);

WWTimer WonXSystem_GetWWVBlankCountUpTimer(WonXSystem wonx_system);
WWTimer WonXSystem_SetWWVBlankCountUpTimer(WonXSystem wonx_system, WWTimer t);

WWTimer WonXSystem_GetWWHBlankCountUpTimer(WonXSystem wonx_system);
WWTimer WonXSystem_SetWWHBlankCountUpTimer(WonXSystem wonx_system, WWTimer t);

UNIXTimer WonXSystem_GetUNIXTimer(WonXSystem wonx_system);
UNIXTimer WonXSystem_SetUNIXTimer(WonXSystem wonx_system,
				  UNIXTimer unix_timer);

WonXSystem WonXSystem_Create();
WonXSystem WonXSystem_Destroy(WonXSystem wonx_system);

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
