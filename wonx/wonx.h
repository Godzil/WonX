#ifndef _WONX_SYS_WONX_H_
#define _WONX_SYS_WONX_H_

#include "service.h"

/*****************************************************************************/
/* �����˸������� WonX �Υ����ӥ��ؿ�                                        */
/*****************************************************************************/

/* ���顼�ޥå׾���ν��� */
void wonx_print_colormap_data(void);

/* �ѥ�åȾ���ν��� */
void wonx_print_palette_data(int n);

/* ���٤ƤΥѥ�åȾ������� */
void wonx_print_all_palette_data(void);

/* ����饯������ν��� */
void wonx_print_character_data(int n);

/* ���٤ƤΥ���饯���������� */
void wonx_print_all_character_data(void);

/* ���ץ饤�Ⱦ���ν��� */
void wonx_print_sprite_data(int n);

/* ���٤ƤΥ��ץ饤�Ⱦ������� */
void wonx_print_all_sprite_data(void);

/* ���ߤ�ɽ��/��ɽ���Υ�٥�μ�����(1�ʾ��ɽ����0�ʲ�����ɽ��) */
int wonx_get_lcddraw_level(void);

/* ���ߤ�ɽ��/��ɽ���Υ�٥������ */
int wonx_set_lcddraw_level(int level);

/* ɽ����٥�򲼤��� */
int wonx_lcddraw_level_down(void);

/* ɽ����٥��夲�� */
int wonx_lcddraw_level_up(void);

#endif
