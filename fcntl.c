/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_configure.h"

#include "wonx/fcntl.h"

#include "WonX.h"

/*****************************************************************************/
/* �ߴ��ؿ������                                                            */
/*****************************************************************************/

/*
 * void * �ǥǡ������Ϥ��ؿ��ϡ�����ְ㤨��Х��������ǽ��������Τǡ�
 * void * ��Ŭ�ڤʷ����֤������Ƥ��롥
 */

/*
 * X�����ФȤ�Ʊ�������������Ȥ�ʤ��ʤ�ʤɤ����꤬�ͤ�����Τǡ�
 * �ߴ��ؿ��������� UNIXTimer_Pause(), UNIXTimer_Unpause() �Ǥ����ꡤ
 * �����޳����ߤ�����ߤ��ƽ�����Ԥ����ޤ���unpause ����ޤ��ˡ�
 * ���ʤ餺 sync ����褦�ˤ��롥
 */

/*
 * �����ޤΰ����ߤΣ��Ų�������꤬�ФƤ���Τǡ�
 * �ߴ��ؿ�����ߴ��ؿ���Ƥ�ǤϤ����ʤ���
 * (�����ߤϥͥ��Ȥ���뤬����������)
 * �����褦�ʽ����򤹤�ؿ��ξ��ϡ�ɬ�� static ���̴ؿ��˽�����ޤȤᡤ
 * ���ä���ƤӽФ��褦�ˤ��뤳�ȡ�
 * ������ɽ��������⤢�뤷�͡�
 */

/*
 * mmap() �� UNIX ɸ��Τ�Τ� WonderWitch �Τ�Τǥ���եꥯ�Ȥ��Ƥ��ޤ����Ȥ�
 * �к�������Ū�����Ƥ���ͳ�� README �򻲾Ȥ��Ƥ���������
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

  /* �����ޤ�����ߤ��� */
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

  /* �����ޤ��Ȥ��᤹ */
  UNIXTimer_Unpause(WonXSystem_GetUNIXTimer(WonX_GetWonXSystem()));

  return (ret);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
