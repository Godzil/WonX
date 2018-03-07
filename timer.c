/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "wonx_include/timer.h"

#include "wonx_configure.h"
#include "Wonx.h"
#include "etc.h"

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

/*****************************************************************************/
/* �ߴ��ؿ������                                                            */
/*****************************************************************************/

/*
 * X�����ФȤ�Ʊ�������������Ȥ�ʤ��ʤ�ʤɤ����꤬�ͤ�����Τǡ�
 * �ߴ��ؿ��������� UNIXTimer_Pause(), UNIXTimer_Unpause() �Ǥ����ꡤ
 * �����޳����ߤ�����ߤ��ƽ�����Ԥ����ޤ���unpause ����ޤ��ˡ�
 * ���ʤ餺 sync ����褦�ˤ��롥
 */

/*
 * �����ޤΰ����ߤΣ��Ų�������꤬�ФƤ���Τǡ�
 * �ߴ��ؿ�����ߴ��ؿ���Ƥ�ǤϤ����ʤ���
 * (�����ߤϥͥ��Ȥ���뤬����������)
 * �����褦�ʽ����򤹤�ؿ��ξ��ϡ�ɬ�� static ���̴ؿ��˽�����ޤȤᡤ
 * ���ä���ƤӽФ��褦�ˤ��뤳�ȡ�
 * ������ɽ��������⤢�뤷�͡�
 */

void rtc_set_datetime(int type, unsigned int value)
{
  printf("call : rtc_set_datetime() : type = %d, value = %d\n",
	 type, (int)value);
  fflush(stdout);

  /* ̤���ݡ��� */
  printf("call : rtc_set_datetime() : not supported\n");

  printf("call : rtc_set_datetime() : return value = none\n");
  fflush(stdout);

  return;
}

unsigned int rtc_get_datetime(int type)
{
  unsigned int ret = 0;
  time_t timer;
  struct tm * tblock;

  printf("call : rtc_get_datetime() : type = %d\n", type);
  fflush(stdout);

  time(&timer);
  tblock = localtime(&timer);

  switch (type) {
  case RTC_YEAR        : ret = get_year(  tblock); break;
  case RTC_MONTH       : ret = get_month( tblock); break;
  case RTC_DATE        : ret = get_day(   tblock); break;
  case RTC_DAY_OF_WEEK : ret = get_week(  tblock); break;
  case RTC_HOUR        : ret = get_hour(  tblock); break;
  case RTC_MIN         : ret = get_minute(tblock); break;
  case RTC_SEC         : ret = get_second(tblock); break;
  default : Wonx_Error("rtc_get_datetime", "Unknown parameter.");
  }

  printf("call : rtc_get_datetime() : return value = %d\n", (int)ret);
  fflush(stdout);

  return (ret);
}

