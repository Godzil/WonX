/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/bank.h"

#include "WonX.h"

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

void bank_set_map(int bank, int bank_num)
{
  return;
}

int bank_get_map(int bank)
{
  return (0);
}

unsigned char bank_read_byte(int bank, unsigned int off)
{
  return (0);
}

void bank_write_byte(int bank, unsigned int off, unsigned int data)
{
  return;
}

unsigned int bank_read_word(int bank, unsigned int off)
{
  return (0);
}

void bank_write_word(int bank, unsigned int off, unsigned int data)
{
  return;
}

void bank_read_block(int bank, unsigned int off,
		     void * buffer, unsigned int size)
{
  return;
}

void bank_write_block(int bank, unsigned int off,
		      void * buffer, unsigned int size)
{
  return;
}

void bank_fill_block(int bank, unsigned int off,
		     unsigned int size, unsigned int data)
{
  return;
}

void bank_erase_flash(int bank)
{
  return;
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
