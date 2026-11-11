#ifndef SNAKE_H
#define SNAKE_H

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Direction.h"

typedef struct
{
	List *start;
	List *end;
	Direction dir;
	bool alive;
} Snake;

Snake *snake_create(Point *start)
{
	List *list1 = list_create(start);
	List *list2 = list_create(point_create(start->x - 1, start->y));
	List *list3 = list_create(point_create(start->x - 2, start->y));

	list_link(list1, list2);
	list_link(list2, list3);

	Snake *snake = (Snake *)memset(malloc(sizeof(Snake)), 0, sizeof(Snake));
	snake->start = list1;
	snake->end = list3;
	snake->dir = RIGHT;
	snake->alive = true;

	return snake;
}

bool snake_includes(Snake *snake, Point *point)
{
	List *temp = snake->start;

	while (temp != NULL)
	{
		if (point_equals(temp->value, point))
			return true;

		temp = temp->next;
	}

	return false;
}

Point *snake_newPoint(Snake *snake, Direction dir)
{
	Point *origin = snake->start->value;

	snake->dir = dir == NONE || snake->dir == -dir ? snake->dir : dir;

	switch (snake->dir)
	{
	case UP:
		return point_create(origin->x, origin->y - 1);
	case DOWN:
		return point_create(origin->x, origin->y + 1);
	case LEFT:
		return point_create(origin->x - 1, origin->y);
	case RIGHT:
		return point_create(origin->x + 1, origin->y);
	default:
		exit(1);
	}
}

void snake_addStart(Snake *snake, Point *point)
{
	if (snake_includes(snake, point))
		snake->alive = false;

	List *node = list_create(point);
	list_link(node, snake->start);
	snake->start = node;
}

void snake_removeEnd(Snake *snake)
{
	snake->end = snake->end->prev;
	free(snake->end->next);
	snake->end->next = NULL;
}

void snake_free(Snake *snake)
{
	list_free(snake->start);
}

#endif // SNAKE_H