#ifndef _WONX_SYS_FCNTL_H_
#define _WONX_SYS_FCNTL_H_

#include "filesys.h"

/*
 * fcntl.h は /usr/include/fcntl.h を読み込めばよいので，
 * 本当はこのファイルでは，
 * #include <fcntl.h>
 * するだけにしたいのだが，これだと -Iwonx のようにしてコンパイル
 * している場合に，自分自身を読み込んでしまう可能性があるので，
 * #include </usr/include/fcntl.h>
 * として，自分自身を読み込まないように，/usr/include を明示している．
 */

/*
 * NetBSD と FreeBSD では，/usr/include/fcntl.h と
 * /usr/include/sys/fcntl.h はまったく同じである．
 *
 * Solaris では，/usr/include/fcntl.h が /usr/include/sys/fcntl.h を
 * インクルードしている．
 *
 * Linux では，/usr/include/fcntl.h が本体になっていて，
 * /usr/include/sys/fcntl.h は /usr/include/fcntl.h をインクルードするだけの
 * ファイルになっている．
 */

/* 一応両方とも include しておく */
#include </usr/include/fcntl.h>
#include </usr/include/sys/fcntl.h>

/*
 * mmap() が UNIX 標準のものと WonderWitch のものでコンフリクトしてしまうことの
 * 対策．具体的な内容や理由は README を参照してください．
 */
#include </usr/include/stdio.h>
/* void * mmap(char * filename); */
void * wonx_mmap(char * filename);
/* #define wonx_mmap mmap */
#define mmap wonx_mmap

#endif
