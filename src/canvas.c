#include "../canvas.h"
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
  mvwaddch(win, p->y, p->x, '*' | A_BOLD);
}
/*
 * spawns fruit randomly within the canvas
*/
void spawn_fruit(WINDOW * win, struct fruit *fr, int side_length){

  srand(time(NULL));
  fr->coords.y =  rand() % side_length,
  fr->coords.x =  rand() % side_length;

  print_fruit(win, &fr->coords);
}
