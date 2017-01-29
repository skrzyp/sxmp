#include <xmp.h>
#include <string.h>

xmp_context context;
struct xmp_frame_info frame_info;
struct xmp_module_info module_info;

void  module_init() { context = xmp_create_context(); }

int   module_status() { return xmp_get_player(context, XMP_PLAYER_STATE); }

void  module_load(char* path)
{
  xmp_load_module(context, path);
  xmp_get_module_info(context, &module_info);
  xmp_set_player(context, XMP_PLAYER_DEFPAN, 25);
}

void  module_play(){ xmp_start_player(context, 44100, 0); }

int   module_fill_buffer(void* buffer, int size)
{
  return xmp_play_buffer(context, buffer, size, 1);
}

int   module_get_time()
{
  return frame_info.time;
}

int   module_is_played()
{
  return frame_info.total_time - frame_info.time;
}

char* module_get_title(){ return module_info.mod->name; }
char* module_get_type(){ return module_info.mod->type; }

void  module_deinit()
{
  xmp_end_player(context);
  xmp_release_module(context);
  xmp_free_context(context);
}
