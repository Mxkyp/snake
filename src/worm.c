#include "../worm.h"
#include "../canvas.h"
#include <stdlib.h>
#include <unistd.h>

bool print_snake(WINDOW *win, struct snake *s){
  for(struct point *p = s->head; ; p++){
   mvwaddch(win, p->y, p->x, 'o' | A_BOLD);
   if(p == s->tail){ break; }
  }
}

struct snake* create_snake(int side_length){
  struct snake* snake = malloc(sizeof(int*) * 2
                               + (side_length * side_length) * sizeof(int));
  if(snake == NULL){
    return NULL;
  }

  snake->head = &snake->body[0];
  snake->head->y = side_length/2;
  snake->head->x = side_length/2;
  snake->tail = snake->head;
  return snake;
}

bool move_snake(WINDOW *win, struct snake *s, const int side_length, struct point *fruit_position, const int direction){
  if(check_move(s, side_length, direction)){
    update_snake(win, s, direction);
    return true;
  }
  return false;
}

void update_snake(WINDOW* win, struct snake *s, const int direction){
  struct point *to_free = s->tail;
  for(struct point *prev = s->tail, *next = prev; next != s->head; prev--, next-=2){
    refresh();
    *prev = *next;
  }

  if(s->tail != s->head){
  mvwdelch(win, to_free->y,to_free->x);
  }
  timeout(150);
  refresh();

  switch(direction){
    case UP:   s->head->y--;
      break;
    case RIGHT:s->head->x++;
      break;
    case DOWN: s->head->y++;
      break;
    case LEFT: s->head->x--;
      break;
  };
}

/*
 * left-top point of the canvas= (0, 0)
 * right-bottom point of the canvas= (side_length, side_length)
*/
bool check_move(struct snake *s,const int side_length, const int move_direction){
  switch(move_direction){
    case UP: return    (s->head->y - 1 >= 0);
      break;
    case RIGHT: return (s->head->x + 1 <= side_length);
      break;
    case DOWN: return  (s->head->y + 1 <= side_length);
      break;
    case LEFT: return  (s->head->x - 1 >= 0);
      break;
  };
}
