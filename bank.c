/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/bank.h>

#include "wonx.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

void bank_set_map(int bank, int bank_num)
{
  return;
}

int bank_get_map(int bank)
{
  return (0);
}

unsigned char bank_read_byte(int bank, unsigned int offset)
{
  return (0);
}

void bank_write_byte(int bank, unsigned int offset, unsigned int data)
{
  return;
}

unsigned int bank_read_word(int bank, unsigned int offset)
{
  return (0);
}

void bank_write_word(int bank, unsigned int offset, unsigned int data)
{
  return;
}

void bank_read_block(int bank, unsigned int offset,
		     void * buffer, unsigned int size)
{
  return;
}

void bank_write_block(int bank, unsigned int offset,
		      void * buffer, unsigned int size)
{
  return;
}

void bank_fill_block(int bank, unsigned int offset,
		     unsigned int size, unsigned int data)
{
  return;
}

void bank_erase_flash(int bank)
{
  return;
}
