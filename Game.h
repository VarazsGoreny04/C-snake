#ifndef GAME_H
#define GAME_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Point.h"
#include "List.h"
#include "Snake.h"
#include "Direction.h"

typedef struct
{
	Point *dimensions;
	Snake *snake;
	Point *apple;
	int score;
} Game;

void game_printTable(Point *dimensions, int score)
{
	printf("+");
	for (int x = dimensions->x; x >= 1; --x)
		printf("--");
	printf("+\n");

	for (int y = dimensions->y; y >= 1; --y)
	{
		printf("|");
		for (int x = dimensions->x; x >= 1; --x)
			printf("  ");
		printf("|\n");
	}

	printf("+");
	for (int x = dimensions->x; x >= 1; --x)
		printf("--");
	printf("+\n");

	printf("Score: %d\n", score);
}

void game_jumpCursor(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

void game_jumpCursorToPoint(Point *point)
{
	game_jumpCursor((point->x + 1) * 2, point->y + 2);
}

void game_printApple(Point *apple)
{
	game_jumpCursorToPoint(apple);
	printf("()");
}

void game_printSnakePoint(Point *snakePoint)
{
	game_jumpCursorToPoint(snakePoint);
	printf("[]");
}

void game_printScore(Point *dimensions, int score)
{
	game_jumpCursor((int)(sizeof("Score: ")), dimensions->y + 3);
	printf("%d", score);
}

void game_printErase(Point *point)
{
	game_jumpCursorToPoint(point);
	printf("  ");
}

void game_printSnake(Snake *snake)
{
	List *node = snake->start;
	while (node != NULL)
	{
		game_printSnakePoint(node->value);
		node = node->next;
	}
}

Point *game_createApple(Point *dimensions, Point *oldApple, Snake *snake)
{
	int length = 0;
	List *points = NULL;

	{
		List *endOfPoints = NULL;

		for (int y = dimensions->y - 1; y >= 0; --y)
		{
			for (int x = dimensions->x - 1; x >= 0; --x)
			{
				Point *point = point_create(x, y);

				if (!point_equals(oldApple, point) && !snake_includes(snake, point))
				{
					++length;

					if (points == NULL)
					{
						points = list_create(point);
						endOfPoints = points;
					}
					else
					{
						list_link(endOfPoints, list_create(point));
						endOfPoints = endOfPoints->next;
					}
				}
				else
					point_free(point);
			}
		}
	}

	if (points == NULL)
		exit(1);
	else
	{
		int random = rand() % length;

		List *temp = points;
		int index = 0;
		while (index != random)
		{
			temp = temp->next;
			++index;
		}

		Point *result = point_create(temp->value->x, temp->value->y);

		list_free(points);

		return result;
	}
}

Game *game_create(unsigned int x, unsigned int y)
{
	srand(time(0));

	if (x < 5 || y < 5)
		exit(1);

	Game *game = (Game *)memset(malloc(sizeof(Game)), 0, sizeof(Game));
	game->dimensions = point_create(x, y);
	game->snake = snake_create(point_create((int)(x / 2), (int)(y / 2)));
	game->apple = game_createApple(game->dimensions, game->snake->start->value, game->snake);
	game->score = 0;

	return game;
}

void game_createNewApple(Game *game)
{
	if (!game->snake->alive)
		return;

	Point *oldApple = game->apple;
	game->apple = game_createApple(game->dimensions, oldApple, game->snake);
	point_free(oldApple);
}

bool game_boundCheck(Point *dimensions, Point *point)
{
	return point->x < 0 || point->y < 0 || point->x >= dimensions->x || point->y >= dimensions->y;
}

void game_step(Game *game, Direction dir)
{
	if (!game->snake->alive)
		return;

	Point *newHead = snake_newPoint(game->snake, dir);

	if (point_equals(newHead, game->apple))
	{
		++game->score;
		game_printScore(game->dimensions, game->score);
		game_createNewApple(game);
		game_printApple(game->apple);
	}
	else
	{
		game_printErase(game->snake->end->value);
		snake_removeEnd(game->snake);
	}

	if (snake_includes(game->snake, newHead) || game_boundCheck(game->dimensions, newHead))
	{
		game->snake->alive = false;
		return;
	}

	snake_addStart(game->snake, newHead);
	game_printSnakePoint(game->snake->start->value);
}

Direction game_readDirection()
{
	char c = getch();

	switch (c)
	{
	case 'w':
		return UP;
	case 's':
		return DOWN;
	case 'a':
		return LEFT;
	case 'd':
		return RIGHT;
	default:
		return NONE;
	}
}

void game_run(Game *game)
{
	system("cls");

	game_printTable(game->dimensions, game->score);
	game_printApple(game->apple);
	game_printSnake(game->snake);

	while (game->snake->alive)
	{
		game_jumpCursor(0, game->dimensions->y + 4);
		game_step(game, game_readDirection());
	}

	game_jumpCursor(0, game->dimensions->y + 4);
	printf("The game has ended.\n");
}

void game_free(Game *game)
{
	point_free(game->dimensions);
	snake_free(game->snake);
	point_free(game->apple);
}

#endif // GAME_H