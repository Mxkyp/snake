#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include "canvas.h"
#include <stdbool.h>
#include <time.h>

/* renders the snake, fruit on the canvas */
void render(WINDOW *content, struct fruit *fr, struct snake *head, int starty, int startx);

/* takes input from the user to change the snake's move direction accordingly */
void input(int *direction);

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
WINDOW *create_canvas(int side_length, int *start_y, int *start_x);

/*
  if not spawned or spawned at least FRUIT_LIFETIME_SECONDS away,
  delets old fruit, creates new, prints it and restarts the fruit timer
 */
void manage_fruit(WINDOW *content, struct fruit *fr, struct snake *s);

/*
 gives a 300ms window for inputing a char
 */
void get_move(int *c);

void end_screen(WINDOW *main, int score, int side_length);
void print_score(int game_score, int starty, int startx);
#endif // MAIN_H_
