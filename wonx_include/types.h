#ifndef _WONX_SYS_TYPES_H_
#define _WONX_SYS_TYPES_H_

#include "system_configure.h"

#include <stdlib.h> /* for NULL definition */

#ifndef _WONX_
#define _WONX_
#endif

#ifdef TYPEDEF_USHORT
typedef unsigned short int ushort;
#endif
#ifdef TYPEDEF_ULONG
typedef unsigned long  int ulong;
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef int            BOOL;

#ifndef far
#define far  /* None */
#endif

#ifndef near
#define near /* None */
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef struct {
  BYTE year;
  BYTE month;
  BYTE date;
  BYTE day_of_week;
  BYTE hour;
  BYTE minute;
  BYTE second;
} datetime_t;

#endif
