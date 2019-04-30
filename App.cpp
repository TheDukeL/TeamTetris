#include <gtkmm.h>
#include "Game.h"
#include "App.h"

App::App(SFMLWidget& widget) : widget(widget)
{
	widget.renderWindow.create(VideoMode(WINDOWSIZEXY[X],WINDOWSIZEXY[Y]), GAMENAME, Style::Titlebar | Style::Close);
	widget.signal_draw().connect(sigc::bind_return(sigc::hide(sigc::mem_fun(this, &App::startGame)),true));
}

App::~App() {};

void App::startGame()
{
	Game oneGame(widget.renderWindow);
	oneGame.start();

	while (widget.renderWindow.isOpen())
	{
		Event event;
		
		//sends events to game
		while (widget.renderWindow.pollEvent(event))
		{
			oneGame.update(event);
		}
		//controlls time for moving down a piece
		oneGame.tick();
	}
}