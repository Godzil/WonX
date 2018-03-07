/* configure.h for configuration of wonx */

#ifndef _WONX_winx_configure_h_INCLUDED_
#define _WONX_wonx_configure_h_INCLUDED_

/* WonX �ǤΥ����޳����ߤμ���(ñ�̤ϥߥ���) */
#define WONX_TIMER_INTERVAL 100 /* 0.1 �� */

/* HBLANK, VBLANK �����ߤΥǥե���ȤΥ��󥿡��Х�(0.1��ñ��) */
#define WONX_HBLANK_INTERVAL ( 3 * 10) /*  3 ���� */
#define WONX_VBLANK_INTERVAL (20 * 10) /* 20 ���� */

/*
 * ���ꥢ���̿����Υ����ॢ���Ȼ��֤�ñ��
 * (ñ�̤ϥߥ��ä���������ʤ����٤�̵��)
 */
#define WONX_SERIAL_PORT_TIMETICKS 100 /* 1/10 ��ñ�� */

#endif /* _WONX_wonx_configure_h_INCLUDED_ */

/* End of wonx_configure.h */
