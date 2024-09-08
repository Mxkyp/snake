#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include <stdbool.h>
#include <time.h>
#include "fruit.h"
#include "point.h"

#define TOP 0
#define BOT 1
#define SNAKE_COLOR 2
#define BACKGROUND_BORDER_COLOR 1

struct snake;
struct GameElements{
 struct snake *snake_head;
 struct fruit *fruit;
};

enum directions{UP = 0, DOWN, LEFT = 3, RIGHT};
/*
 * To create game_elements and return a pointer to a structure holding them,
 * if failed aborts the program
*/
struct GameElements* create_game_elements();

/* renders the snake, fruit on the canvas */
void render(WINDOW *content,struct GameElements *game_elements, struct point *background_upper_left_corner);

/* takes input from the user to change the snake's move direction accordingly */
void input(int *direction);

/*
  if not spawned or spawned at least FRUIT_LIFETIME_SECONDS away,
  delets old fruit, creates new, prints it and restarts the fruit timer
 */
void manage_fruit(WINDOW *content, struct GameElements *game_elements);

/*
 gives a 300ms window for inputing a char
 */
void get_move(int *c);

#endif // MAIN_H_
