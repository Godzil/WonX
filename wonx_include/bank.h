#ifndef _WONX_SYS_BANK_H_
#define _WONX_SYS_BANK_H_

#include "service.h"

/*****************************************************************************/
/* 定数の定義                                                                */
/*****************************************************************************/

#define BANK_SRAM 0
#define BANK_ROM0 1
#define BANK_ROM1 2

#define sram_get_map()     bank_get_map(BANK_SRAM)
#define rom0_get_map()     bank_get_map(BANK_ROM0)
#define rom1_get_map()     bank_get_map(BANK_ROM1)
#define sram_set_map(bank) bank_set_map(BANK_SRAM, bank)
#define rom0_set_map(bank) bank_set_map(BANK_ROM0, bank)
#define rom1_set_map(bank) bank_set_map(BANK_ROM1, bank)

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

void bank_set_map(int bank, int bank_num);
int bank_get_map(int bank);
unsigned char bank_read_byte(int bank, unsigned int off);
void bank_write_byte(int bank, unsigned int off, unsigned int data);
unsigned int bank_read_word(int bank, unsigned int off);
void bank_write_word(int bank, unsigned int off, unsigned int data);
void bank_read_block(int bank, unsigned int off,
		     void * buffer, unsigned int size);
void bank_write_block(int bank, unsigned int off,
		      void * buffer, unsigned int size);
void bank_fill_block(int bank, unsigned int off,
		     unsigned int size, unsigned int data);
void bank_erase_flash(int bank);

#endif
