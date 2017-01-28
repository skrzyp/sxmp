#include <stdio.h>
#include <string.h>
#include <time.h>

#include "sxmp.h"
#include "player/xmp.h"
#include "audio/libao.h"
#include "ui/ncurses.h"

void version(void){
  printf("libxmp version:\t%s\n", xmp_version);
  printf("sxmp version:\t%s\n", sxmp_version);
}

int main(int argc, char **argv) {
  version();

  if (argc <= 1) {
    printf("usage, %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }


  ui_init();

  strcpy(filename, argv[1]);

  audio_init();
  init_module();
  load_module(filename);

  sprintf(playback,"title:\t%s", module_info.mod->name);
  sprintf(filetype,"type:\t%s", module_info.mod->type);

  play_module();
  while (play_module_frame() == 0) {
    playback_time = frame_info.time;
    sprintf(duration,"time:\t%02d:%02d.%03d",playback_time/1000/60,(playback_time/1000)%60,playback_time%1000);
    if (get_module_frame() > 0)
      break;
    audio_playframe(frame_info.buffer, frame_info.buffer_size);
    ui_update();
  }

  deinit_module();
  audio_deinit();
  ui_deinit();
  return 0;
}
