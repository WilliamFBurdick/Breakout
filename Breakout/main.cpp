#include "Game.h"
#include <stdexcept>
#include <cstdio>

int main(int argc, char* argv[])
{
	try
	{
		Game game;
		game.Run();
	}
	catch (std::exception e)
	{
		printf("ERROR: %s", e.what());
	}
	return 0;
}