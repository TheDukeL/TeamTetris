#include "menu.h"
#include<iostream>

tetris_window::tetris_window()
{
  set_border_width(10);

  image.set("tetrismenubackground1.png");
  grid.attach(image,0,0,3,1);

  
  
  
  start.add_label("Start");
  //
  grid.attach(start,0,1,1,1);

  


  settings.add_label("Settings");
  //
  grid.attach(settings,1,1,1,1);
  ////
  settings.signal_pressed().connect(sigc::mem_fun(*this,&tetris_window::settingspop));
  ////
  
  
  help.add_label("Help");
  //
  grid.attach(help,2,1,1,1);
  ////
  help.signal_pressed().connect(sigc::mem_fun(*this,&tetris_window::helping));
  ////
  
  

  grid.show_all();

  add(grid);
}

tetris_window::~tetris_window()
{}
////


void tetris_window::helping(){
  image.set("tetris_help.png");
}



void tetris_window::settingspop(){
  Gtk::MessageDialog dialog(*this, "Music?",false,Gtk::MESSAGE_QUESTION,Gtk::BUTTONS_YES_NO); 
  int Answer=dialog.run(); 
  switch(Answer){
  case(Gtk::RESPONSE_YES):
      //music on
    break;
  case(Gtk::RESPONSE_NO):
    //music off
    break;
  default:
    //music on by default
      break;
  }
}
