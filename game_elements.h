#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H
#include "point.h"
#include <time.h>
#include <stdbool.h>
#include <curses.h>

#define MIN_SIZE 8 // (its minimal size of the board)
#define FRUIT_LIFETIME_SECONDS 5;
struct fruit{
  struct point coords;
  time_t spawn_time;
  bool is_spawned;
  time_t lifetime;
};

#define START_SIZE 3 //the starting length of the snake
struct snake{
  int move_direction;
  int game_score;
  struct point coords;
  struct snake *next;
  struct snake *before;
};

struct GameElements{
 struct snake *snake_head;
 struct fruit *fruit;
};

///////////////////////////////////////////////////////////////////////////////////////
/////////////////FRUIT PROTOTYPES///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
/////////////////SNAKE PROTOTYPES///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

/*
 * creates a snake's head and returns it
 * doesnt check for proper creation
 * returns a pointer to it
*/
struct snake *create_snake(const int canvas_side_length); //change the argument to the spawn point

/*
 * free's the memory allocated for snake
*/
void delete_snake(struct snake *head);

/*
 * creates a new node at the end of snake's body,
 * checks if it was properly created with assert
 * returns a pointer to it
*/
struct snake *grow_snake(struct snake *head);


void print_snake(WINDOW *win, struct snake *head);


bool move_snake(int side_length, struct GameElements *game);

/*
 * checks if a given point p would be on the snake, starting from the s cell
 * if yes returns true else false
*/
bool on_snake(struct point *p, struct snake *s);


void set_new_tail(struct snake *tail, struct snake *new_tail);

void move_point(struct point *p, int move_direction);


void wrap_point_around_canvas(int side_length, struct point *p);

bool on_fruit(struct point *p, struct point *fruit_pos);
#endif
