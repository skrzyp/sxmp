#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>
#include <string.h>
#include <ao/ao.h>
#define BUF_SIZE 4096

void version(void){
  printf("libxmp version: %s\n", xmp_version);
}

int main(int argc, char **argv) {
  version();
  if (argv[1] == 0) {
    printf("usage, %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  ao_device *device;
  ao_sample_format format;
  int default_driver;
  char *buffer;
  int buf_size;
  int sample;
  float freq = 440.0;
  int i;
  ao_initialize();

  default_driver = ao_default_driver_id();

  memset(&format, 0, sizeof(format));
  format.bits = 16;
  format.channels = 2;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  device = ao_open_live(default_driver, &format, NULL );

  xmp_context context = xmp_create_context();
  struct xmp_frame_info frame_info;

  if (xmp_load_module(context, argv[1]) != 0){
    fprintf(stderr, "can't find %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (xmp_test_module(argv[1], NULL) != 0) {
    fprintf(stderr, "%s is not a valid module\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  xmp_start_player(context, 44100, 0);

  while (xmp_play_frame(context) == 0) {
    xmp_get_frame_info(context, &frame_info);
    if (frame_info.loop_count > 0)
      break;
    ao_play(device, frame_info.buffer, frame_info.buffer_size);
  }

  xmp_end_player(context);
  xmp_release_module(context);
  xmp_free_context(context);
  ao_close(device);
  ao_shutdown();

  return 0;
}
