#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../display.h"
#include "../main.h"

bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx){
  *starty = (LINES - side_length) / 2;
  *startx = (COLS  - side_length) / 2;
  curs_set(0);

  refresh();

  *background = create_background(side_length, starty, startx);
  *content    = create_content(side_length, starty, startx);

  refresh();

  if(background == NULL || content == NULL){
    return false;
  }
  return true;
}

WINDOW *create_background(int side_length, int *start_y, int *start_x){
  WINDOW *border_win;
  border_win = newwin( side_length+2, side_length+2, *start_y, *start_x);
  start_color();
  init_pair(BACKGROUND_BORDER_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);

  wbkgdset(border_win,COLOR_PAIR(BACKGROUND_BORDER_COLOR));
  box(border_win,0,0);

  wrefresh(border_win);
  return border_win;
}

WINDOW *create_content(int side_length, int *start_y, int *start_x){
  WINDOW *content_win;

  content_win = newwin(side_length, side_length, *start_y+1 , *start_x+1);
  wrefresh(content_win);

  return content_win;
}

void end_screen(WINDOW *main, int score, int side_length){
  touchwin(main);

  WINDOW *end_screen;
  const int end_screen_width =  13,
            end_screen_height = 8;
  end_screen = derwin(main, end_screen_height, end_screen_width,(side_length - end_screen_height)/2,(side_length - end_screen_width)/2);
  assert(end_screen);

  wclear(end_screen);
  start_color();

  init_pair(SNAKE_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);

  wbkgd(end_screen, COLOR_PAIR(SNAKE_COLOR) | A_DIM);
  box(end_screen,0,0);


  wattron(end_screen, COLOR_PAIR(5) | A_BOLD | A_BLINK);
  mvwprintw(end_screen, (end_screen_height-1)/2,(end_screen_width - (int)strlen("GAME OVER"))/2 , "GAME OVER");
  wattroff(end_screen, COLOR_PAIR(5) | A_BOLD | A_BLINK);

  attron(COLOR_PAIR(SNAKE_COLOR));
  mvwprintw(end_screen, (end_screen_height-1)/2 + 1,(end_screen_width - (int)strlen("GAME OVER"))/2 , "SCORE:%d ",score);
  attroff(COLOR_PAIR(SNAKE_COLOR));

  doupdate();
  wrefresh(end_screen);
  refresh();

  sleep(10);
}