void rtc_set_datetime_struct(datetime_t * d)
{
  printf("call : rtc_set_datetime_struct() : buffer = %p\n", (void *)d);
  fflush(stdout);

  /* ̤���ݡ��� */
  printf("call : rtc_set_datetime_struct() : not supported\n");

  printf("call : rtc_set_datetime_struct() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_get_datetime_struct(datetime_t * d)
{
  time_t timer;
  struct tm * tblock;

  printf("call : rtc_get_datetime_struct() : buffer = %p\n", (void *)d);
  fflush(stdout);

  time(&timer);
  tblock = localtime(&timer);

  d->year = get_year(tblock);
  d->month = get_month(tblock);
  d->date = get_day(tblock);
  d->day_of_week = get_week(tblock);
  d->hour = get_hour(tblock);
  d->minute = get_minute(tblock);
  d->second = get_second(tblock);

  printf("call : rtc_get_datetime_struct() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_enable_alarm(int hour, int minute)
{
  printf("call : rtc_enable_alarm() : hour = %d, minute = %d\n", hour, minute);
  fflush(stdout);

  /* ̤���ݡ��� */
  printf("call : rtc_enable_alarm() : not supported\n");

  printf("call : rtc_enable_alarm() : return value = none\n");
  fflush(stdout);

  return;
}

void rtc_disable_alarm(void)
{
  printf("call : rtc_disable_alarm() : \n");
  fflush(stdout);

  /* ̤���ݡ��� */
  printf("call : rtc_disable_alarm() : not supported\n");

  printf("call : rtc_disable_alarm() : return value = none\n");
  fflush(stdout);

  return;
}

void timer_enable(int type, unsigned int auto_preset, unsigned int count)
{
  WWTimer ww_timer;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : timer_enable() : type = %d, auto_preset = %u, count = %u\n",
	 type, (int)auto_preset, (int)count);
  fflush(stdout);

  /*
   * TIMER_HBLANK �ξ��ϡ�1/(75*144) ��?
   * TIMER_VBLANK �ξ��ϡ�1/75 ��
   * �������ºݤˤ����û�����֤ˤ����� wonx �����褬�Ĥ��Ƥ����ʤ��Τǡ�
   * ������Ĺ��ˤ��Ƥ��롥
   */

  switch (type) {
  case TIMER_VBLANK:
    ww_timer = WonxSystem_GetWWVBlankCountUpTimer(Wonx_GetWonxSystem());
    WWTimer_SetPresetCounter(ww_timer, count * WONX_VBLANK_INTERVAL);
    break;
  case TIMER_HBLANK:
    ww_timer = WonxSystem_GetWWHBlankCountUpTimer(Wonx_GetWonxSystem());
    WWTimer_SetPresetCounter(ww_timer, count * WONX_HBLANK_INTERVAL);
    break;
  default:
    /*
     * ̵��̣������gcc -Wall �ǥ���ѥ��뤹��ȥ�˥󥰤��Ф�Τǡ�
     * NULL �˽�������롥
     */
    ww_timer = NULL;
    Wonx_Error("timer_enable", "Invalid timer type.");
  }

  switch (auto_preset) {
  case TIMER_ONESHOT:    WWTimer_SetAutoPresetOFF(ww_timer); break;
  case TIMER_AUTOPRESET: WWTimer_SetAutoPresetON( ww_timer); break;
  default: Wonx_Error("timer_enable", "Invalid auto preset type.");
  }

  WWTimer_Reset(ww_timer);
  WWTimer_ON(ww_timer);

  printf("call : timer_enable() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void timer_disable(int type)
{
  WWTimer ww_timer;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : timer_disable() : type = %d\n", type);
  fflush(stdout);

  switch (type) {
  case TIMER_VBLANK:
    ww_timer = WonxSystem_GetWWVBlankCountUpTimer(Wonx_GetWonxSystem());
    break;
  case TIMER_HBLANK:
    ww_timer = WonxSystem_GetWWHBlankCountUpTimer(Wonx_GetWonxSystem());
    break;
  default:
    /*
     * ̵��̣������gcc -Wall �ǥ���ѥ��뤹��ȥ�˥󥰤��Ф�Τǡ�
     * NULL �˽�������롥
     */
    ww_timer = NULL;
    Wonx_Error("timer_disable", "Invalid timer type.");
  }

  WWTimer_OFF(ww_timer);

  printf("call : timer_disable() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int timer_get_count(int type)
{
  WWTimer ww_timer;
  unsigned int ret = 0;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : timer_get_count() : type = %d\n", type);
  fflush(stdout);

  switch (type) {
  case TIMER_VBLANK:
    ww_timer = WonxSystem_GetWWVBlankCountUpTimer(Wonx_GetWonxSystem());
    break;
  case TIMER_HBLANK:
    ww_timer = WonxSystem_GetWWHBlankCountUpTimer(Wonx_GetWonxSystem());
    break;
  default:
    /*
     * ̵��̣������gcc -Wall �ǥ���ѥ��뤹��ȥ�˥󥰤��Ф�Τǡ�
     * NULL �˽�������롥
     */
    ww_timer = NULL;
    Wonx_Error("timer_get_count", "Invalid timer type.");
  }

  ret = WWTimer_GetCounter(ww_timer);

  printf("call : timer_get_count() : return value = %u\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
