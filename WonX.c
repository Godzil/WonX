#include "WonXP.h"
#include "etc.h"

#include "wonx/disp.h"
#include "wonx/system.h"
#include "wonx/comm.h"

static WonX wonx = NULL;

int WonX_IsCreated(void)
{
  return (wonx != NULL);
}

void WonX_Create(void)
{
  if (WonX_IsCreated())
    WonX_Error("WonX_Create", "WonX has been already created.");

  wonx = (WonX)malloc(sizeof(_WonX));
  if (wonx == NULL) WonX_Error("WonX_Create", "Cannot allocate memory.");

  /*
   * WonX �Υ����ޤ���ϥǥ����ץ쥤�Υ�ե�å���ʤɤδؿ���ƤӽФ����ᡤ
   * WonXSystem_Create() �ǥ����ޤ򥹥����Ȥ��������� WonXDisplay_Create() ��
   * WonXDisplay ���֥������Ȥ�������Ƥ���ɬ�פ����롥���Τ���
   * WonXDisplay_Create() �� WonXSystem_Create() �θ�˻��äƤ��äƤϤ����ʤ���
   */
  wonx->wonx_display =
    WonXDisplay_Create(LCD_PIXEL_WIDTH * 2, LCD_PIXEL_HEIGHT * 2,
                       LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT,
		       SCREEN_CHAR_WIDTH, SCREEN_CHAR_HEIGHT);

  /*
   * WonXDisplay ��Ʊ�ͤΤ��Ȥ� WonXSerialPort �Ǥ⾭��Ū�˵������ǽ����
   * ���뤫�⤷��ʤ��Τǡ� WonXSerialPort_Create() �⤤������
   * WonXSystem_Create() �������֤��Ƥ�����
   */
  wonx->wonx_serial_port = WonXSerialPort_Create();

  /*
   * WonXSystem_Create() �Ǥϥ����ޤ�������뤬�������ޤ���Ϥ������
   * ���֥������Ȥ��ƤФ���ǽ�������뤿�ᡤ�����ޤκ����ϰ��ֺǸ�˹Ԥ�
   * �٤��Ǥ��롥���Τ��ᡤWonXSystem_Create() �ϰ��ֺǸ�˹Ԥ���
   * (¾�Υ��֥������Ȥκ��������˥����ޤ������ä���硤�������ʤ��Ȥ�
   *  �ʤäƤ��ޤ�)
   */
  wonx->wonx_system = WonXSystem_Create();

  return;
}

void WonX_Destroy(void)
{
  if (!WonX_IsCreated())
    WonX_Error("WonX_Destroy", "WonX has not been created yet.");

  /*
   * WonXSystem �ϥ����ޤ���Ĥ��������ޤ���Ϥ�����ʥ��֥������Ȥ�
   * �ƤФ���ǽ�������뤿�ᡤ���ֺǽ�˥����ޤ���ߤ���ɬ�פ����롥
   * ���Τ��ᡤWonXSystem_Destroy() �ϰ��ֺǽ�˹Ԥ���
   * (¾�Υ��֥������Ȥκ�������˥����ޤ������ä���硤�������ʤ��Ȥ�
   *  �ʤäƤ��ޤ�)
   */
  if (wonx->wonx_system)
    wonx->wonx_system = WonXSystem_Destroy(wonx->wonx_system);

  /*
   * WonXDisplay ��Ʊ�ͤΤ��Ȥ� WonXSerialPort �Ǥ⾭��Ū�˵������ǽ����
   * ���뤫�⤷��ʤ��Τǡ� WonXSerialPort_Destroy() �⤤������
   * WonXSystem_Destroy() �θ���֤��Ƥ�����
   */
  if (wonx->wonx_serial_port)
    wonx->wonx_serial_port = WonXSerialPort_Destroy(wonx->wonx_serial_port);

  /*
   * WonX �Υ����ޤ���ϥǥ����ץ쥤�Υ�ե�å���ʤɤδؿ���ƤӽФ����ᡤ
   * WonXDisplay ��õ������ WonXSystem ��õ�ơ������ޤ���ߤ���
   * ɬ�פ����롥(�Ǥʤ��� WonXDisplay_Destroy() �μ¹���˥����ޤ������ä�
   * �Ȥ��ˡ��������ʤ��Ȥˤʤ�)
   * ���Τ��ᡤWonXDisplay_Destroy() �� WonXSystem_Destroy() ������
   * ���äƤ��äƤϤ����ʤ���
   */
  if (wonx->wonx_display)
    wonx->wonx_display = WonXDisplay_Destroy(wonx->wonx_display);

  free(wonx);
  wonx = NULL;

  return;
}

WonXDisplay WonX_GetWonXDisplay(void)
{
  return (wonx->wonx_display);
}

WonXSystem WonX_GetWonXSystem(void)
{
  return (wonx->wonx_system);
}

WonXSerialPort WonX_GetWonXSerialPort(void)
{
  return (wonx->wonx_serial_port);
}

/*===========================================================================*/
/* ���顼����                                                                */
/*===========================================================================*/

int WonX_Error(char * funcname, char * message)
{
  fprintf(stderr, "error : %s(): %s\n", funcname, message);
  exit (1);
}

int WonX_Warning(char * funcname, char * message)
{
  fprintf(stderr, "warning : %s(): %s\n", funcname, message);
  return (0);
}

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
