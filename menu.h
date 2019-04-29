#ifndef MENU_H
#define MENU_H

#include<gtkmm.h>

class tetris_window:public Gtk::Window
{
public:
  tetris_window();
  virtual ~tetris_window();



protected:
////
void helping();
void settingspop();

  Gtk::Image image;
  Gtk::Button start;
  Gtk::Button settings;
  Gtk::Button help;
  Gtk::Grid grid;
};

#endif
