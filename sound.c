/*****************************************************************************/
/* ここから                                                                  */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/sound.h>

#include "wonx.h"

/*****************************************************************************/
/* メンバ関数の定義                                                          */
/*****************************************************************************/

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
