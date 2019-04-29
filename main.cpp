#include <gtkmm.h>
#include "SFMLWidget.h"
#include "App.h"
#include "menu.h"

int main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv); 								// Initialize Gtk
	Gtk::Window window; 									// The GTK window will be our top level Window
    SFMLWidget ourRenderWindow(sf::VideoMode(2000, 1300));	// SFMLWidget for Gtk Window
    
    App app(ourRenderWindow);
	ourRenderWindow.show();
	
	Gtk::VBox ourVBox;
    Gtk::Button ourButton("Start"); //Just a clickable button, it will start the game
    ourButton.show();
    ourButton.signal_clicked().connect(sigc::mem_fun(&app, &App::startGame));

	ourVBox.pack_start(ourRenderWindow);
    ourVBox.pack_start(ourButton);
    ourVBox.show();
	window.add(ourVBox);
	Gtk::Main::run(window); //Draw the window
	
	return 0;
}