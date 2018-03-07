/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include "UNIXSerialPortP.h"
#include "WonX.h"
#include "etc.h"

/*****************************************************************************/
/* ���дؿ������                                                          */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* �ݡ��Ȥ� open/close                                                       */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_Open(UNIXSerialPort unix_serial_port)
{
  unix_serial_port->opened = 1;
  return (0);
}
int UNIXSerialPort_Close(UNIXSerialPort unix_serial_port)
{
  unix_serial_port->opened = 0;
  return (0);
}

int UNIXSerialPort_IsOpened(UNIXSerialPort unix_serial_port)
{ return (unix_serial_port->opened != 0); }
int UNIXSerialPort_IsClosed(UNIXSerialPort unix_serial_port)
{ return (unix_serial_port->opened == 0); }

/*---------------------------------------------------------------------------*/
/* �����ǡ��������뤫�ɤ���                                                  */
/*---------------------------------------------------------------------------*/

/*
 * �����ॢ���Ȼ��֤�ߥ���ñ�̤ǻ��ꡥ
 * 0 �ΤȤ��ϡ�¨��
 * -1 �ΤȤ��ϡ�̵�����Ԥ�
 */

int UNIXSerialPort_IsDataExisting(UNIXSerialPort unix_serial_port,
				  int timeout)
{
  fd_set bitmap;
  struct timeval t;
  struct timeval * t_p;
#if 0
  int c;
#endif

  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (0);

  /*
   * 0 �ΤȤ��ϡ�¨��
   * -1 �ΤȤ��ϡ�̵�����Ԥ�
   */
  if (timeout == -1) {
    t_p = NULL;
  } else {
    t.tv_sec  =  timeout / 1000;
    t.tv_usec = (timeout % 1000) * 1000;
    t_p = &t;
  }

  /*
   * FreeBSD3.4 �Ǽ¸������Ȥ���
   * ���顼�ॷ���ʥ����Ѥ����硤select()�ǤΥ֥�å����
   * ���顼�ॷ���ʥ뤬ȯ������ȡ�����ľ���select()�⥿���ॢ����
   * ���Ƥ��ޤ��Τǡ���ա�
   * (select() �������ॢ���Ȥ�����˥��顼�ॷ���ʥ뤬ȯ��������ϡ�
   *  �����ư���)
   * ����������̵꤬���������Ԥ������֤����ԤäƤ���ʤ��Ȥ������ݤ�
   * �������ǽ�������롥
   */

#if 0
  /* �ɤ����Ф�����ʸ��������Ȥ��ϡ����ä��Υ����ɤ�Ȥ� */
  do {
    FD_ZERO(&bitmap);
    FD_SET(fileno(stdin), &bitmap);
    select(fileno(stdin) + 1, &bitmap, NULL, NULL, t_p);

    if (!FD_ISSET(fileno(stdin), &bitmap))
      return (0);

    c = fgetc(stdin);
  } while (0); /* �ɤ����Ф�����ʸ��������Ȥ��ϡ�������c������å����� */
  ungetc(c, stdin);
#else
  FD_ZERO(&bitmap);
  FD_SET(fileno(stdin), &bitmap);
  select(fileno(stdin) + 1, &bitmap, NULL, NULL, t_p);

  if (!FD_ISSET(fileno(stdin), &bitmap))
    return (0);
#endif

  return (1);
}

/*---------------------------------------------------------------------------*/
/* ����                                                                      */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_ReceiveCharacter(UNIXSerialPort unix_serial_port,
				    int timeout)
{
  int c;

  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (-1);

  c = UNIXSerialPort_IsDataExisting(unix_serial_port, timeout)
    ? fgetc(stdin) : -1;
  c = (c == '\n') ? '\r' : c; /* \r �Υ��ߥ�졼����� */

  return (c);
}

/*---------------------------------------------------------------------------*/
/* ����                                                                      */
/*---------------------------------------------------------------------------*/

int UNIXSerialPort_SendCharacter(UNIXSerialPort unix_serial_port,
				 unsigned char c)
{
  if (UNIXSerialPort_IsClosed(unix_serial_port)) return (0);

  wonx_print_character(stdout, c);

  return (1);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ���                                                        */
/*---------------------------------------------------------------------------*/

UNIXSerialPort UNIXSerialPort_Create()
{
  UNIXSerialPort unix_serial_port;

  unix_serial_port = (UNIXSerialPort)malloc(sizeof(_UNIXSerialPort));
  if (unix_serial_port == NULL)
    WonX_Error("UNIXSerialPort_Create", "Cannot allocate memory.");

  unix_serial_port->opened = 0;

  return (unix_serial_port);
}

/*---------------------------------------------------------------------------*/
/* ���֥������Ȥκ��                                                        */
/*---------------------------------------------------------------------------*/

UNIXSerialPort UNIXSerialPort_Destroy(UNIXSerialPort unix_serial_port)
{
  if (unix_serial_port == NULL)
    WonX_Error("UNIXSerialPort_Destroy", "Object is not created.");

  if (UNIXSerialPort_IsOpened(unix_serial_port))
    UNIXSerialPort_Close(unix_serial_port);

  free(unix_serial_port);

  return (NULL);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
