#include "../worm.h"
#include "../canvas.h"
#include <stdlib.h>
#include <unistd.h>

struct snake *create_snake(const int canvas_side_length){
  struct snake *s = malloc(sizeof(*s));
  s->coords.y = canvas_side_length/2;
  s->coords.x = canvas_side_length/2;
  s->next = NULL;
  s->before = NULL;
  return s;
}

void print_snake(WINDOW * win, struct snake *s, struct point old_tail_coords){
  mvwdelch(win, old_tail_coords.y, old_tail_coords.x);
  for(struct snake *p = s; p != NULL; p = s->next){
    mvwaddch(win, p->coords.y, p->coords.x,'o' | A_BOLD);
  }
}

void update_snake(WINDOW *win, struct snake **s, const int direction){
  struct snake *last;

  for(last = *s; last->next != NULL;last = (*s)->next);

  struct snake old_tail;
  old_tail.coords = last->coords;

  for( ; last->before != NULL; last = last->before){
    *last = *last->before;
  }

  switch(direction){
    case UP: (*s)->coords.y--;
      break;
    case RIGHT: (*s)->coords.x++;
      break;
    case DOWN: (*s)->coords.y++;
      break;
    case LEFT: (*s)->coords.x--;
      break;
  }

  print_snake(win, *s, old_tail.coords);

}
