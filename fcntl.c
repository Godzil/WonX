/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_configure.h"

#include "wonx/fcntl.h"

#include "WonX.h"

/*****************************************************************************/
/* 互換関数の定義                                                            */
/*****************************************************************************/

/*
 * void * でデータを渡す関数は，型を間違えるバグが入る可能性があるので，
 * void * を適切な型に置き換えてある．
 */

/*
 * Xサーバとの同期の整合性がとれなくなるなどの問題が考えられるので，
 * 互換関数の内部は UNIXTimer_Pause(), UNIXTimer_Unpause() でくくり，
 * タイマ割り込みを一時停止して処理を行う．また，unpause するまえに，
 * かならず sync するようにする．
 */

/*
 * タイマの一時停止の２重解除の問題が出てくるので，
 * 互換関数から互換関数を呼んではいけない．
 * (一時停止はネストされるが，いちおう)
 * 似たような処理をする関数の場合は，必ず static な別関数に処理をまとめ，
 * そっちを呼び出すようにすること．
 * 引数の表示の問題もあるしね．
 */

/*
 * mmap() が UNIX 標準のものと WonderWitch のものでコンフリクトしてしまうことの
 * 対策．具体的な内容や理由は README を参照してください．
 */
#if 0
void * wonx_mmap(char * filename);
void * mmap = wonx_mmap;
#endif
#if 0
#ifdef wonx_mmap
#undef wonx_mmap
#endif
#endif

void * wonx_mmap(char * filename)
{
  int size = 10;
  FILE * fp;
  int i, c;
  char * p;
  void * ret;

  if (!WonX_IsCreated()) WonX_Create();

  /* タイマを一時停止する */
  UNIXTimer_Pause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  printf("call : mmap() : filename = %s\n", filename);
  fflush(stdout);

  p = (char *)malloc(size);
  if (p == NULL) WonX_Error("mmap", "cannot allocate memory.");

  fp = fopen(filename, "rb");
  if (fp == NULL) WonX_Error("mmap", "cannot open file.");

  i = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (i > size - 1) {
      p = (char *)realloc(p, size);
      if (p == NULL) WonX_Error("mmap", "cannot reallocate memory.");
    }
    p[i] = c;
    i++;
  }

  fclose(fp);
  ret = p;

  WonXDisplay_Sync(WonX_GetWonXDisplay());

  printf("call : mmap() : return value = 0x%p\n", ret);
  fflush(stdout);

  /* タイマをもとに戻す */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* ここまで                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
