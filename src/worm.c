#include "../worm.h"
#include "../canvas.h"
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
    grow_snake(s);
  }
  return s;
}

struct snake *grow_snake(struct snake *head){
  struct snake *new = malloc(sizeof(*new));
  assert(new);
  while(head->next != NULL){
    head = head->next;
  }

  head->next = new;

  new->coords.x = head->coords.x + 1;
  new->coords.y = head->coords.y;
  new->before = head;
  new->next = NULL;

  return new;
}

void print_snake(WINDOW *win, struct snake *head){
  start_color();
  init_pair(2, COLOR_BLUE, COLOR_BLACK);

  while(head != NULL){
    mvwaddch(win, head->coords.y, head->coords.x, 'o' | A_BOLD | COLOR_PAIR(2));
    head = head->next;
  }
}

bool move_snake(int side_length, struct snake *head, struct fruit *fr){
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

  switch(head->move_direction){ // update the head
    case UP: head->coords.y--;
      if(head->coords.y < 0){ head->coords.y = side_length-1;}
      break;
    case RIGHT: head->coords.x++;
      if(head->coords.x >= side_length){ head->coords.x = 0;}
      break;
    case DOWN: head->coords.y++;
      if(head->coords.y >= side_length){ head->coords.y = 0;}
      break;
    case LEFT: head->coords.x--;
      if(head->coords.x < 0){ head->coords.x = side_length-1;}
      break;
  };

  if(on_snake(&head->coords, head->next)){ return false; }
  else if(head->coords.y == fr->coords.y && head->coords.x == fr->coords.x){ // if head lands on a fruit enlargen the snake by 1, delete the fruit
    grow_snake(head);
    fr->is_spawned = false;
    head->game_score++;
  }
  return true;
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
