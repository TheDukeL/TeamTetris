#pragma once

enum colors { LIGHTBLUE = 1, BLUE = 2, ORANGE = 3, YELLOW = 4, GREEN = 5, VIOLET = 6, RED = 7 };
const int colorsRGB[7][3] = { 
								{0,240,240},//Lightblue 
								{0,0,240},	//Blue
								{240,160,0},//Orange
								{240,240,0},//Yellow
								{0,240,0},	//Green
								{160,0,240},//Violet
								{240,0,0}	//Red
							};
enum eventGame { UP, DOWN, LEFT, RIGHT };
const int EMPTY = 0, //used when a square of the board or tetromino is empty 
			R = 0, G = 1, B = 2;
const float STARTINGXPIECESPX = 295, ONEXYPX = 29.9f, STARTINGXPX = 175, STARTINGYPX = 50;
const int LINESFORLEVEL = 10, 
			X = 0, Y = 1;

