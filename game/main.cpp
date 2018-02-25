#include"Game.h"

int main()
{
	Game game;

	while (game.windowIsOpen())
	{
		game.update();
		game.render();
	}

	return 0;
}

//test