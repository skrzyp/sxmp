#include <ao/ao.h>
#define BUF_SIZE 4096
ao_device *device;

void audio_init(void){
  ao_sample_format format;
  int default_driver;
  ao_initialize();

  default_driver = ao_default_driver_id();

  format.bits = 16;
  format.channels = 2;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  device = ao_open_live(default_driver, &format, NULL );
}

void audio_playframe(void *buffer, int buffer_size) {
    ao_play(device, buffer, buffer_size);
}

void audio_deinit(void) {
    ao_close(device);
    ao_shutdown();
}
