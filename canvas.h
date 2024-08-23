#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdbool.h>
#include <curses.h>

struct point{
  int x,y;
};

/*
 * creates a random coordinate fruit_p within the side_length square,
 * then call print_fruit(win, fruit_p)
*/
struct point spawn_fruit(WINDOW * win, struct point *fruit_p, int side_length);

/*
 * prints the fruits at the point *p
*/
void print_fruit(WINDOW * win, struct point *p);
#endif
