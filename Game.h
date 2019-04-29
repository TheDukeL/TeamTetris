#ifndef GAME_H
#define GAME_H

#include "Constants.h"
#include "Board.h"
#include "Tetromino.h"
#include "Screen.h"
#include <stdlib.h>   
#include <vector>
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
	Tetromino *fallingTetromino;
	vector<Tetromino*> nextTetrominos;
	Clock clock;
	Time time;
	Screen oneScreen;

	int level, lines, points, fallingTetrominoType, stallPlace = 4;
	bool started, closing, gameOver;

	void determineNextTetrominos();
	Tetromino* generateTetromino();
	void doAfterEvent();
	void finalizeTetromino();
	void checkGameOver();
	void moveLeft();
	void moveDown(int origin);
	void moveRight();
	void rotate();
	void checkBoard();
	void checkLines();
	void restart();
};

#endif
