/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include "wonx_configure.h"

#include "WonXSystemP.h"
#include "WonX.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

WWInterrupt WonXSystem_GetWWInterrupt(WonXSystem wonx_system)
{ return (wonx_system->ww_interrupt); }
WWInterrupt WonXSystem_SetWWInterrupt(WonXSystem wonx_system,
				      WWInterrupt ww_interrupt)
{ return (wonx_system->ww_interrupt = ww_interrupt); }

WWTimer WonXSystem_GetWWTimer(WonXSystem wonx_system, int type)
{ return (wonx_system->ww_timer[type]); }
WWTimer WonXSystem_SetWWTimer(WonXSystem wonx_system, int type, WWTimer t)
{ return (wonx_system->ww_timer[type] = t); }

WWTimer WonXSystem_GetWWVBlankTimer(WonXSystem wonx_system)
{ return (WonXSystem_GetWWTimer(wonx_system, 0)); }
WWTimer WonXSystem_SetWWVBlankTimer(WonXSystem wonx_system, WWTimer t)
{ return (WonXSystem_SetWWTimer(wonx_system, 0, t)); }

WWTimer WonXSystem_GetWWVBlankCountUpTimer(WonXSystem wonx_system)
{ return (WonXSystem_GetWWTimer(wonx_system, 1)); }
WWTimer WonXSystem_SetWWVBlankCountUpTimer(WonXSystem wonx_system, WWTimer t)
{ return (WonXSystem_SetWWTimer(wonx_system, 1, t)); }

WWTimer WonXSystem_GetWWHBlankCountUpTimer(WonXSystem wonx_system)
{ return (WonXSystem_GetWWTimer(wonx_system, 2)); }
WWTimer WonXSystem_SetWWHBlankCountUpTimer(WonXSystem wonx_system, WWTimer t)
{ return (WonXSystem_SetWWTimer(wonx_system, 2, t)); }

UNIXTimer WonXSystem_GetUNIXTimer(WonXSystem wonx_system)
{ return (wonx_system->unix_timer); }
UNIXTimer WonXSystem_SetUNIXTimer(WonXSystem wonx_system,
				  UNIXTimer unix_timer)
{ return (wonx_system->unix_timer = unix_timer); }

static int WonXTimer_Callback(WonXSystem wonx_system)
{
  WWTimer ww_timer;
  WWInterrupt ww_interrupt;
  WonXDisplay wonx_display;
  XDisplay x_display;
  WonXSerialPort wonx_serial_port;
  WWSerialPort ww_serial_port;
  UNIXSerialPort unix_serial_port;

  unsigned int old_key;
  unsigned int new_key;

  ww_interrupt = WonXSystem_GetWWInterrupt(wonx_system);

  wonx_display = WonX_GetWonXDisplay();
  x_display = WonXDisplay_GetXDisplay(wonx_display);

  wonx_serial_port = WonX_GetWonXSerialPort();
  ww_serial_port = WonXSerialPort_GetWWSerialPort(wonx_serial_port);
  unix_serial_port = WonXSerialPort_GetUNIXSerialPort(wonx_serial_port);

  ww_timer = WonXSystem_GetWWVBlankTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteVBlankCallback(ww_interrupt);
  }

  ww_timer = WonXSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteTimerCountUpCallback(ww_interrupt);
  }

  ww_timer = WonXSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (WWTimer_IsON(ww_timer)) {
    if (WWTimer_Count(ww_timer))
      WWInterrupt_ExecuteHBlankCountUpCallback(ww_interrupt);
  }

  /* �������ϳ����� */
  /*
   * XDisplay_Flush() ��¾�ΤȤ�����ƤФ줿���˳����ߤ�Ȥ�
   * ���ܤ��Ƥ��ޤ��Τǡ�XDisplay ���饹�Τۤ��ǳ����ߤν����򤹤뤫��
   * �ե饰��Ω�Ƥ�褦�˲��ɤ���ɬ�פ�ͭ�뤫�⡥
   * (�̤ξ������ˤ� XDisplay_Flush() ���ƤФ�Ƥ���ȡ����������ߤ�
   *  ȯ�����ʤ��ʤäƤ��ޤ�)
   * �Ȥꤢ�����ϴʰ�Ū�ˤ��Τ褦�ʼ����ˤ��Ƥ���������̵��������
   */
  old_key = XDisplay_GetKeyPress(x_display);
  XDisplay_Flush(x_display);
  new_key = XDisplay_GetKeyPress(x_display);
  /* �����������������줿��� */
  /*
   * WonderWitch �Ǽ¸������Ȥ���������Υ�������ˤϳ����ߤ�
   * ������ʤ��褦���ä��Τǡ������줿�Ȥ��Τߥ�����Хå��ؿ���ƤӽФ���
   */
  if (new_key & (~old_key)) {
    WWInterrupt_ExecuteKeyCallback(ww_interrupt);
  }

  /* ���ꥢ����������� */
  /*
   * ���Ʊ����ͳ�ǳ����ߤ�Ȥꤳ�ܤ���ǽ����ͭ��Τǡ�UNIXSerialPort ��
   * �ۤ��ǳ����ߤν����򤹤뤫���ե饰��Ω�Ƥ�褦�˲��ɤ���ɬ�פ�ͭ�뤫�⡥
   * �Ȥꤢ�����ϴʰ�Ū�ˤ��Τ褦�ʼ����ˤ��Ƥ���������̵��������
   */
  if (WWSerialPort_IsOpened(ww_serial_port) &&
      UNIXSerialPort_IsOpened(unix_serial_port)) {
    if (UNIXSerialPort_IsDataExisting(unix_serial_port, 0))
      WWInterrupt_ExecuteReceiveReadyCallback(ww_interrupt);
  }

  WonXDisplay_PrintData(wonx_display);

  return (0);
}

