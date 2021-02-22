#include "point.h"

float dist(Point *p1, Point *p2) {

    return sqrt(fabs(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2) + pow(p1->z - p2->z, 2)));
}
