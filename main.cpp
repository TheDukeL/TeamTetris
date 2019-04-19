#include "Game.h"
#include "App.h"

int main()
{
	App app;

	while ( app.startGame() ) {};

	return 0;
}