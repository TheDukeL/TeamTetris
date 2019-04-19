#include "Game.h"
#include "App.h"

App::App() {};
App::~App() {};

bool App::startGame()
{
	window.create(VideoMode(WINDOWSIZEXY[X],WINDOWSIZEXY[Y]), GAMENAME, Style::Titlebar | Style::Close);
	Game oneGame(window);
	oneGame.start();

	while (window.isOpen())
	{
		Event event;
		
		//sends events to game
		while (window.pollEvent(event))
			oneGame.update(event);
		
		//controlls time for moving down a piece
		oneGame.tick();
	}
	return false;
}