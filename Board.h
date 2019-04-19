#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"
#include "Constants.h"

class Board
{
public:
	Board();
	~Board();

	void addPieceToBoard(Tetromino& tetromino, int x, int y);
	int checkAndCleanLines();
	bool checkCollision(Tetromino& tetromino, int x, int y);
	bool movementAllowed(Tetromino& tetromino, int x, int y);
	bool checkGameOver();
	void cleanBoard();
	array<array<int, 13>, 23> getSettledPieces();

	const int getSIZEX();
	const int getSIZEY();
	const int getSTARTINGX();
	const int getSTARTINGY();

private:
	void cleanLine(int y);

	const int REALSIZEX = 13, REALSIZEY = 23;
	array<array<int, 13>, 23> settledPieces = {};
	const int SIZEXY[2] = { 10,20 }, STARTINGX = 4, STARTINGY = 0;
};

#endif