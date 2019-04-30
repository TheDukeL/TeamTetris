#include <gtkmm.h>
#include "SFMLWidget.h"
#include "App.h"
#include "menu.h"

int main(int argc, char** argv)
{

    Gtk::Main kit(argc, argv);	// Initialize Gtk

    tetris_window menuWindow;	// Create and run start menu
    Gtk::Main::run(menuWindow);	// Will process after start button is clicked

    Gtk::Window window; 									// The GTK window will be our top level Window
    SFMLWidget ourRenderWindow(sf::VideoMode(1600, 1600));	// SFMLWidget to put our SFML game into Gtk Window

    App app(ourRenderWindow);	// Create game window
    ourRenderWindow.show();
    Gtk::VBox ourVBox;
    ourVBox.pack_start(ourRenderWindow);
    ourVBox.show();
    window.add(ourVBox);
    Gtk::Main::run(window); //Draw and run the game window

    return 0;
}
