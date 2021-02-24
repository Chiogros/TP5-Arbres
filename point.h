#ifndef POINT_STRUCT_H
#define POINT_STRUCT_H

typedef struct Point Point;
struct Point {
    int x;
    int y; 
    int z;
};

#endif

#ifndef POINT_H
#define POINT_H

#include <math.h>

float dist(Point *p1, Point *p2);    // 23


#endif
