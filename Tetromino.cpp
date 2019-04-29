#include "Tetromino.h"
#include "Constants.h"

Tetromino::Tetromino()
{
    this->setX(STARTINGX);
    this->setY(STARTINGY);
}

Tetromino::~Tetromino() {};

//rotates this shape 90 degrees counter-clockwise
void Tetromino::rotate()
{
    //I pulled this from https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
    //no idea how it works
    for (int i = 0; i < SIZEXY/2; i++)
    { 
        for (int j = i; j < SIZEXY-i-1; j++)
        { 
            int temp = shape[i][j];

            shape[i][j] = shape[SIZEXY-1-j][i];
            shape[SIZEXY-1-j][i] = shape[SIZEXY-1-i][SIZEXY-1-j];
            shape[SIZEXY-1-i][SIZEXY-1-j] = shape[j][SIZEXY-1-i];
            shape[j][SIZEXY-1-i] = temp;
        } 
    } 
}

//moves this shape one square to the left
void Tetromino::shiftLeft()
{
    this->position[0]--;
}

//moves this shape one square to the right
void Tetromino::shiftRight()
{
    this->position[0]++;
}

//moves this shape one square down
void Tetromino::shiftDown()
{
    this->position[1]++;
}

/*
The getBounds functions find the positions where the actual tetris piece begins in its array.

I.E. the following shape:

0 0 0 0
0 1 0 0
0 1 0 0
0 1 0 0

would have a 1 for boundsTop, 1 for boundsLeft, 2 for boundsRight, and 0 for boundsBottom.
*/

int Tetromino::getBoundsTop()
{
    for (int i = 0; i < SIZEXY; i++) //scan from the top row down
    {
        for (int j = 0; j < SIZEXY; j++) //scan from left-to-right on each row
        {
            //we hit the top of the tetris piece- return the row
            if (shape[i][j] > 0)
                return i;
        }
    }
    return SIZEXY-1;
}

int Tetromino::getBoundsBottom()
{
    for (int i = SIZEXY-1; i > 0; i--) //scan from the bottom row up
    {
        for (int j = 0; j < SIZEXY; j++) //scan from left-to-right on each row
        {
            //we hit the bottom of the tetris piece- return the row
            if (shape[i][j] > 0)
                return SIZEXY-1-i; //subtract i from SIZEXY-1 to get it from bottom instead of top
        }
    }

    return 0;
}

int Tetromino::getBoundsLeft()
{
    for (int i = 0; i < SIZEXY; i++) //scan from left column to right
    {
        for (int j = 0; j < SIZEXY; j++) //scan from top-to-bottom on each column
        {
            //we hit the left of the tetris piece; return the column
            if (shape[j][i] > 0)
                return i;
        }
    }

    return SIZEXY-1;
}

int Tetromino::getBoundsRight()
{
    for (int i = SIZEXY-1; i > 0; i--) //scan from right column to left
    {
        for (int j = 0; j < SIZEXY; j++) //scan from top-to-bottom on each column
        {
            //we hit the right of the tetris piece; return the column
            if (shape[j][i] > 0)
                return SIZEXY-1-i; //subtract i from SIZEXY-1 to get it from right instead of left
        }
    }

    return 0;
}

//SIZEXY represents the side length of the actual tetris piece array (always 4 in our case)
int Tetromino::getSIZEXY()
{
    return SIZEXY;
}

int Tetromino::getX()
{
    return this->position[X];
}

int Tetromino::getY()
{
    return this->position[Y];
}

void Tetromino::setX(int x)
{
    this->position[X] = x;
}

void Tetromino::setY(int y)
{
    this->position[Y] = y;
}

void Tetromino::setPos(int x, int y)
{
    this->position[X] = x;
    this->position[Y] = y;
}

//returns a 2D std::array of this tetris piece's shape
std::array<std::array<int, 4>, 4> Tetromino::getShape()
{
    return shape;
}

/*
0 - empty
1 - red
2 - orange
3 - yellow
4 - green
5 - light blue
6 - blue
7 - purple
*/

IBlock::IBlock()
{
    this->shape = {{
        {0, 0, 5, 0},
        {0, 0, 5, 0},
        {0, 0, 5, 0},
        {0, 0, 5, 0}
    }};
}

IBlock::~IBlock() {};

JBlock::JBlock()
{
    this->shape = {{
        {0, 0, 6, 0},
        {0, 0, 6, 0},
        {0, 6, 6, 0},
        {0, 0, 0, 0}
    }};
}

JBlock::~JBlock() {};

LBlock::LBlock()
{
    this->shape = {{
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0}
    }};
}

LBlock::~LBlock() {};

OBlock::OBlock()
{
    this->shape = {{
        {0, 0, 0, 0},
        {0, 3, 3, 0},
        {0, 3, 3, 0},
        {0, 0, 0, 0}
    }};
}

OBlock::~OBlock() {};

SBlock::SBlock()
{
    this->shape = {{
        {0, 0, 0, 0},
        {0, 0, 4, 4},
        {0, 4, 4, 0},
        {0, 0, 0, 0}
    }};
}

SBlock::~SBlock() {};

ZBlock::ZBlock()
{
    this->shape = {{
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0}
    }};
}

ZBlock::~ZBlock() {};

TBlock::TBlock()
{
    this->shape = {{
        {0, 0, 7, 0},
        {0, 7, 7, 0},
        {0, 0, 7, 0},
        {0, 0, 0, 0}
    }};
}

TBlock::~TBlock() {};