#include "../main.h"
#include "../game_elements.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <assert.h>


struct fruit *create_fruit(void){
  struct fruit *new = malloc(sizeof(*new));
  assert(new);

  new->coords.x = 0;
  new->coords.y = 0;
  new->is_spawned = false;
  new->lifetime = FRUIT_LIFETIME_SECONDS;

  return new;
}

bool check_fruit(struct fruit *fr){
return ( fr->is_spawned == false ||
        (time(NULL)-fr->spawn_time) >  fr->lifetime);
}

void print_fruit(WINDOW *win, struct point *p){
  if(win == NULL){
   win = stdscr;
  }
  start_color();
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  mvwaddch(win, p->y, p->x, '*' | A_BOLD | COLOR_PAIR(3));
}

void spawn_fruit(WINDOW * win,  struct GameElements *game_elements, int side_length){

  do{
  srand(time(NULL));
  game_elements->fruit->coords.y =  rand() % side_length,
  game_elements->fruit->coords.x =  rand() % side_length;
  }while(on_snake(&game_elements->fruit->coords, game_elements->snake_head));

  print_fruit(win, &game_elements->fruit->coords);
}

