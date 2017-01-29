#include <asap.h>
#include <stdio.h>
#include <string.h>

ASAP *asap;
const ASAPInfo *info;
FILE *module_file;
unsigned char module[ASAPInfo_MAX_MODULE_LENGTH];
int module_len;
int song;
int position;
int duration;
char title[255];
char type[255];
char author[255];

void  module_init() { asap = ASAP_New(); }

void  module_load(char* path)
{
  module_file = fopen(path, "rb");
  module_len  = fread(module, 1, sizeof(module), module_file);
  fclose(module_file);
  ASAP_Load(asap, path, module, module_len);
  info = ASAP_GetInfo(asap);
  song = ASAPInfo_GetDefaultSong(info);
  duration = ASAPInfo_GetDuration(info,song);
}

int module_get_duration()
{
  return duration;
}

void  module_play(){ ASAP_PlaySong(asap, song, -1); }

int   module_fill_buffer(void* buffer, int length)
{
  position = ASAP_GetPosition(asap);
  return ASAP_Generate((ASAP *) asap, buffer, length, ASAPSampleFormat_S16_L_E);
}

int   module_get_position() { return position; }

int   module_is_played()
{
  int played;
  if (duration == -1)
    played = 1;
  else
    played = duration - position;
  return played;
}

char* module_get_title()
{
  strcpy(title,ASAPInfo_GetTitle(info));
  return title;
}

char* module_get_author()
{
  strcpy(author, ASAPInfo_GetAuthor(info));
  return author;
}

char* module_get_type()
{
  strcpy(type,
         ASAPInfo_GetExtDescription(
           ASAPInfo_GetOriginalModuleExt(info,module,module_len)
         )
  );
  return type;
}

void  module_deinit()
{
}
