/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include "wonx_include/comm.h"

#include "wonx_configure.h"
#include "Wonx.h"
#include "etc.h"

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

void comm_open(void)
{
  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_open() : \n");
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_open", "Serial port has already opened.");

  WWSerialPort_ON(ww_serial_port);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_open() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void comm_close(void)
{
  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_close() : \n");
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_close", "Serial port is not opened.");

  WWSerialPort_OFF(ww_serial_port);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_close() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

static void comm_output(unsigned char c)
{
  if      (c == '\n') printf("\\n");
  else if (c == '\r') printf("\\r");
  else if (c == '\t') printf("\\t");
  else if (isprint(c)) fputc(c, stdout);
  else printf("^%02x", (int)c);
  fflush(stdout);
  return;
}

static int comm_input(int timeout)
{
  int tmp;
  int c;
  fd_set bitmap;
  struct timeval t;
  struct timeval * t_p;

  /*
   * 0 �ΤȤ��ϡ�¨��
   * -1 �ΤȤ��ϡ�̵�����Ԥ�
   */
  if (timeout == -1) {
    t_p = NULL;
  } else {
    tmp = WONX_SERIAL_PORT_TIMETICKS * timeout;
    t.tv_sec  =  tmp / 1000;
    t.tv_usec = (tmp % 1000) * 1000;
    t_p = &t;
  }

  FD_ZERO(&bitmap);
  FD_SET(fileno(stdin), &bitmap);

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
  select(fileno(stdin) + 1, &bitmap, NULL, NULL, t_p);

  c = FD_ISSET(fileno(stdin), &bitmap) ? fgetc(stdin) : -1;

  return (c);
}

int comm_send_char(unsigned char c)
{
  int ret;

  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_send_char() : character = 0x%02x\n", (int)c);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_send_char", "Serial port is not opened.");

  printf("output to serial port : ");
  comm_output(c);
  printf("\n");
  fflush(stdout);
  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_send_char() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_receive_char(void)
{
  WWSerialPort ww_serial_port;
  int c;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_receive_char() : \n");
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_receive_char", "Serial port is not opened.");

  c = comm_input(WWSerialPort_GetReceiveTimeout(ww_serial_port));

  if (c == -1) ret = ERR_SIO_TIMEOUT;
  else ret = c;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_receive_char() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_receive_with_timeout(int timeout)
{
  WWSerialPort ww_serial_port;
  int c;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_receive_with_timeout() : timeout = %d\n", timeout);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_receive_with_timeout", "Serial port is not opened.");

  c = comm_input(timeout);

  if (c == -1) ret = ERR_SIO_TIMEOUT;
  else ret = c;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_receive_with_timeout() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_send_string(char * string)
{
  WWSerialPort ww_serial_port;
  int ret;
  int i;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_send_string() : string = %s\n", string);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_send_string", "Serial port is not opened.");

  printf("output to serial port : ");
  for (i = 0; string[i]; i++) {
    comm_output(string[i]);
  }
  printf("\n");
  fflush(stdout);
  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_send_string() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_send_block(void * buffer, int size)
{
  WWSerialPort ww_serial_port;
  int ret;
  int i;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_send_block() : buffer = %p, size = %d\n", buffer, size);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_send_block", "Serial port is not opened.");

  printf("output to serial port : ");
  for (i = 0; i < size; i++) {
    comm_output(((char *)buffer)[i]);
  }
  printf("\n");
  fflush(stdout);
  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_send_block() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_receive_block(void * buffer, int size)
{
  WWSerialPort ww_serial_port;
  int ret;
  int c;
  int i;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_receive_block() : buffer = %p, size = %d\n",
	 buffer, size);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (!WWSerialPort_IsON(ww_serial_port))
    Wonx_Error("comm_receive_block", "Serial port is not opened.");

  ret = 0;
  for (i = 0; i < size; i++) {
    c = comm_input(WWSerialPort_GetReceiveTimeout(ww_serial_port));
    if (c == -1) {
      ret = ERR_SIO_TIMEOUT;
      break;
    }
    ((char *)buffer)[i] = c;
  }

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_receive_block() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void comm_set_timeout(int recv_timeout, int send_timeout)
{
  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_set_timeout() : receive_timeout = %d, send_timeout = %d\n", recv_timeout, send_timeout);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  WWSerialPort_SetReceiveTimeout(ww_serial_port, recv_timeout);
  WWSerialPort_SetSendTimeout(   ww_serial_port, send_timeout);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_set_timeout() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

void comm_set_baudrate(int baudrate)
{
  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_set_baudrate() : baudrate = %d\n", baudrate);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  switch (baudrate) {
  case COMM_SPEED_9600:  WWSerialPort_SetBaudrate9600( ww_serial_port); break;
  case COMM_SPEED_38400: WWSerialPort_SetBaudrate38400(ww_serial_port); break;
  default: Wonx_Error("comm_set_baudrate", "Invalid baudrate");
  }

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_set_baudrate() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

int comm_get_baudrate(void)
{
  WWSerialPort ww_serial_port;
  int ret = 0;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_get_baudrate() : \n");
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  if (WWSerialPort_IsBaudrate9600(ww_serial_port))
    ret = COMM_SPEED_9600;
  else if (WWSerialPort_IsBaudrate38400(ww_serial_port))
    ret = COMM_SPEED_38400;
  else Wonx_Error("comm_get_baudrate", "Invalid baudrate");

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_get_baudrate() : return value = %d\n", ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

void comm_set_cancel_key(unsigned int pattern)
{
  WWSerialPort ww_serial_port;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_set_cancel_key() : pattern = %u\n", (int)pattern);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  WWSerialPort_SetCancelKey(ww_serial_port, pattern);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_set_cancel_key() : return value = none\n");
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return;
}

unsigned int comm_get_cancel_key(void)
{
  WWSerialPort ww_serial_port;
  unsigned int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_get_cancel_key() : \n");
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  /* �����˽������ */
  ret = WWSerialPort_GetCancelKey(ww_serial_port);

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_get_cancel_key() : return value = %u\n", (int)ret);
  fflush(stdout);

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  return (ret);
}

int comm_xmodem(void * xmodem)
{
  WWSerialPort ww_serial_port;
  int ret;

  if (!Wonx_IsCreated()) Wonx_Create();

  /* �����ޤ�����ߤ��� */
  UNIXTimer_Pause(WonxSystem_GetUNIXTimer(Wonx_GetWonxSystem()));

  printf("call : comm_xmodem() : xmodem = %p\n", xmodem);
  fflush(stdout);

  ww_serial_port = WonxSerialPort_GetWWSerialPort(Wonx_GetWonxSerialPort());

  /* ̤���ݡ��� */
  printf("call : comm_xmodem() : not supported.\n");
  fflush(stdout);
  ret = 0;

  WonxDisplay_Sync(Wonx_GetWonxDisplay());

  printf("call : comm_xmodem() : return value = %d\n", ret);
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
