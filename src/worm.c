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
  return s;
}

struct snake *new_node(struct snake *head){
  struct snake *new = malloc(sizeof(*new)), *passer;
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
  while(head != NULL){
    mvwaddch(win, head->coords.y, head->coords.x, 'o' | A_BOLD);
    head = head->next;
  }
}

bool move_snake(int direction, struct snake *head){
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

  switch(direction){ // update the head
    case UP: head->coords.y--;
      break;
    case RIGHT: head->coords.x++;
      break;
    case DOWN: head->coords.y++;
      break;
    case LEFT: head->coords.x--;
      break;
  };

}
