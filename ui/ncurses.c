#include "../sxmp.h"
#include <ncurses.h>

void ui_init(){
  initscr();
  clear();
  noecho();
  start_color();
  cbreak();
  nodelay(stdscr,TRUE);
  init_pair(1,COLOR_WHITE,COLOR_BLUE);
}

void ui_update(){
  static int height, width;
  getch();
  clear();
  getmaxyx(stdscr,height,width);
  mvaddstr((height/2)-1,1, playerdata.str_title);
  mvaddstr((height/2),1,   playerdata.str_filetype);
  mvaddstr((height/2)+1,1, playerdata.str_position);
  attron(COLOR_PAIR(1));
  move(0,0);
  for(int i=0; i<width; i++)
    { mvaddch(0,i,' '); }
  mvprintw(0,0,"simple extensible media player");
  mvprintw(0,width-sizeof(sxmp_version),sxmp_version);
  attroff(COLOR_PAIR(1));
  refresh();
}

void ui_deinit(){
  endwin();
}
