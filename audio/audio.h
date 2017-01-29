#ifndef audio_h_INCLUDED
#define audio_h_INCLUDED
#include <ao/ao.h>

#define BUF_SIZE 4096

ao_device *device;

extern void audio_init();
extern void audio_play();
extern void audio_play_buffer();
extern void audio_deinit();

#endif 

