#ifndef MENU_H
#define MENU_H

#include <gtkmm.h>

class tetris_window:public Gtk::Window
{
public:
  tetris_window();
  virtual ~tetris_window();



protected:
////
void helping();
void startGame();

  Gtk::Image image;
  Gtk::Button start;
  Gtk::Button help;
  Gtk::Grid grid;
};

#endif
