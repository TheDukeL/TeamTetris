#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"
#include "Constants.h"

class Board
{
public:
	Board();
	~Board();

	void settleTetromino(Tetromino& tetromino);
	int checkAndCleanLines();
	bool movementAllowed(Tetromino& tetromino, int xOff, int yOff);
	bool checkGameOver();
	void cleanBoard();
	std::array<std::array<int, 13>, 23> getSettledPieces();

	const int getSIZEX();
	const int getSIZEY();

private:
	void cleanLine(int y);

	const int REALSIZEX = 13, REALSIZEY = 23;
	std::array<std::array<int, 13>, 23> settledPieces = {};
	const int SIZEXY[2] = {10, 20};
};

#endif