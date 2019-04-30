#include "Board.h"
#include <iostream>
#include <list>

using namespace std;

Board::Board() {};
Board::~Board() {};

// Adds a tetris piece to the board of type tetromino at [x, y]
void Board::settleTetromino(Tetromino& tetromino)
{		
	for (int i = 0; i < tetromino.getSIZEXY(); i++)
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
			if (tetromino.getShape()[i][j] != EMPTY)
				settledPieces[i+tetromino.getY()][j+tetromino.getX()] = tetromino.getShape()[i][j];
}

//check if the movement is allowed to xOff, yOff
bool Board::movementAllowed(Tetromino & tetromino, int xOff, int yOff)
{
	int x = tetromino.getX();
	int y = tetromino.getY();
	int size = tetromino.getSIZEXY();

	int xMin = x+tetromino.getBoundsLeft()+xOff; //left bound
	int xMax = x+size-tetromino.getBoundsRight()+xOff; //right bound
	int yMin = y+tetromino.getBoundsTop()+yOff; //top bound
	int yMax = y+size-tetromino.getBoundsBottom()+yOff; //bottom bound

	//prevent the tetromino from going off the game board
	if (xMin < 0 || xMax > SIZEXY[X] || yMax > SIZEXY[Y])
		return false;

	//check and see if any of the tetromino's squares overlap with any squares on the board or go out-of-bounds
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tetromino.getShape()[i][j] != EMPTY && settledPieces[i+y+yOff][j+x+xOff] != EMPTY)
				return false;
		}
	}

	return true;
}

//checks lines, cleans them and returns the amount of lines cleaned (for incrementing score)
int Board::checkAndCleanLines()
{
	list<int> linesToClean;
	bool found = false;

	for (int i = 0; i < SIZEXY[Y]; i++)
	{
		found = true;

		for (int j = 0; j < SIZEXY[X]; j++)
			if (settledPieces[i][j] == EMPTY)
				found = false;

		if (found) //we found a filled line
			linesToClean.push_back(i);
	}

	if (linesToClean.empty())
		return EMPTY;

	for (int line : linesToClean)
		cleanLine(line);
		
	return linesToClean.size();
}

// Clears line at height y
void Board::cleanLine(int y)
{
	for (int j = 0; j < SIZEXY[X]; j++)
		settledPieces[y][j] = EMPTY;

	for (int i = y; i > 0; i--)
	{
		for (int j = 0; j < SIZEXY[X]; j++)
		{			
			settledPieces[i][j] = settledPieces[i-1][j];
			settledPieces[i-1][j] = EMPTY;
		}
	}
}

// Returns true if any piece on the top row is filled (game over)
bool Board::checkGameOver()
{
	for (int j = 0; j < SIZEXY[X]; j++)
		if (settledPieces[0][j] != EMPTY)
			return true;

	return false;
}

// Replaces every piece on the board with EMPTY
void Board::cleanBoard()
{
	for (int i = 0; i < SIZEXY[Y]; i++)
		for (int j = 0; j < SIZEXY[X]; j++)
			settledPieces[i][j] = EMPTY;
}

std::array<std::array<int, 13>, 23> Board::getSettledPieces()
{
	return settledPieces;
}

const int Board::getSIZEX()
{
	return SIZEXY[X];
}

const int Board::getSIZEY()
{
	return SIZEXY[Y];
}