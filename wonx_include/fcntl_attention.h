#ifndef _WONX_SYS_FCNTL_H_
#define _WONX_SYS_FCNTL_H_

/*
 * fcntl.h は /usr/include/fcntl.h を読み込めばよいので，
 * wonx_include/fcntl.h を作らないほうがよい．(wonx_include/fcntl.h を作ると，
 * 書き方によってはそっちが読み込まれてしまうかもしれないので)
 * もしも作るとすれば，このファイルのようなのを作るか？
 */

#include "filesys.h"

/* 自分自身を読み込まないように，/usr/include を明示する */
#include </usr/include/fcntl.h>

#endif
