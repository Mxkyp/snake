#include "main.h"
#include "canvas.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#define SIDE_LENGTH 30

int main(void){
  struct square_map *canvas = create_canvas(SIDE_LENGTH);
  WINDOW *content = NULL, *background = NULL;
  int starty, startx;
  char* last_fruit = NULL;


  initscr();

  assert(create_windows(canvas, &content, &background, &starty, &startx));
  refresh();
  while(true){
    last_fruit = spawn_fruit(canvas, last_fruit, SIDE_LENGTH, false);
    wclear(content);
    print_canvas(content, canvas);
    wrefresh(content);
    sleep(1);
  }
  endwin();
  return 0;
}

bool create_windows(struct square_map *canvas, WINDOW** content, WINDOW** background, int *starty, int *startx){
	*starty = (LINES - canvas->side_length) / 2;	/* Calculating for a center placement */
	*startx = (COLS  - canvas->side_length) / 2;	/* of the window		*/
  curs_set(0);

  refresh();

  *background = create_background(canvas, starty, startx);
  *content = wcreate_canvas(canvas, starty, startx);

  refresh();

  if(background == NULL || content == NULL){
    return false;
  }
  return true;
}

WINDOW *create_background(struct square_map *canvas, int *start_y, int *start_x){
  WINDOW *border_win;
  border_win = newwin(canvas->side_length+2, canvas->side_length+2, *start_y, *start_x);
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);

  wbkgd(border_win,COLOR_PAIR(1));
  wborder(border_win,'@','@','@','@','@','@','@','@');

  wrefresh(border_win);
  return border_win;
}

WINDOW *wcreate_canvas(struct square_map *canvas, int *start_y, int *start_x){
  WINDOW *content_win;

  content_win = newwin(canvas->side_length, canvas->side_length, *start_y+1 , *start_x+1);
  wrefresh(content_win);

  return content_win;
}
