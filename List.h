#ifndef LIST_H
#define LIST_H

#include <malloc.h>
#include <string.h>
#include "Point.h"

typedef struct List_t
{
	Point *value;
	struct List_t *prev;
	struct List_t *next;
} List;

List *list_create(Point *value)
{
	List *list = (List *)memset(malloc(sizeof(List)), 0, sizeof(List));
	list->value = value;

	return list;
}

void list_link(List *node1, List *node2)
{
	node1->next = node2;
	node2->prev = node1;
}

List *list_start(List *list)
{
	List *start = list;

	while (start->prev != NULL)
		start = start->prev;

	return start;
}

List *list_end(List *list)
{
	List *end = list;

	while (end->prev != NULL)
		end = end->next;

	return end;
}

void list_concat(List *list1, List *list2)
{
	List *list1end = list_end(list1);

	List *list2start = list_start(list2);

	list_link(list1end, list2start);
}

void list_apply(List *list, List *predicate(List *))
{
	List *temp = list;

	while (temp != NULL)
	{
		predicate(temp);
		temp = temp->next;
	}
}

void list_free(List *list)
{
	List *start = list_start(list);

	while (start->next != NULL)
	{
		start = start->next;
		point_free(start->prev->value);
		memset(start->prev, 0, sizeof(*start));
		free(start->prev);
	}

	point_free(start->value);
	free(start);
}

#endif // LIST_H