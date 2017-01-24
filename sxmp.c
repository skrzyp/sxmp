#include <stdio.h>
#include "xmp_wrapper.c"
#include "audio.c"

#define SXMP_VERSION "0.0.2"

void version(void){
  const char* sxmp_version = SXMP_VERSION;
  printf("libxmp version:\t%s\n", xmp_version);
  printf("sxmp version:\t%s\n", sxmp_version);
}

int main(int argc, char **argv) {
  version();
  if (argv[1] == 0) {
    printf("usage, %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  audio_init();
  init_module();
  load_module(argv[1]);

  printf("starting playback: %s\n", argv[1]);
  play_module();
  while (play_module_frame() == 0) {
    if (get_module_frame() > 0)
      break;
    audio_playframe(frame_info.buffer, frame_info.buffer_size);
  }

  deinit_module();
  audio_deinit();
  return 0;
}
