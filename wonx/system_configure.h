/* configure.h for configuration of wonx */

#ifndef _WONX_system_configure_h_INCLUDED_
#define _WONX_system_configure_h_INCLUDED_

/*
 * 以下を有効にすると，ushort, ulong が typedef される．
 */

#if 0 /* ushort は，普通は標準で /usr/include/sys/types.h で定義されている */
#define TYPEDEF_USHORT
#endif
#if 1
#define TYPEDEF_ULONG
#endif

#endif /* _WONX_system_configure_h_INCLUDED_ */

/* End of system_configure.h */
