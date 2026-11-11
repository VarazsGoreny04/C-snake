#include "Game.h"

int main()
{
	Game *game = game_create(9, 9);

	game_run(game);
	game_free(game);

	return 0;
}