#include "Board.h"
#include <list>

using namespace std;

Board::Board() {};
Board::~Board() {};

// Adds a tetris piece to the board of type tetromino at [x, y]
void Board::addPieceToBoard(Tetromino& tetromino, int x, int y)
{		
	for (int i = 0; i < tetromino.getSIZEXY(); i++)
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
			if (tetromino.getPiece()[i][j] != EMPTY)
				settledPieces[i+y][j+x] = tetromino.getPiece()[i][j];
}

//checks for collisions
bool Board::checkCollision(Tetromino & tetromino, int x, int y)
{
	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if ((y+i) > (SIZEXY[Y]-2) && tetromino.getPiece()[i][j] != EMPTY)
				return true;

			if (i == tetromino.getSIZEXY()-1)
			{
				if (tetromino.getPiece()[i][j] != EMPTY && settledPieces[i + y + 1][j + x] != EMPTY)
					return true;
			}
			else
			{ 
				if (tetromino.getPiece()[i][j] != EMPTY && tetromino.getPiece()[i+1][j] == EMPTY && settledPieces[i + y + 1][j + x] != EMPTY)
					return true;
			}
		}
	}

	return false;
}

//check if the movement is allowed
bool Board::movementAllowed(Tetromino & tetromino, int x, int y)
{
	if (x < 0 || x > (SIZEXY[X]-1) || y > (SIZEXY[Y]-1))
		return false;

	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if ((j+x) > (SIZEXY[X] - 1) && tetromino.getPiece()[i][j] != EMPTY)	
				return false;
			if ((i+y) > (SIZEXY[Y] - 1) && tetromino.getPiece()[i][j] != EMPTY)
				return false;
			if (tetromino.getPiece()[i][j] != EMPTY && settledPieces[i + y][j + x] != EMPTY)
				return false;
		}
	}

	return true;
}

//checks lines, cleans them and returns the amount of lines cleaned
int Board::checkAndCleanLines()
{
	list<int> linesToClean;
	bool found = false;

	for (int i = 0; i < SIZEXY[Y]; i++)
	{
		found = true;

		for (int j = 0; j < SIZEXY[X]; j++)
			if (settledPieces[i][j] == EMPTY) { found = false; }

		if (found) { linesToClean.push_back(i); }
	}

	if (linesToClean.empty()) { return EMPTY; }

	for (int line : linesToClean) {
		cleanLine(line);
	}

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

array<array<int, 13>, 23> Board::getSettledPieces()
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

const int Board::getSTARTINGX()
{
	return STARTINGX;
}

const int Board::getSTARTINGY()
{
	return STARTINGY;
}