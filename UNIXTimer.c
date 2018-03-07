/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <unistd.h>
#include <signal.h>

#include "UNIXTimerP.h"
#include "etc.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* ������Хå��ؿ�                                                          */
/*---------------------------------------------------------------------------*/

/* pointed_unix_timer ���ͤϤ����Ѳ����뤫�狼��ʤ��Τǡ���Ŭ����ػߤ��� */

volatile static UNIXTimer pointed_unix_timer = NULL;

static void UNIXTimer_CallBackFunction(int argument)
{
  int ret;

  /*
   * static �ʥե饰��Ω�Ƥơ�������Хå��ؿ����饳����Хå��ؿ���
   * �ƤФ줿�Τ򸡽Ф���Τ�ɬ�פ��⡥
   */

  if (pointed_unix_timer == NULL) return;
  if (!pointed_unix_timer->timer_on) return;

  if (pointed_unix_timer->pause) {
    pointed_unix_timer->interrupt_in_pause++;
  } else {
    if (pointed_unix_timer->interrupt_in_pause == 0)
      pointed_unix_timer->interrupt_in_pause = 1;
    while (pointed_unix_timer->interrupt_in_pause > 0) {
      pointed_unix_timer->interrupt_in_pause--;
      if (pointed_unix_timer->callback != NULL) {

	/*
	 * ������Хå��ؿ����椫�� UNIXTimer_Unpause() �ʤɤ��ƤФ�ơ�
	 * �������餵��˥�����Хå��ؿ����ƤФ줿�ꤷ���Ȥ��Τ���ˡ�
	 * �ݡ������롥
	 */
	pointed_unix_timer->pause++;

	ret = (*pointed_unix_timer->callback)(pointed_unix_timer->parameter);

	pointed_unix_timer->pause--;

	/*
	 * ������Хå��ؿ������ UNIXTimer_* ��Ϣ�δؿ����ƤӽФ����ȡ�
	 * ������ UNIXTimer ���֥������Ȥξ��֤��Ѥ�äƤ��ޤ���ǽ�������롥
	 */

	/*
	 * �ʲ��ν�����Ʊ�����Ȥ�ؿ�����Ƭ�Ǥ�äƤ���Τǡ�
	 * ��Ŭ������ƺ������ʤ��褦����դ��뤳�ȡ�
	 */
	if (pointed_unix_timer == NULL) return;
	if (!pointed_unix_timer->timer_on) return;

	if (ret) {
	  pointed_unix_timer->interrupt_in_pause = 0;
	  UNIXTimer_OFF(pointed_unix_timer);
	  return;
	}

	/*
	 * ������Хå��ؿ���ǡ��ݡ����ξ��֤��ڤ��ؤ�äƤ��ޤä�
	 * �Ȥ��Τ��ᡥ
	 * �ʲ��ν�����Ʊ���褦�ʤ��Ȥ����ä����ˤ�äƤ���Τǡ�
	 * ��Ŭ������ƺ������ʤ��褦����դ��뤳�ȡ�
	 */
	if (pointed_unix_timer->pause) break;

      }
    }
  }

  if (pointed_unix_timer->auto_preset)
    UNIXTimer_ON(pointed_unix_timer);
  else
    UNIXTimer_OFF(pointed_unix_timer);

  return;
}

/*---------------------------------------------------------------------------*/
/* �����ޤ� ON, OFF                                                          */
/*---------------------------------------------------------------------------*/

/*
 * ���Τ�����ν����ϡ�������˥����޳����ߤ�ȯ�����ʤ����ɤ�����
 * �����դ��뤳�ȡ��Ǥʤ����ԲĲ�ʥХ��θ����ˤʤ롥
 */

int UNIXTimer_ON(UNIXTimer unix_timer)
{
  int t;

  unix_timer->timer_on = 1;
  pointed_unix_timer = unix_timer;

  /*
   * SIGALRM ����Ѥ���Τǡ�sleep() ��˥��顼�ब���������ˤϡ�
   * ������Хå��ؿ������������� sleep() �λĤ���֤Ϸ�³����ʤ���
   */
  signal(SIGALRM, UNIXTimer_CallBackFunction);

#if 0 /* use ualarm() */
  /* ualarm(); �ΰ�����0���Ѥ��Ƥϥ���ʤΤ� */
  t = unix_timer->interval * 1000;
  if (t < 1) t = 1;
  ualarm(t, 0);
#else /* use alarm() */
  /* alarm(); �ΰ�����0���Ѥ��Ƥϥ���ʤΤ� */
  t = unix_timer->interval / 1000;
  if (t < 1) t = 1;
  alarm(t);
#endif

  return (0);
}

int UNIXTimer_OFF(UNIXTimer unix_timer)
{
  alarm(0); /* �����ޤ�̵���ˤ��� */
  unix_timer->timer_on = 0;
  pointed_unix_timer = NULL;
  return (0);
}

int UNIXTimer_IsON(UNIXTimer unix_timer)
{ return (unix_timer->timer_on != 0); }
int UNIXTimer_IsOFF(UNIXTimer unix_timer)
{ return (unix_timer->timer_on == 0); }

/*---------------------------------------------------------------------------*/
/* ������                                                                  */
/*---------------------------------------------------------------------------*/

/*
 * �ؿ�����Ƭ�������� Pause, Unpause �Ǥ�����Ф����ʤɤϡ�
 * �ؿ�����ؿ���ƤӽФ����Ȥ��ˡ����� Pause, Unpause ��������Τ�
 * ��դ��뤳�ȡ�(���������ݡ����ϥͥ��ȤǤ���)
 */

