#ifndef _WWTimerP_h_INCLUDED_
#define _WWTimerP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWTimer.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWTimer {

  int timer_on; /* �����ޤξ��� */
  int auto_preset; /* �����ȥץꥻ�å� */
  int preset_counter; /* �ץꥻ�åȡ������� */
  int counter; /* ������ */

} _WWTimer;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/