/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/comm.h"

#include "Wonx.h"

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
{}

void comm_close(void)
{}

int comm_send_char(unsigned char c)
{
  return (0);
}

int comm_receive_char(void)
{
  return (0);
}

int comm_receive_with_timeout(int timeout)
{
  return (0);
}

int comm_send_string(char * string)
{
  return (0);
}

int comm_send_block(void * buffer, int size)
{
  return (0);
}

int comm_receive_block(void * buffer, int size)
{
  return (0);
}

void comm_set_timeout(int recv_timeout, int send_timeout)
{
}

void comm_set_baudrate(int baudrate)
{
}

int comm_get_baudrate(void)
{
  return (0);
}

void comm_set_cancel_key(unsigned int pattern)
{
}

unsigned int comm_get_cancel_key(void)
{
  return (0);
}

int comm_xmodem(void * xmodem)
{
  return (0);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
