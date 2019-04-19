#pragma once

#include "Constants.h"
#include "Board.h"
#include "Tetromino.h"
#include "Screen.h"
#include <stdlib.h>    
#include <ctime> 
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class Game
{
	
public:

	void tick();
	void update(const Event event);
	void start();
	 Game(RenderWindow &window);
	~Game();
	
	
private:
	Board oneBoard;
	Tetromino *tetrominos[7][4], *fallingTetromino;
	Clock clock;
	Time time;
	Screen oneScreen;

	const int NUMTETROMINOS = 7,NUMMAXROT = 4,ONELEVELSPEED= 50,INITALSPEED= 600, ONEPOINT = 10,FINALLEVEL = 10,
		INITIALROTATION=1;
	enum origin { APP, TICK };

	int xy[2],level,lines,points,fallingTetrominoType;
	bool started, closing, gameOver;

	void generateTetrominos();
	void generateFallingTetromino();
	void doAfterEvent();
	void checkGameOver();
	void moveLeft();
	void moveDown(int origin);
	void moveRight();
	void rotate();
	void checkBoard();
	void checkLines();
	void restart();


};

