#ifndef _WONX_SYS_SYSTEM_H_
#define _WONX_SYS_SYSTEM_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

enum {
  SYS_INT_SENDREADY = 0,
  SYS_INT_KEY,
  SYS_INT_CASETTE,
  SYS_INT_RECEIVEREADY,
  SYS_INT_DISPLINE,
  SYS_INT_TIMER_COUNTUP,
  SYS_INT_VBLANK,
  SYS_INT_HBLANK_COUNTUP
};

typedef struct {
  void (*callback)(void);
  int cs;
  int ds;
  int reserve;
} intvector_t;

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

void sys_interrupt_set_hook(int type, intvector_t * vector,
			    intvector_t * old_vector);
void sys_interrupt_reset_hook(int type, intvector_t * old_vector);
void sys_wait(unsigned int wait_time);
unsigned long int sys_get_tick_count(void);
void sys_sleep(void);
void sys_set_sleep_time(int sleep_time);
int sys_get_sleep_time(void);
void sys_set_awake_key(int pattern);
int sys_get_awake_key(void);
void sys_set_keepalive_int(int pattern);
void sys_get_ownerinfo(int size, char * buffer);
int sys_suspend(int core);
void sys_resume(int core);
void sys_set_remote(int remote);
unsigned int sys_get_remote(void);
void * sys_alloc_iram(void * p, unsigned int size);
void sys_free_iram(void * p);
void * sys_get_my_iram(void);
unsigned int sys_get_version(void);
int sys_swap(int core);
void sys_set_resume(unsigned int flags);
unsigned int sys_get_resume(void);

#endif
