#ifndef _WonxSystem_h_INCLUDED_
#define _WonxSystem_h_INCLUDED_

/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include "WWInterrupt.h"
#include "WWTimer.h"
#include "UNIXTimer.h"

/*****************************************************************************/
/* クラスの定義                                                              */
/*****************************************************************************/

typedef struct _WonxSystem * WonxSystem;

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

WWInterrupt WonxSystem_GetWWInterrupt(WonxSystem wonx_system);
WWInterrupt WonxSystem_SetWWInterrupt(WonxSystem wonx_system,
				      WWInterrupt ww_interrupt);

WWTimer WonxSystem_GetWWTimer(WonxSystem wonx_system, int type);
WWTimer WonxSystem_SetWWTimer(WonxSystem wonx_system, int type, WWTimer t);

WWTimer WonxSystem_GetWWVBlankTimer(WonxSystem wonx_system);
WWTimer WonxSystem_SetWWVBlankTimer(WonxSystem wonx_system, WWTimer t);

WWTimer WonxSystem_GetWWVBlankCountUpTimer(WonxSystem wonx_system);
WWTimer WonxSystem_SetWWVBlankCountUpTimer(WonxSystem wonx_system, WWTimer t);

WWTimer WonxSystem_GetWWHBlankCountUpTimer(WonxSystem wonx_system);
WWTimer WonxSystem_SetWWHBlankCountUpTimer(WonxSystem wonx_system, WWTimer t);

UNIXTimer WonxSystem_GetUNIXTimer(WonxSystem wonx_system);
UNIXTimer WonxSystem_SetUNIXTimer(WonxSystem wonx_system,
				  UNIXTimer unix_timer);

WonxSystem WonxSystem_Create();
WonxSystem WonxSystem_Destroy(WonxSystem wonx_system);

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
