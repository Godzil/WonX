#ifndef _WONX_SYS_FCNTL_H_
#define _WONX_SYS_FCNTL_H_

#include "filesys.h"

/*
 * fcntl.h �� /usr/include/fcntl.h ���ɤ߹���Ф褤�Τǡ�
 * �����Ϥ��Υե�����Ǥϡ�
 * #include <fcntl.h>
 * ��������ˤ������Τ������������ -Iwonx �Τ褦�ˤ��ƥ���ѥ���
 * ���Ƥ�����ˡ���ʬ���Ȥ��ɤ߹���Ǥ��ޤ���ǽ��������Τǡ�
 * #include </usr/include/fcntl.h>
 * �Ȥ��ơ���ʬ���Ȥ��ɤ߹��ޤʤ��褦�ˡ�/usr/include ���������Ƥ��롥
 */

/*
 * NetBSD �� FreeBSD �Ǥϡ�/usr/include/fcntl.h ��
 * /usr/include/sys/fcntl.h �Ϥޤä���Ʊ���Ǥ��롥
 *
 * Solaris �Ǥϡ�/usr/include/fcntl.h �� /usr/include/sys/fcntl.h ��
 * ���󥯥롼�ɤ��Ƥ��롥
 *
 * Linux �Ǥϡ�/usr/include/fcntl.h �����ΤˤʤäƤ��ơ�
 * /usr/include/sys/fcntl.h �� /usr/include/fcntl.h �򥤥󥯥롼�ɤ��������
 * �ե�����ˤʤäƤ��롥
 */

/* ���ξ���Ȥ� include ���Ƥ��� */
#include </usr/include/fcntl.h>
#include </usr/include/sys/fcntl.h>

/*
 * mmap() �� UNIX ɸ��Τ�Τ� WonderWitch �Τ�Τǥ���եꥯ�Ȥ��Ƥ��ޤ����Ȥ�
 * �к�������Ū�����Ƥ���ͳ�� README �򻲾Ȥ��Ƥ���������
 */
#include </usr/include/stdio.h>
/* void * mmap(char * filename); */
void * wonx_mmap(char * filename);
/* #define wonx_mmap mmap */
#define mmap wonx_mmap

#endif
