#include <stdlib.h>
#include <time.h>

#include <sys/timer.h>

#include "wonx.h"

#include "WonxDisplay.h"

typedef struct {
  unsigned char year;
  unsigned char month;
  unsigned char date;
  unsigned char day_of_week;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
} datetime_t;

/* int tm_year; year - 1900 */
static int get_year(struct tm * tblock) { return (tblock->tm_year - 100); }
/* int tm_mon; month of year (0-11) */
static int get_month(struct tm * tblock) { return (tblock->tm_mon + 1); }
/* int tm_mday; day of month (1-31) */
static int get_day(struct tm * tblock) { return (tblock->tm_mday); }
/* int tm_wday; day of week (Sunday = 0) */
static int get_week(struct tm * tblock) { return (tblock->tm_wday); }
/* int tm_hour; hours (0 - 23) */
static int get_hour(struct tm * tblock) { return (tblock->tm_hour); }
/* int tm_min; minutes (0 - 59) */
static int get_minute(struct tm * tblock) { return (tblock->tm_min); }
/* int tm_sec; seconds (0 - 60) */
static int get_second(struct tm * tblock) { return (tblock->tm_sec); }

void rtc_set_datetime(int field, unsigned int value)
{
  printf("call : rtc_set_datetime() : field = %d, value = %d\n",
	 field, (int)value);
  fflush(stdout);

  /* 未サポート */
  printf("call : rtc_set_datetime() : not supported\n");

  printf("call : rtc_set_datetime() : return value = none\n");
  fflush(stdout);

  return;
}

unsigned int rtc_get_datetime(int field)
{
  unsigned int ret;
  time_t timer;
  struct tm * tblock;

  printf("call : rtc_get_datetime() : field = %d\n", field);
  fflush(stdout);

  time(&timer);
  tblock = localtime(&timer);

  switch (field) {
  case RTC_YEAR        : ret = get_year(  tblock); break;
  case RTC_MONTH       : ret = get_month( tblock); break;
  case RTC_DATE        : ret = get_day(   tblock); break;
  case RTC_DAY_OF_WEEK : ret = get_week(  tblock); break;
  case RTC_HOUR        : ret = get_hour(  tblock); break;
  case RTC_MIN         : ret = get_minute(tblock); break;
  case RTC_SEC         : ret = get_second(tblock); break;
  }

  printf("call : rtc_get_datetime() : return value = %d\n", (int)ret);
  fflush(stdout);

  return (ret);
}

void rtc_set_datetime_struct(void * buffer)
{
  printf("call : rtc_set_datetime_struct() : buffer = %p\n", buffer);
  fflush(stdout);

  /* 未サポート */
  printf("call : rtc_set_datetime_struct() : not supported\n");

  printf("call : rtc_set_datetime_struct() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_get_datetime_struct(void * buffer)
{
  time_t timer;
  struct tm * tblock;
  datetime_t * p;

  printf("call : rtc_get_datetime_struct() : buffer = %p\n", buffer);
  fflush(stdout);

  time(&timer);
  tblock = localtime(&timer);

  p = (datetime_t *)buffer;

  p->year = get_year(tblock);
  p->month = get_month(tblock);
  p->date = get_day(tblock);
  p->day_of_week = get_week(tblock);
  p->hour = get_hour(tblock);
  p->minute = get_minute(tblock);
  p->second = get_second(tblock);

  printf("call : rtc_get_datetime_struct() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_enable_alarm(int hour, int minute)
{
  printf("call : rtc_enable_alarm() : hour = %d, minute = %d\n", hour, minute);
  fflush(stdout);

  /* 未サポート */
  printf("call : rtc_enable_alarm() : not supported\n");

  printf("call : rtc_enable_alarm() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_disable_alarm(void)
{
  printf("call : rtc_disable_alarm() : \n");
  fflush(stdout);

  /* 未サポート */
  printf("call : rtc_disable_alarm() : not supported\n");

  printf("call : rtc_disable_alarm() : return value = none\n");
  fflush(stdout);

  return;
}

void timer_enable(int type, unsigned int auto_preset, unsigned int preset)
{
  printf("call : timer_enable() : type = %d, auto_preset = %u, preset = %u\n",
	 type, (int)auto_preset, (int)preset);
  fflush(stdout);

  /* 未サポート */
  printf("call : timer_enable() : not supported\n");

  printf("call : timer_enable() : return value = none\n");
  fflush(stdout);

  return;
}

void timer_disable(int type)
{
  printf("call : timer_disable() : type = %d\n", type);
  fflush(stdout);

  /* 未サポート */
  printf("call : timer_disable() : not supported\n");

  printf("call : timer_disable() : return value = none\n");
  fflush(stdout);

  return;
}

unsigned int timer_get_count(int type)
{
  unsigned int ret = 0;

  printf("call : timer_get_count() : type = %d\n", type);
  fflush(stdout);

  /* 未サポート */
  printf("call : timer_get_count() : not supported\n");

  printf("call : timer_get_count() : return value = %u\n", ret);
  fflush(stdout);

  return;
}
