#ifndef _WONX_SYS_SERVICE_H_
#define _WONX_SYS_SERVICE_H_

#include "types.h"

#define MK_WORD(high,low)  (((unsigned short int)(high) <<  8) | ((unsigned short int)(low)))
#define MK_DWORD(high,low) (((unsigned long  int)(high) << 16) | ((unsigned long  int)(low)))
#define MK_FP(seg,off) ((void *)MK_DWORD(seg,off))

#if 0
#define FP_OFF(p) ((unsigned short int)((unsigned long int)(p) & 0xffff))
#define FP_SEG(p) ((unsigned short int)((unsigned long int)(p) >> 16))
#else
#define FP_OFF(p) (p)
#define FP_SEG(p) (0)
#endif

int _asm_inline(char * code);
int _asm_int(char * code, int ax);
int _asm_intb(char * code, int ax, unsigned char bl);
int _asm_intbb(char * code, int ax, unsigned char bl, unsigned char cl);
int _asm_intw(char * code, int ax, int bx);
int _asm_intww(char * code, int ax, int bx, int cx);
int _asm_intwww(char * code, int ax, int bx, int cx, int dx);
int _asm_intwwww(char * code, int ax, int bx, int cx, int dx, int si);
int _asm_intwp(char * code, int ax, int bx, int (*dummy)(void), void * dx);
int _asm_intwwp(char * code, int ax, int bx, int cx, void * dx);
int _asm_intwwwp(char * code, int ax, int bx, int cx, int dx, void * si);
int _asm_intwfp(char * code, int ax, int bx, void * dsdx);
int _asm_intfp(char * code, int ax, void * bxdx);

long int _asm_intl(char * code, int ax);
long int _asm_intlw(char * code, int ax, int bx);
long int _asm_intlww(char * code, int ax, int bx, int cx);
long int _asm_intlwww(char * code, int ax, int bx, int cx, int dx);
long int _asm_intlwwww(char * code, int ax, int bx, int cx, int dx, int si);
long int _asm_intlwp(char * code, int ax, int bx, int (*dummy)(void), void * dx);
long int _asm_intlwwp(char * code, int ax, int bx, int cx, void * dx);
long int _asm_intlwwwp(char * code, int ax, int bx, int cx, int dx, void * si);
long int _asm_intlwfp(char * code, int ax, int bx, void * dsdx);

#define service(vec, ah)                          _asm_int(NULL,0)
#define serviceb(vec, ah, bl)                     _asm_intb(NULL,0,0)
#define servicebb(vec, ah, bl, cl)                _asm_intbb(NULL,0,0,0)
#define servicew(vec, ah, bx)                     _asm_intw(NULL,0,0)
#define serviceww(vec, ah, bx, cx)                _asm_intww(NULL,0,0,0)
#define servicewww(vec, ah, bx, cx, dx)           _asm_intwww(NULL,0,0,0,0)
#define servicew_w(vec, ah, bx, dx)               _asm_intwww(NULL,0,0,0,0)
#define servicewwww(vec, ah, bx, cx, dx, si)      _asm_intwwww(NULL,0,0,0,0,0)
#define servicewp(vec, ah, bx, dx)                _asm_intwp(NULL,0,0,0,0)
#define servicewwp(vec, ah, bx, cx, dx)           _asm_intwwp(NULL,0,0,0,0)
#define servicewwwp(vec, ah, bx, cx, dx, si)      _asm_intwwwp(NULL,0,0,0,0,0)
#define servicewfp(vec, ah, bx, dsdx)             _asm_intwfp(NULL,0,0,0)
#define servicewwfp(vec, ah, bx, cx, dsdx)        _asm_intwfp(NULL,0,0,0)
#define servicefp(vec, ah, bxdx)                  _asm_intwfp(NULL,0,0,0)

#define servicex(vec, ah, al)                     _asm_int(NULL,0)
#define servicexw(vec, ah, al, bx)                _asm_intw(NULL,0,0)
#define servicexww(vec, ah, al, bx, cx)           _asm_intww(NULL,0,0,0)
#define servicexwww(vec, ah, al, bx, cx, dx)      _asm_intwww(NULL,0,0,0,0)
#define servicexwwww(vec, ah, al, bx, cx, dx, si) _asm_intwwww(NULL,0,0,0,0,0)
#define servicexwp(vec, ah, al, bx, dx)           _asm_intwp(NULL,0,0,0,0)
#define servicexwwp(vec, ah, al, bx, cx, dx)      _asm_intwwp(NULL,0,0,0,0)
#define servicexwfp(vec, ah, al, bx, dsdx)        _asm_intwfp(NULL,0,0,0)

#define servicel(vec, ah)                         _asm_intl(NULL,0)
#define servicelw(vec, ah, bx)                    _asm_intlw(NULL,0,0)
#define servicelww(vec, ah, bx, cx)               _asm_intlww(NULL,0,0,0)
#define servicelwww(vec, ah, bx, cx, dx)          _asm_intlwww(NULL,0,0,0,0)
#define servicelwp(vec, ah, bx, dx)               _asm_intlwp(NULL,0,0,0,0)
#define servicelwfp(vec, ah, bx, dsdx)            _asm_intlwfp(NULL,0,0,0)

#define servicelx(vec, ah, al)                    _asm_intl(NULL ,0)
#define servicelxw(vec, ah, al, bx)               _asm_intlw(NULL,0,0)
#define servicelxww(vec, ah, al, bx, cx)          _asm_intlww(NULL,0,0,0)
#define servicelxwww(vec, ah, al, bx, cx, dx)     _asm_intlwww(NULL,0,0,0,0)
#define servicelxwp(vec, ah, al, bx, dx)          _asm_intlwp(NULL,0,0,0,0)
#define servicelxwfp(vec, ah, al, bx, dsdx)       _asm_intlwfp(NULL,0,0,0)

void bios_exit();

#endif
