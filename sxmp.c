#include "sxmp.h"
#include "player/player.h"
#include "audio/audio.h"
#include "ui/ui.h"
#include <dlfcn.h>
int  buffer_size = BUF_SIZE;
char buffer[BUF_SIZE];

int main(int argc, char **argv)
{

  if (argc <= 1) {
    printf("usage, %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }


  ui_init();

  strcpy(playerdata.filename, argv[1]);

  audio_init();
  module_init();
  module_load(playerdata.filename);

  sprintf(playerdata.str_title,"title:\t%s", module_get_title());
  sprintf(playerdata.str_filetype,"type:\t%s", module_get_type());

  module_play();
  ui_draw(0);
  while (module_is_played() > 0) {
    playerdata.position = module_get_time();
    sprintf(playerdata.str_position,
            "time:\t%02d:%02d.%03d",
            playerdata.position/1000/60,
            (playerdata.position/1000)%60,
            playerdata.position%1000);
    module_fill_buffer(&buffer, buffer_size);
    audio_play_buffer(&buffer, buffer_size);
    ui_update();
  }

  module_deinit();
  audio_deinit();
  ui_deinit();
  return 0;
}
