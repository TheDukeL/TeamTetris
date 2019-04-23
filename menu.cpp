#include "menu.h"
#include<iostream>

tetris_window::tetris_window()
{
  set_border_width(10);

  image.set("tetris.png");
  grid.attach(image,0,0,3,1);

  start.add_label("Start");
  //
  grid.attach(start,0,1,1,1);



  settings.add_label("Settings");
  //
  grid.attach(settings,1,1,1,1);

  help.add_label("Help");
  //
  grid.attach(help,2,1,1,1);

  grid.show_all();

  add(grid);
}

tetris_window::~tetris_window()
{}
