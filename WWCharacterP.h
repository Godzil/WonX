#ifndef _WWCharacterP_h_INCLUDED_
#define _WWCharacterP_h_INCLUDED_

/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "WWCharacter.h"

/*****************************************************************************/
/* ���饹�����                                                              */
/*****************************************************************************/

typedef struct _WWCharacter {
  int number;

  /* �ӥåȥޥåפ�2�ӥåȤǤԤȤĤΥԥ�������б����롥 */
  /* 2�ӥåȤ��ͤ���palette �ο����б����롥             */
  unsigned char bitmap[16];
} _WWCharacter;

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

#endif

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/