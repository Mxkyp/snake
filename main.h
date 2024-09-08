#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include <stdbool.h>
#include <time.h>
#include "fruit.h"

#define TOP 0
#define BOT 1
#define SNAKE_COLOR 2
#define BACKGROUND_BORDER_COLOR 1


enum directions{UP = 0, DOWN, LEFT = 3, RIGHT};

/* renders the snake, fruit on the canvas */
void render(WINDOW *content, struct fruit *fr, struct snake *head, int starty, int startx);

/* takes input from the user to change the snake's move direction accordingly */
void input(int *direction);

/*
  if not spawned or spawned at least FRUIT_LIFETIME_SECONDS away,
  delets old fruit, creates new, prints it and restarts the fruit timer
 */
void manage_fruit(WINDOW *content, struct fruit *fr, struct snake *s);

/*
 gives a 300ms window for inputing a char
 */
void get_move(int *c);

#endif // MAIN_H_
