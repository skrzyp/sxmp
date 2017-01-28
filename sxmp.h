#ifndef sxmp_h_INCLUDED
#define sxmp_h_INCLUDED

#include <stdio.h>
#include <string.h>
#include <time.h>

#define SXMP_VERSION "0.0.3"

char filename[255];
char filetype[255];
char playback[255];
char duration[255];
static int  playback_time;
static const char* sxmp_version = SXMP_VERSION;

extern void version();
extern int main(int, char**);

#endif // sxmp_h_INCLUDED

