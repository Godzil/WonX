#include <stdlib.h>

#include <sys/system.h>

#include "wonx.h"

#include "WonxDisplay.h"

void sys_interrupt_set_hook(int type, intvector_t * intvector,
			    intvector_t * last_intvector)
{}

void sys_interrupt_reset_hook(int type, intvector_t * last_intvector)
{}

void sys_wait(unsigned int time)
{
}

unsigned long int sys_get_tick_count(void)
{
  return (0);
}

void sys_sleep(void)
{
}

void sys_set_sleep_time(int sleep_time)
{
}

int  sys_get_sleep_time(void)
{
  return (0);
}

void sys_set_awake_key(int awake_key_pattern)
{
}

int  sys_get_awake_key(void)
{
  return (0);
}

void sys_set_keepalive_int(int keepalive_pattern)
{
}

void sys_get_ownerinfo(int size, char *buffer)
{
}

int  sys_suspend(int core)
{
  return (0);
}

void sys_resume(int core)
{
}

void sys_set_remote(int remote_enable)
{
}

unsigned int sys_get_remote(void)
{
  return (0);
}

void * sys_alloc_iram(void *pointer, unsigned size)
{}

void sys_free_iram(void * p)
{}

void * sys_get_my_iram(void)
{
}

unsigned int sys_get_version(void)
{
  return (0);
}

int sys_swap(int core)
{
  return (0);
}

void sys_set_resume(unsigned int flags)
{
}

unsigned int sys_get_resume(void)
{
  return (0);
}
