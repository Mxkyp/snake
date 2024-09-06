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
#define SIDE_LENGTH 30

int main(void){
  initscr();

  //background and content display
  WINDOW *content = NULL, *background = NULL;
  int starty, startx;
  assert(create_windows(SIDE_LENGTH, &content, &background, &starty, &startx));
  refresh();

  //snake and fruit
  struct fruit *fr         = create_fruit();
  struct snake *snake_head = create_snake(SIDE_LENGTH);
  assert(fr);
  assert(snake_head);


  int direction;

  cbreak();
  noecho();


  while(true){
    render(content, fr, snake_head);
    input(&direction);
    if(move_snake(direction, SIDE_LENGTH, snake_head, fr) == false){ break; }

    wrefresh(content);
    wclear(content);
  }

  clear();
  endwin();
  return 0;
}

void render(WINDOW *content, struct fruit *fr, struct snake *head){
    manage_fruit(content, fr, head);
    print_fruit(content, &fr->coords);
    print_snake(content, head);
}

void input(int *direction){
    static int c;
    int last_direction = *direction;
    get_move(&c);

    switch(c){
      case 'w': *direction = UP;
        break;
      case 'd': *direction = RIGHT;
        break;
      case 's': *direction = DOWN;
        break;
      case 'a': *direction = LEFT;
        break;
    }
    if(last_direction == *direction + 1 || last_direction == *direction - 1){
      *direction = last_direction;
    }
}

void manage_fruit(WINDOW *content, struct fruit *fr, struct snake *s){
    if(check_fruit(fr)){
      mvwdelch(content, fr->coords.y, fr->coords.x);
      spawn_fruit(content, fr, s, SIDE_LENGTH);
      time(&fr->spawn_time);
      fr->is_spawned = true;
    }
}

void get_move(int *c){
    timeout(300);
    *c = getch();
    flushinp();
}


bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx){
  *starty = (LINES - side_length) / 2;
  *startx = (COLS  - side_length) / 2;
  curs_set(0);

  refresh();

  *background = create_background(side_length, starty, startx);
  *content    = create_canvas(side_length, starty, startx);

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

WINDOW *create_canvas(int side_length, int *start_y, int *start_x){
  WINDOW *content_win;

  content_win = newwin(side_length, side_length, *start_y+1 , *start_x+1);
  wrefresh(content_win);

  return content_win;
}
