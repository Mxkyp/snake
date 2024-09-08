#include "../fruit.h"
#include "../snake.h"
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

void print_fruit(WINDOW * win, struct point *p){
  if(win == NULL){
   win = stdscr;
  }
  start_color();
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  mvwaddch(win, p->y, p->x, '*' | A_BOLD | COLOR_PAIR(3));
}

void spawn_fruit(WINDOW * win, struct fruit *fr, struct snake *s, int side_length){

  do{
  srand(time(NULL));
  fr->coords.y =  rand() % side_length,
  fr->coords.x =  rand() % side_length;
  }while(on_snake(&fr->coords, s));

  print_fruit(win, &fr->coords);
}