WonXSystem WonXSystem_Create()
{
  WonXSystem wonx_system;
  WWInterrupt ww_interrupt;
  WWTimer ww_timer;
  UNIXTimer unix_timer;

  wonx_system = (WonXSystem)malloc(sizeof(_WonXSystem));
  if (wonx_system == NULL)
    WonX_Error("WonXSystem_Create", "Cannot allocate memory.");

  ww_interrupt = WWInterrupt_Create();
  if (ww_interrupt == NULL)
    WonX_Error("WonXSystem_Create", "Cannot create WonderWitch interrupt.");
  WonXSystem_SetWWInterrupt(wonx_system, ww_interrupt);

  ww_timer = WWTimer_Create(1, WONX_VBLANK_INTERVAL);
  if (ww_timer == NULL)
    WonX_Error("WonXSystem_Create", "Cannot create WonderWitch VBlank timer.");
  WonXSystem_SetWWVBlankTimer(wonx_system, ww_timer);

  ww_timer = WWTimer_Create(0, WONX_VBLANK_INTERVAL);
  if (ww_timer == NULL)
    WonX_Error("WonXSystem_Create",
	       "Cannot create WonderWitch VBlank count up timer.");
  WonXSystem_SetWWVBlankCountUpTimer(wonx_system, ww_timer);

  ww_timer = WWTimer_Create(0, WONX_HBLANK_INTERVAL);
  if (ww_timer == NULL)
    WonX_Error("WonXSystem_Create",
	       "Cannot create WonderWitch HBlank count up timer.");
  WonXSystem_SetWWHBlankCountUpTimer(wonx_system, ww_timer);

  WWTimer_Reset(WonXSystem_GetWWVBlankTimer(       wonx_system));
  WWTimer_Reset(WonXSystem_GetWWVBlankCountUpTimer(wonx_system));
  WWTimer_Reset(WonXSystem_GetWWHBlankCountUpTimer(wonx_system));

  WWTimer_ON( WonXSystem_GetWWVBlankTimer(       wonx_system));
  WWTimer_OFF(WonXSystem_GetWWVBlankCountUpTimer(wonx_system));
  WWTimer_OFF(WonXSystem_GetWWHBlankCountUpTimer(wonx_system));

  unix_timer = UNIXTimer_Create(1, WONX_TIMER_INTERVAL, wonx_system,
				(UNIXTimerCallBack)WonXTimer_Callback);
  if (unix_timer == NULL)
    WonX_Error("WonXSystem_Create", "Cannot create UNIX timer.");
  WonXSystem_SetUNIXTimer(wonx_system, unix_timer);

  UNIXTimer_ON(unix_timer);

  return (wonx_system);
}

WonXSystem WonXSystem_Destroy(WonXSystem wonx_system)
{
  WWInterrupt wi;
  WWTimer wt;
  UNIXTimer unix_timer;

  if (wonx_system == NULL)
    WonX_Error("WonXSystem_Destroy", "Object is not created.");

  unix_timer = WonXSystem_GetUNIXTimer(wonx_system);

  if (unix_timer)
    UNIXTimer_OFF(unix_timer);

  wt = WonXSystem_GetWWVBlankTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);
  wt = WonXSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);
  wt = WonXSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (wt) WWTimer_OFF(wt);

  if (unix_timer)
    WonXSystem_SetUNIXTimer(wonx_system, UNIXTimer_Destroy(unix_timer));

  wt = WonXSystem_GetWWVBlankTimer(wonx_system);
  if (wt) WonXSystem_SetWWVBlankTimer(wonx_system, WWTimer_Destroy(wt));
  wt = WonXSystem_GetWWVBlankCountUpTimer(wonx_system);
  if (wt) WonXSystem_SetWWVBlankCountUpTimer(wonx_system, WWTimer_Destroy(wt));
  wt = WonXSystem_GetWWHBlankCountUpTimer(wonx_system);
  if (wt) WonXSystem_SetWWHBlankCountUpTimer(wonx_system, WWTimer_Destroy(wt));

  wi = WonXSystem_GetWWInterrupt(wonx_system);
  if (wi) WonXSystem_SetWWInterrupt(wonx_system, WWInterrupt_Destroy(wi));

  free(wonx_system);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
