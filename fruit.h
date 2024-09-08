#ifndef CANVAS_H_
#define CANVAS_H_
#include <stdbool.h>
#include <time.h>
#include <curses.h>
#include "main.h"
#include "point.h"

#define FRUIT_LIFETIME_SECONDS 5;
#define MIN_SIZE 8

struct snake;
struct GameElements;


struct fruit{
  struct point coords;
  time_t spawn_time;
  bool is_spawned;
  time_t lifetime;
};

/*
 * creates a random coordinate fruit_p within the square of side_length
 * thats not on the snake,
 * then call print_fruit(win, fruit_p)
*/
void spawn_fruit(WINDOW * win, struct GameElements *game_elements, int side_length);

/*
 creates an object of fruit class, and initalizes it with default values
 */
struct fruit *create_fruit(void);

/*
 * prints the fruits at the point *p
*/
void print_fruit(WINDOW * win, struct point *p);

/*
 checks if either fruit isn't spawned, or the time since it has spawned is greater than FRUIT_LIFETIME_SECONDS
 */
bool check_fruit(struct fruit *fr);

#endif
