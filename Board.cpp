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

//checks if the tetromino is colliding with settled tetrominos on the board at x, y
bool Board::checkCollision(Tetromino & tetromino, int x, int y)
{
	int tetX = tetromino.getX();
	int tetY = tetromino.getY();
	int size = tetromino.getSIZEXY();

	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if (tetY+j > SIZEXY[Y]-1)
				return true;

			if (tetromino.getShape()[i][j] != EMPTY)
			{
				if (settledPieces[tetX + i + 1][tetY + j + 1] != EMPTY)
					return true;
			}
		}
	}

	/*
	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if ((tetromino.getY()+i) > (SIZEXY[Y]-2) && tetromino.getShape()[i][j] != EMPTY)
				return true;

			if (i == tetromino.getSIZEXY()-1)
			{
				if (tetromino.getShape()[i][j] != EMPTY && settledPieces[i + tetromino.getY() + 1][j + tetromino.getX()] != EMPTY)
					return true;
			}
			else
			{ 
				if (tetromino.getShape()[i][j] != EMPTY && tetromino.getShape()[i+1][j] == EMPTY && settledPieces[i + tetromino.getY() + 1][j + tetromino.getX()] != EMPTY)
					return true;
			}
		}
	}
	*/

	return false;
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

	//make sure the new space isn't occupied by any settled tetrominoes
	if (checkCollision(tetromino, x+xOff, y+yOff))
	{
		return false;
	}

	//check and see if any of the tetromino's squares overlap with any squares on the board
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (tetromino.getShape()[i][j] != EMPTY && settledPieces[i+y+yOff][j+x+xOff] != EMPTY)
			{
				return false;
			}
		}
	}

	return true;

/*
	if (x < 0 || x > (SIZEXY[X]-1) || y > (SIZEXY[Y]-1))
		return false;

	for (int i = 0; i < tetromino.getSIZEXY(); i++)
	{
		for (int j = 0; j < tetromino.getSIZEXY(); j++)
		{
			if ((j+x) > (SIZEXY[X] - 1) && tetromino.getShape()[i][j] != EMPTY)	
				return false;
			if ((i+y) > (SIZEXY[Y] - 1) && tetromino.getShape()[i][j] != EMPTY)
				return false;
			if (tetromino.getShape()[i][j] != EMPTY && settledPieces[i + y][j + x] != EMPTY)
				return false;
		}
	}

	return true;
	*/
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