#ifndef POINT_H
#define POINT_H

#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	int x;
	int y;
} Point;

Point *point_create(int x, int y)
{
	Point *point = (Point *)memset(malloc(sizeof(Point)), 0, sizeof(Point));
	point->x = x;
	point->y = y;

	return point;
}

bool point_equals(Point *p1, Point *p2)
{
	return p1->x == p2->x && p1->y == p2->y;
}

void point_free(Point *point)
{
	free(point);
}

#endif // POINT_H