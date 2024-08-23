#include "main.h"
#include "canvas.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#define SIDE_LENGTH 20

int main(void){
  WINDOW *content = NULL, *background = NULL;
  int starty, startx;
  struct point fruit_position, prev_fruit_pos = {.y = 0, .x = 0};


  initscr();

  assert(create_windows(SIDE_LENGTH, &content, &background, &starty, &startx));
  refresh();

  while(true){
    mvwdelch(content, prev_fruit_pos.y, prev_fruit_pos.x);
    prev_fruit_pos = spawn_fruit(content, &fruit_position, SIDE_LENGTH);
    wrefresh(content);
  }

  endwin();
  return 0;
}

bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx){
	*starty = (LINES - side_length) / 2;	/* Calculating for a center placement */
	*startx = (COLS  - side_length) / 2;	/* of the window		*/
  curs_set(0);

  refresh();

  *background = create_background(side_length, starty, startx);
  *content = wcreate_canvas(side_length, starty, startx);

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
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  wbkgd(border_win,COLOR_PAIR(1));
  wborder(border_win,'@','@','@','@','@','@','@','@');

  wrefresh(border_win);
  return border_win;
}

WINDOW *wcreate_canvas(int side_length, int *start_y, int *start_x){
  WINDOW *content_win;

  content_win = newwin(side_length, side_length, *start_y+1 , *start_x+1);
  wrefresh(content_win);

  return content_win;
}
