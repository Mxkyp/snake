#ifndef MAIN_H_
#define MAIN_H_
#include <curses.h>
#include <stdbool.h>
#include <time.h>
#include "point.h"

struct GameBoard;

#define TOP 0
#define BOT 1
#define SNAKE_COLOR 2
#define BACKGROUND_BORDER_COLOR 1

enum directions{UP = 0, DOWN, LEFT = 3, RIGHT};

/*
 * create game_elements(snake and fruit) and return a pointer to a structure holding them,
 * if failed aborts the program
*/
struct GameElements* create_game_elements();
void delete_game_elements(struct GameBoard* board, struct GameElements *game);

/* renders the snake, fruit on the content window */
void render(struct GameBoard *board, struct GameElements *game_elements);

/* takes input from the user to change the snake's move direction accordingly */
void input(int *direction);

/*
  if not spawned or spawned at least FRUIT_LIFETIME_SECONDS away,
  delets old fruit, creates new, prints it and restarts the fruit timer
 */
void manage_fruit(WINDOW *content, struct GameElements *game_elements);



/*
 * disables line buffering, erase kill character processing and echoing of input
*/
void set_curses_input_options();

/*
 gives a 300ms window for inputing a char
 */
void get_move(int *c);

/*
 * sets the direction based on input ch (w == up , a == left...)
 * validates it by preventing a 180 turn (can't go the opposite direction)
*/
void set_and_validate_direction(int *direction, int input_ch);

#endif // MAIN_H_
