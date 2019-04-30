#include <gtkmm.h>
#include "SFMLWidget.h"
#include "App.h"
#include "menu.h"

int main(int argc, char** argv)
{

    Gtk::Main kit(argc, argv); 								// Initialize Gtk
	tetris_window menuWindow;
	Gtk::Main::run(menuWindow);
	
	Gtk::Window window; 									// The GTK window will be our top level Window
    SFMLWidget ourRenderWindow(sf::VideoMode(1600, 1600));	// SFMLWidget for Gtk Window
    
    App app(ourRenderWindow);
	ourRenderWindow.show();
	
	Gtk::VBox ourVBox;

	ourVBox.pack_start(ourRenderWindow);
    ourVBox.show();
	window.add(ourVBox);
	Gtk::Main::run(window); //Draw the window

	
	return 0;
}