#ifndef APP_H
#define APP_H

#include <gtkmm/widget.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SFMLWidget.h"

using namespace sf;

class App
{
	
public:
	SFMLWidget& widget;
	App(SFMLWidget& widget);
	~App();
	void startGame();

private:		
	const char *GAMENAME = "Tetris";
	const int WINDOWSIZEXY[2] = { 650,650 };
};

#endif