#include "../point.h"

struct point set_yx(const int y_val, const int x_val){
  struct point temp = {.y = y_val, .x = x_val};
  return temp;
}

struct point set_default(void){
  struct point temp = {.y = 0, .x = 0};
  return temp;
}

struct point set_to_middle_of_square(const int square_side_length){
  struct point temp = {.y = square_side_length/2, .x = square_side_length/2};
  return temp;
}
