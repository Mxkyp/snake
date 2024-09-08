#ifndef WORM_H_
#define WORM_H_
#include "fruit.h"
#include <stdlib.h>
#include <curses.h>
#define START_SIZE 3 //the starting length of the snake

struct snake{
  int move_direction;
  int game_score;
  struct point coords;
  struct snake *next;
  struct snake *before;
};

/*
 * creates a snake's head and returns it
 * doesnt check for proper creation
 * returns a pointer to it
*/
struct snake *create_snake(const int canvas_side_length); //change the argument to the spawn point

/*
 * creates a new node at the end of snake's body,
 * checks if it was properly created with assert
 * returns a pointer to it
*/
struct snake *grow_snake(struct snake *head, const int canvas_side_length);


void print_snake(WINDOW *win, struct snake *head);


bool move_snake(int side_length, struct snake *head, struct fruit *fr);

/*
 * checks if a given point p would be on the snake, starting from the s cell
 * if yes returns true else false
*/
bool on_snake(struct point *p, struct snake *s);


void set_new_tail(const int move_direction, const int canvas_side_length, struct snake *tail, struct snake *new_tail);

void move_point(struct point *p, int move_direction);


void wrap_point_around_canvas(int side_length, struct point *p);

bool on_fruit(struct point *p, struct point *fruit_pos);
#endif
