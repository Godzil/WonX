#ifndef _WONX_SYS_KEY_H_
#define _WONX_SYS_KEY_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define KEY_START  (1 <<  1)
#define KEY_A      (1 <<  2)
#define KEY_B      (1 <<  3)
#define KEY_UP1    (1 <<  4)
#define KEY_RIGHT1 (1 <<  5)
#define KEY_DOWN1  (1 <<  6)
#define KEY_LEFT1  (1 <<  7)
#define KEY_UP2    (1 <<  8)
#define KEY_RIGHT2 (1 <<  9)
#define KEY_DOWN2  (1 << 10)
#define KEY_LEFT2  (1 << 11)

#define KEY_X1 KEY_UP1
#define KEY_X2 KEY_RIGHT1
#define KEY_X3 KEY_DOWN1
#define KEY_X4 KEY_LEFT1
#define KEY_Y1 KEY_UP2
#define KEY_Y2 KEY_RIGHT2
#define KEY_Y3 KEY_DOWN2
#define KEY_Y4 KEY_LEFT2

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

int key_press_check(void);
int key_hit_check(void);
int key_wait(void);
void key_set_repeat(int rate, int delay);
int key_get_repeat(void);
int key_hit_check_with_repeat(void);

#endif
