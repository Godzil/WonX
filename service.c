/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>

#include "wonx/service.h"

#include "WonX.h"

/*****************************************************************************/
/* ダミー関数の定義                                                          */
/*****************************************************************************/

int _asm_inline(char * code) { return (0); }
int _asm_int(char * code, int ax) { return (0); }
int _asm_intb(char * code, int ax, unsigned char bl) { return (0); }
int _asm_intbb(char * code, int ax, unsigned char bl, unsigned char cl) { return (0); }
int _asm_intw(char * code, int ax, int bx) { return (0); }
int _asm_intww(char * code, int ax, int bx, int cx) { return (0); }
int _asm_intwww(char * code, int ax, int bx, int cx, int dx) { return (0); }
int _asm_intwwww(char * code, int ax, int bx, int cx, int dx, int si) { return (0); }
int _asm_intwp(char * code, int ax, int bx, int (*dummy)(void), void * dx) { return (0); }
int _asm_intwwp(char * code, int ax, int bx, int cx, void * dx) { return (0); }
int _asm_intwwwp(char * code, int ax, int bx, int cx, int dx, void * si) { return (0); }
int _asm_intwfp(char * code, int ax, int bx, void * dsdx) { return (0); }
int _asm_intfp(char * code, int ax, void * bxdx) { return (0); }

long int _asm_intl(char * code, int ax) { return (0); }
long int _asm_intlw(char * code, int ax, int bx) { return (0); }
long int _asm_intlww(char * code, int ax, int bx, int cx) { return (0); }
long int _asm_intlwww(char * code, int ax, int bx, int cx, int dx) { return (0); }
long int _asm_intlwwww(char * code, int ax, int bx, int cx, int dx, int si) { return (0); }
long int _asm_intlwp(char * code, int ax, int bx, int (*dummy)(void), void * dx) { return (0); }
long int _asm_intlwwp(char * code, int ax, int bx, int cx, void * dx) { return (0); }
long int _asm_intlwwwp(char * code, int ax, int bx, int cx, int dx, void * si) { return (0); }
long int _asm_intlwfp(char * code, int ax, int bx, void * dsdx) { return (0); }

void bios_exit()
{
  printf("call : bios_exit() : \n");
  fflush(stdout);
  if (WonX_IsCreated()) WonX_Destroy();
  exit (0);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
