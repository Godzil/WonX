#ifndef _WONX_SYS_SOUND_H_
#define _WONX_SYS_SOUND_H_

#include "service.h"

/*****************************************************************************/
/* 互換関数の宣言                                                            */
/*****************************************************************************/

void sound_init(void);
void sound_set_channel(unsigned int flags);
unsigned int sound_get_channel(void);
void sound_set_output(unsigned int flags);
unsigned int sound_get_output(void);
void sound_set_wave(int channel, unsigned char * wave);
void sound_set_pitch(int channel, unsigned int frequency);
unsigned int sound_get_pitch(int channel);
void sound_set_volume(int channel, unsigned int volume);
unsigned int sound_get_volume(int channel);
void sound_set_sweep(int sweep, int step);
unsigned int sound_get_sweep(void);
void sound_set_noise(unsigned int flags);
unsigned int sound_get_noise(void);
unsigned int sound_get_random(void);

#endif
