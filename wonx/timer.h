#ifndef _WONX_SYS_TIMER_H_
#define _WONX_SYS_TIMER_H_

#include "service.h"

enum {
  RTC_YEAR = 0,
  RTC_MONTH,
  RTC_DATE,
  RTC_DAY_OF_WEEK,
  RTC_HOUR,
  RTC_MIN,
  RTC_SEC
};

enum timer_type {
  TIMER_HBLANK = 0,
  TIMER_VBLANK
};

enum timer_preset_type {
  TIMER_ONESHOT = 0,
  TIMER_AUTOPRESET
};

#define rtc_set_year(year)        rtc_set_datetime(RTC_YEAR, year)
#define rtc_set_month(month)      rtc_set_datetime(RTC_MONTH, month)
#define rtc_set_date(date)        rtc_set_datetime(RTC_DATE, date)
#define rtc_set_day_of_week(week) rtc_set_datetime(RTC_DAY_OF_WEEK, week)
#define rtc_set_hour(hour)        rtc_set_datetime(RTC_HOUR, hour)
#define rtc_set_minute(min)       rtc_set_datetime(RTC_MIN, min)
#define rtc_set_second(sec)       rtc_set_datetime(RTC_SEC, sec)

#define rtc_get_year()        rtc_get_datetime(RTC_YEAR)
#define rtc_get_month()       rtc_get_datetime(RTC_MONTH)
#define rtc_get_date()        rtc_get_datetime(RTC_DATE)
#define rtc_get_day_of_week() rtc_get_datetime(RTC_DAY_OF_WEEK)
#define rtc_get_hour()        rtc_get_datetime(RTC_HOUR)
#define rtc_get_minute()      rtc_get_datetime(RTC_MIN)
#define rtc_get_second()      rtc_get_datetime(RTC_SEC)

void rtc_set_datetime(int type, unsigned int value);
unsigned int rtc_get_datetime(int type);
void rtc_set_datetime_struct(datetime_t * d);
void rtc_get_datetime_struct(datetime_t * d);
void rtc_enable_alarm(int hour, int minute);
void rtc_disable_alarm(void);
void timer_enable(int type, unsigned int auto_preset, unsigned int count);
void timer_disable(int type);
unsigned int timer_get_count(int type);

#endif
