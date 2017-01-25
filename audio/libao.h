#ifndef audio_h_INCLUDED
#define audio_h_INCLUDED
#include <ao/ao.h>

extern ao_device *device;

extern void audio_init();
extern void audio_play();
extern void audio_playframe();
extern void audio_deinit();

#endif 

