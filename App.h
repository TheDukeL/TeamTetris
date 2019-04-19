#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

class App
{
	
public:
	
	App();
	~App();
	bool startGame();


private:
	RenderWindow window;		
	const char *GAMENAME = "Tetris";
	const int WINDOWSIZEXY[2] = { 650,650 };
};

