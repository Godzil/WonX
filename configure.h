/* configure.h for configuration of xfireworks */

#ifndef _WONX_CONFIGURE_H_INCLUDED_
#define _WONX_CONFIGURE_H_INCLUDED_

/* Wonx でのタイマ割り込みの周期(単位はマイクロ秒) */
#define WONX_TIMER_INTERVAL 100000 /* 0.1 秒*/

/* HBLANK, VBLANK 割り込みのデフォルトのインターバル(0.1秒単位) */
#define WONX_HBLANK_INTERVAL ( 3 * 10) /*  3 秒毎 */
#define WONX_VBLANK_INTERVAL (20 * 10) /* 20 秒毎 */

#endif /* _WONX_CONFIGURE_H_INCLUDED_ */

/* End of configure.h */
