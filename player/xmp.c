#include <xmp.h>

xmp_context context;
struct xmp_frame_info frame_info;
struct xmp_module_info module_info;

void init_module(){
  context = xmp_create_context();
}

int status_module(){
  return xmp_get_player(context, XMP_PLAYER_STATE);
}

void load_module(char* path){
  xmp_load_module(context, path);
  xmp_get_module_info(context, &module_info);
}

void play_module(){
  xmp_start_player(context, 44100, 0);
}

int play_module_frame(){
  return xmp_play_frame(context);
}

int get_module_frame(){
  xmp_get_frame_info(context, &frame_info);
  return frame_info.loop_count;
}

char* get_module_name(){
  return module_info.mod->name;
}

void deinit_module(){
  xmp_end_player(context);
  xmp_release_module(context);
  xmp_free_context(context);
}
