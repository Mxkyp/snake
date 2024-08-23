#include "canvas.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>
#define MIN_SIZE 8
#define TOP 0
#define BOT 1


void print_fruit(WINDOW * win, struct point *p){
  if(win == NULL){
   win = stdscr;
  }
  mvwaddch(win, p->y, p->x, '*' | A_BOLD);
}
/*
 * spawns fruit randomly within the canvas
 * if the fruit is spawned waits,
*/
struct point spawn_fruit(WINDOW * win, struct point *fruit_p, int side_length){
  static const char empty_cell = ' ';

  srand(time(NULL));
  fruit_p->y =  rand() % side_length,
  fruit_p->x =  rand() % side_length;

  print_fruit(win, fruit_p);

  return *fruit_p;
}
