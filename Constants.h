#ifndef CONSTANTS_H
#define CONSTANTS_H

enum origin { APP, TICK };
const float STARTINGPX = 64; //board offset position from 0 in pixels (used to render the tetrominos aligned to the grid correctly)
const int NUMTETROMINOS = 7; //how many tetrominoes can be loaded into the randomizer at once
const int ONELEVELSPEED = 150; //how much the speed increments per level
const int INITALSPEED = 750; //how fast the tetrominoes fall at game start
const int ONEPOINT = 10; //how many points you get per completed line
const int LINESFORLEVEL = 10; //how many lines required to increment the level by 1
const int EMPTY = 0, X = 0, Y = 1; //shorthands for common values
const int STARTINGX = 3, STARTINGY = 0; //the position on the grid where new tetrominos spawn

const bool DEBUGMODE = false;

#endif