#include "../sxmp.h"
#include <ncurses.h>
#include <sys/types.h>
#include <signal.h>

static int height, width;

void bar(int height, char* content, int colorpair)
{
  move(height,0);
  attron(COLOR_PAIR(colorpair));
  for(int i=0; i<width; i++) { mvaddch(height,i,' '); }
  mvprintw(height,1,content);
  attroff(COLOR_PAIR(colorpair));
}

void ui_draw()
{
  endwin();
  refresh();
  clear();
  getmaxyx(stdscr,height,width);
  mvaddstr((height/2)-1,1, playerdata.str_title);
  mvaddstr((height/2),1,   playerdata.str_filetype);
  mvaddstr((height/2)+1,1, playerdata.str_position);
  bar(height-2, playerdata.filename, 1);
  refresh();
}

void signal_handler()
{
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = ui_draw;
  sigaction(SIGWINCH, &sa, NULL);
}

void ui_init(){
  signal_handler();
  initscr();
  clear();
  noecho();
  start_color();
  cbreak();
  curs_set(0);
  nodelay(stdscr,TRUE);
  init_pair(1, COLOR_BLACK,COLOR_WHITE);
}

void ui_update(){
  mvaddstr((height/2)+1,1, playerdata.str_position);
  refresh();
}

void ui_deinit(){
  endwin();
}
