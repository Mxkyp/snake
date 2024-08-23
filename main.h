#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include "canvas.h"
#include <stdbool.h>
#include <time.h>

/*
 * creates the background window and canvas window,
 * returns false if any window failed to create
 * returns true if both were created correctly
*/
bool create_windows(int side_length, WINDOW** content, WINDOW** background, int *starty, int *startx);

/*
 * creates background window for the playing canvas,
 * returns a pointer to it
*/
WINDOW *create_background(int side_length, int *start_y, int *start_x);

/*
 * creates a window representing the canvas, inside the background window
 * returns a pointer to it
*/
WINDOW *wcreate_canvas(int side_length, int *start_y, int *start_x);

/*
  return true if fruit is not spawned on the window
  or if the time elapsed between its spawn > 5 seconds
*/
bool fruit_passed(bool spawned, clock_t fruit_spawn, clock_t fruit_lifetime);
#endif // MAIN_H_
