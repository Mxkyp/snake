#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#include "../main.h"
#include "../canvas.h"
#include "../worm.h"
#define SIDE_LENGTH 20
/* add moving the snake */

int main(void){
  initscr();

  WINDOW *content = NULL, *background = NULL;
  int starty, startx;
  assert(create_windows(SIDE_LENGTH, &content, &background, &starty, &startx));
  refresh();

  struct point fruit_position = {.y = 0, .x = 0};
  clock_t fruit_spawn;
  bool spawned = false;
  static const clock_t fruit_lifetime = 5 * CLOCKS_PER_SEC;

  struct snake* snak = create_snake(SIDE_LENGTH);
  int direction = LEFT;
  assert(snak);


  while(true){
    if(fruit_passed(spawned, fruit_spawn, fruit_lifetime)){
      mvwdelch(content, fruit_position.y, fruit_position.x);
      spawn_fruit(content, &fruit_position, SIDE_LENGTH);
      fruit_spawn = clock();
      spawned = true;
    }


    print_snake(content, snak);
    if(!move_snake(snak, SIDE_LENGTH, NULL, direction)){
      wrefresh(content);
      break;
    }
    wrefresh(content);
  }
  clear();

  endwin();
  return 0;
}

bool fruit_passed(bool spawned, clock_t fruit_spawn, clock_t fruit_lifetime){
return ( spawned == false ||
        (double)(clock()-fruit_spawn)/CLOCKS_PER_SEC > (double) fruit_lifetime/CLOCKS_PER_SEC );
}

bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx){
  *starty = (LINES - side_length) / 2;
  *startx = (COLS  - side_length) / 2;
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
