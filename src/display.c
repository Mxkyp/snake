#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "../display.h"
#include "../main.h"
#define SQUARE_START_Y(side_length) (LINES-side_length)/2
#define SQUARE_START_X(side_length) (COLS-side_length)/2

bool create_windows(int side_length, WINDOW** content, WINDOW** background, struct point *background_upper_left_corner){
  *background_upper_left_corner = set_yx(SQUARE_START_Y(side_length), SQUARE_START_X(side_length));
  curs_set(0);

  refresh();

  *background = create_background(side_length, background_upper_left_corner);
  *content    = create_content(side_length, background_upper_left_corner);

  refresh();

  if(background == NULL || content == NULL){
    return false;
  }
  return true;
}

WINDOW *create_background(int side_length, struct point *background_upper_left_corner){
  WINDOW *border_win;
  border_win = newwin(side_length+2, side_length+2, background_upper_left_corner->y, background_upper_left_corner->x);
  start_color();
  init_pair(BACKGROUND_BORDER_COLOR, COLOR_MAGENTA, COLOR_MAGENTA);

  wbkgdset(border_win,COLOR_PAIR(BACKGROUND_BORDER_COLOR));
  box(border_win,0,0);

  wrefresh(border_win);
  return border_win;
}

WINDOW *create_content(int side_length, struct point *background_upper_left_corner){
  WINDOW *content_win;
  struct point content_upper_left_corner = set_yx(background_upper_left_corner->y + 1 , background_upper_left_corner->x + 1);

  content_win = newwin(side_length, side_length, content_upper_left_corner.y , content_upper_left_corner.x);
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

