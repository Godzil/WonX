#ifndef _WONX_SYS_SERVICE_H_
#define _WONX_SYS_SERVICE_H_

#include "types.h"

#define MK_WORD(high,low)  (((unsigned short int)(high) <<  8) | ((unsigned short int)(low)))
#define MK_DWORD(high,low) (((unsigned long  int)(high) << 16) | ((unsigned long  int)(low)))
#define MK_FP(seg,off) ((void *)MK_DWORD(seg,off))
#define FP_OFF(p) ((unsigned short int)((unsigned long int)(p) & 0xffff))
#define FP_SEG(p) ((unsigned short int)((unsigned long int)(p) >> 16))

void bios_exit();

#endif
