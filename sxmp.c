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

  xmp_context context = xmp_create_context();
  struct xmp_frame_info frame_info;
  static const pa_sample_spec simple_spec = {
      .format = PA_SAMPLE_S16LE,
      .rate = 44100,
      .channels = 2
  };
  pa_simple *stream = NULL;
  stream = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL);

  if (xmp_load_module(xmpcon, "test.mod") != 0){
    fprintf(stderr, "can't find test.mod\n");
    exit(EXIT_FAILURE);
  }

  xmp_start_player(xmpcon, 44100, 0);

  while (xmp_play_frame(xmpcon) == 0) {
    xmp_get_frame_info(xmpcon, &frameinfo);
    if (frameinfo.loop_count > 0)
      break;
    pa_simple_write(stream, frameinfo.buffer, frameinfo.buffer_size);
  }

  pa_simple_drain(stream);
  xmp_end_player(xmpcon);
  xmp_release_module(xmpcon);
  xmp_free_context(xmpcon);

  return 0;
}
