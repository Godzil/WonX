/*****************************************************************************/
/* ��������                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "wonx_include/sound.h"

#include "WonX.h"

/*****************************************************************************/
/* �ߴ��ؿ������                                                            */
/*****************************************************************************/

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

void sound_init(void)
{
  return;
}

void sound_set_channel(unsigned int flags)
{
  return;
}

unsigned int sound_get_channel(void)
{
  return (0);
}

void sound_set_output(unsigned int flags)
{
  return;
}

unsigned int sound_get_output(void)
{
  return (0);
}

void sound_set_wave(int channel, unsigned char * wave)
{
  return;
}

void sound_set_pitch(int channel, unsigned int frequency)
{
  return;
}

unsigned int sound_get_pitch(int channel)
{
  return (0);
}

void sound_set_volume(int channel, unsigned int volume)
{
  return;
}

unsigned int sound_get_volume(int channel)
{
  return (0);
}

void sound_set_sweep(int sweep, int step)
{
  return;
}

unsigned int sound_get_sweep(void)
{
  return (0);
}

void sound_set_noise(unsigned int flags)
{
  return;
}

unsigned int sound_get_noise(void)
{
  return (0);
}

unsigned int sound_get_random(void)
{
  return (0);
}

/*****************************************************************************/
/* �����ޤ�                                                                  */
/*****************************************************************************/

/*****************************************************************************/
/* End of File.                                                              */
/*****************************************************************************/
