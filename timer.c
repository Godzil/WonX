#include <stdlib.h>

#include <sys/timer.h>

#include "wonx.h"

#include "WonxDisplay.h"

void rtc_set_datetime(int field, unsigned int value)
{
}

unsigned int rtc_get_datetime(int field)
{
  unsigned int t;
  t = (unsigned int)time(NULL); /* ここはてきとうなので，あとで修正すること */
  return (t);
}

void rtc_set_datetime_struct(void * buf)
{}
void rtc_get_datetime_struct(void * buf)
{}
void rtc_enable_alarm(int hour, int min)
{}
void rtc_disable_alarm(void)
{}
void timer_enable(int type, unsigned int auto_preset, unsigned int preset)
{}
void timer_disable(int type)
{}
unsigned int timer_get_count(int type)
{}
