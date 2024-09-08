#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#include "../main.h"
#include "../fruit.h"
#include "../snake.h"
#include "../display.h"
#define SIDE_LENGTH 25

int main(void){
  initscr();

  //background and content display
  WINDOW *content = NULL, *background = NULL;
  int starty, startx;
  assert(create_windows(SIDE_LENGTH, &content, &background, &starty, &startx));
  cbreak();
  noecho();

  //snake and fruit
  struct fruit *fr         = create_fruit();
  struct snake *snake_head = create_snake(SIDE_LENGTH);
  assert(fr);
  assert(snake_head);


  while(true){
    render(content, fr, snake_head, starty, startx);
    input(&snake_head->move_direction);
    if(move_snake(SIDE_LENGTH, snake_head, fr) == false){ end_screen(content, snake_head->game_score, SIDE_LENGTH); break; }
    wclear(content);
  }

  clear();
  endwin();
  return 0;
}

void render(WINDOW *content, struct fruit *fr, struct snake *head, int starty, int startx){
    manage_fruit(content, fr, head);
    print_fruit(content, &fr->coords);
    print_snake(content, head);
    print_score(head->game_score, starty, startx);
    wrefresh(content);
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
    if(last_direction == *direction + 1 || last_direction == *direction - 1){ // prevent the snake from doing 180 degree turns
                                                                              // this works because directions are enum's
                                                                              // UP = 0 DOWN = 1, LEFT = 3 RIGHT = 4
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

void print_score(int game_score, int starty, int startx){
  mvprintw(starty-1, startx + 1, "score:%d", game_score);
}


