#include "../snake.h"
#include "../fruit.h"
#include "../main.h"
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>

struct snake *create_snake(const int canvas_side_length){
  struct snake *s = malloc(sizeof(*s));
  s->coords.y = canvas_side_length/2;
  s->coords.x = canvas_side_length/2;
  s->before = NULL;
  s->move_direction = UP;
  s->game_score = 0;

  for(int i = 1; i < START_SIZE; i++){
    grow_snake(s, canvas_side_length);
  }
  return s;
}


struct snake *grow_snake(struct snake *head, const int canvas_side_length){
  int direction = head->move_direction;
  struct snake *new = malloc(sizeof(*new));
  assert(new);

  while(head->next != NULL){
    head = head->next;
  }

  head->next = new;

  set_new_tail(direction, canvas_side_length, head, new);
  new->before = head;
  new->next = NULL;

  return new;
}

void set_new_tail(const int move_direction, const int canvas_side_length, struct snake *tail, struct snake *new_tail){
  if(move_direction == UP){
    new_tail->coords.y = tail->coords.y--;
    new_tail->coords.x = tail->coords.x;
  }
  else if(move_direction == DOWN){
    new_tail->coords.y = tail->coords.y++;
    new_tail->coords.x = tail->coords.x;
  }
  else if(move_direction == RIGHT){
    new_tail->coords.y = tail->coords.y;
    new_tail->coords.x = tail->coords.x--;
  }
  else if(move_direction == LEFT){
    new_tail->coords.y = tail->coords.y;
    new_tail->coords.x = tail->coords.x++;
  }
  wrap_point_around_canvas(canvas_side_length, &new_tail->coords);
}

void print_snake(WINDOW *win, struct snake *head){
  start_color();
  init_pair(SNAKE_COLOR, COLOR_BLUE, COLOR_BLACK);

  while(head != NULL){
    mvwaddch(win, head->coords.y, head->coords.x, 'o' | A_BOLD | COLOR_PAIR(2));
    head = head->next;
  }
}

bool move_snake(int side_length, struct snake *head, struct fruit *fruit){
  struct snake *mover = head->next;

  while(mover->next != NULL){ // select the last 2 elements (mover is the last)
    mover = mover->next;
    head = head->next;
  }

  while(true){ // keep replacing each element coordinates with the preceeding elements coordinates
    mover->coords.y = head->coords.y;
    mover->coords.x = head->coords.x;

    if(head->before == NULL){ break; }
    mover = mover->before;
    head = head->before;
  }

  move_point(&head->coords, head->move_direction);
  wrap_point_around_canvas(side_length, &head->coords);

  if(on_snake(&head->coords, head->next)){ return false; }

  else if(on_fruit(&head->coords, &fruit->coords)){ // if head lands on a fruit enlargen the snake by 1, despawn the fruit
    grow_snake(head, side_length);
    fruit->is_spawned = false;
    head->game_score++;
  }
  return true;
}

void move_point(struct point *p, int move_direction){
  switch(move_direction){
    case UP: p->y--;
      break;
    case DOWN: p->y++;
      break;
    case RIGHT: p->x++;
      break;
    case LEFT: p->x--;
      break;
  };
}

void wrap_point_around_canvas(int side_length, struct point *p){
      if      (p->y < 0){ p->y = side_length-1;}
      else if (p->x >= side_length){ p->x = 0;}
      else if (p->y >= side_length){ p->y = 0;}
      else if (p->x < 0){ p->x = side_length-1;}
}

bool on_fruit(struct point *p, struct point *fruit_pos){
  if(p->y == fruit_pos->y && p->x == fruit_pos->x){
    return true;
  }
  return false;
}

bool on_snake(struct point *p, struct snake *s){
  while(s != NULL){
    if(p->y == s->coords.y && p->x == s->coords.x){
      return true;
    }
    s = s->next;
  }
  return false;
}
