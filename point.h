#ifndef POINT_H
#define POINT_H

struct point{
  int x,y;
};

struct point set_yx(const int y, const int x);
/*
 * returns a (0,0) point
*/
struct point set_default(void);
/*
 * returns a point at the middle of a square of a square
*/
struct point set_to_middle_of_square(const int square_side_length);

#endif
