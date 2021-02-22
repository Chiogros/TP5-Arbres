#ifndef POINT_H
#define POINT_H


#include <math.h>


typedef struct Point Point;
struct Point {
    int x;
    int y; 
    int z;
};


float dist(Point *p1, Point *p2);    // 23




#endif