/*
 * �ݡ����ϥͥ��Ȥ����Τǡ�UNIXTimer_Unpause() ��°פ˷����֤��Ƥ����
 * ���ʤ��褦����դ��뤳�ȡ�
 */

/*
 * ���Τ�����ν����ϡ�������˥����޳����ߤ�ȯ�����ʤ����ɤ�����
 * �����դ��뤳�ȡ��Ǥʤ����ԲĲ�ʥХ��θ����ˤʤ롥
 */

int UNIXTimer_Pause(UNIXTimer unix_timer)
{
  unix_timer->pause++; /* �ݡ����ϥͥ��ȤǤ��� */

  return (0);
}

int UNIXTimer_Unpause(UNIXTimer unix_timer)
{
  if (unix_timer->pause == 0)
    Wonx_Error("UNIXTimer_Unpause", "Duplicated unpause.");

  if (unix_timer->pause == 1) {
    if (unix_timer->interrupt_in_pause > 0) {

      /*
       * �����졤�����ǥ����޳����ߤ�ȯ�����Ƥ⡤
       * unix_timer->pause �� 1 �ʤΤǡ�������Хå��ؿ��ϸƤФ�ʤ��Τǡ�
       * ����̵����
       * �����ȥץꥻ�åȤʤ�С��٤Ĥ�����̵����
       * �����ȥץꥻ�åȤǤʤ���� timer_on �ե饰�������Τǡ�����̵����
       */

      /*
       * ������˥����޳����ߤ�ȯ����������ݤʤΤǡ�
       * �����ޤ򤤤ä���̵���ˤ��롥
       */
      alarm(0);

      /*
       * �����ͤ��ѹ�����ľ����ľ��ǳ����ߤ���������ݤʤΤǡ�
       * �����ߤ�OFF�ˤ��Ƥ���ǥ�����Ȥ��롥
       */
      /* ������Хå��ؿ���Ƥ����ˡ�pause �ե饰��̵���ˤ��� */
      unix_timer->pause--; /* �ݡ����ϥͥ��ȤǤ��� */

      /* ������Хå��ؿ��θƤӽФ� */
      UNIXTimer_CallBackFunction(0);
    }
  } else {
    unix_timer->pause--; /* �ݡ����ϥͥ��ȤǤ��� */
  }

  return (0);
}

int UNIXTimer_IsPause(UNIXTimer unix_timer)
{ return (unix_timer->pause != 0); }

/*---------------------------------------------------------------------------*/
/* �����ȥץꥻ�å�                                                          */
/*---------------------------------------------------------------------------*/

int UNIXTimer_SetAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset = 1); }
int UNIXTimer_ResetAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset = 0); }
int UNIXTimer_IsAutoPreset(UNIXTimer unix_timer)
{ return (unix_timer->auto_preset != 0); }

/*---------------------------------------------------------------------------*/
/* ���󥿡��Х�                                                              */
/*---------------------------------------------------------------------------*/

int UNIXTimer_GetInterval(UNIXTimer unix_timer)
{ return (unix_timer->interval); }
int UNIXTimer_SetInterval(UNIXTimer unix_timer, int interval)
{ return (unix_timer->interval = interval); }

/*---------------------------------------------------------------------------*/
/* ������Хå��ؿ��θƤӽФ����Υѥ�᡼��                                  */
/*---------------------------------------------------------------------------*/

void * UNIXTimer_GetParameter(UNIXTimer unix_timer)
{ return (unix_timer->parameter); }
void * UNIXTimer_SetParameter(UNIXTimer unix_timer, void * parameter)
{ return (unix_timer->parameter = parameter); }

/*---------------------------------------------------------------------------*/
/* ������Хå��ؿ��μ�������Ͽ                                              */
/*---------------------------------------------------------------------------*/

UNIXTimerCallBack UNIXTimer_GetCallBack(UNIXTimer unix_timer)
{ return (unix_timer->callback); }
UNIXTimerCallBack UNIXTimer_SetCallBack(UNIXTimer unix_timer,
					UNIXTimerCallBack callback)
{ return (unix_timer->callback = callback); }

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ���                                                        */
/*---------------------------------------------------------------------------*/

UNIXTimer UNIXTimer_Create(int auto_preset, int interval, void * parameter,
			   UNIXTimerCallBack callback)
{
  UNIXTimer unix_timer;

  unix_timer = (UNIXTimer)malloc(sizeof(_UNIXTimer));
  if (unix_timer == NULL)
    Wonx_Error("UNIXTimer_Create", "Cannot allocate memory.");

  unix_timer->timer_on           = 0;
  unix_timer->pause              = 0;
  unix_timer->interrupt_in_pause = 0;
  unix_timer->auto_preset        = 0;
  unix_timer->interval           = 0;
  unix_timer->parameter          = NULL;
  unix_timer->callback           = NULL;

  if (auto_preset) UNIXTimer_SetAutoPreset(unix_timer);
  else UNIXTimer_ResetAutoPreset(unix_timer);

  UNIXTimer_SetInterval(unix_timer, interval);
  UNIXTimer_SetParameter(unix_timer, parameter);
  UNIXTimer_SetCallBack(unix_timer, callback);

  return (unix_timer);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

/*
 * ���Τ�����ν����ϡ�������˥����޳����ߤ�ȯ�����ʤ����ɤ�����
 * �����դ��뤳�ȡ��Ǥʤ����ԲĲ�ʥХ��θ����ˤʤ롥
 */

UNIXTimer UNIXTimer_Destroy(UNIXTimer unix_timer)
{
  if (unix_timer == NULL)
    Wonx_Error("UNIXTimer_Destroy", "Object is not created.");

  UNIXTimer_OFF(unix_timer);

  free(unix_timer);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
