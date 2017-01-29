#ifndef sxmp_h_INCLUDED
#define sxmp_h_INCLUDED

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define BUF_SIZE 4096

struct
{
  char str_filetype[255];
  char str_title[255];
  char str_position[255];
  char str_author[255];

  char filename[255];

  uint32_t  duration;
  uint32_t  position;
} playerdata;

extern int main(int, char**);

#endif // sxmp_h_INCLUDED

