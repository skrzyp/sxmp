#include <stdio.h>
#include <stdlib.h>
#include <xmp.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024

void version(void){
  printf("libxmp version: %s\n", xmp_version);
}

int main(int argc, char **argv) {
  version();
  if (argv[1] == 0) {
    printf("usage, %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int error;
  xmp_context context = xmp_create_context();
  struct xmp_frame_info frame_info;
  static const pa_sample_spec simple_spec = {
      .format = PA_SAMPLE_S16LE,
      .rate = 44100,
      .channels = 2
  };
  pa_simple *stream = NULL;
  stream = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &simple_spec, NULL, NULL, &error);

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
    pa_simple_write(stream, frame_info.buffer, frame_info.buffer_size, &error);
  }

  pa_simple_drain(stream, &error);
  xmp_end_player(context);
  xmp_release_module(context);
  xmp_free_context(context);

  return 0;
}
