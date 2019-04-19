#include "Tetromino.h"
#include "Constants.h"

Tetromino::Tetromino() {};

Tetromino::~Tetromino() {};

void Tetromino::clear()
{
    for (int i = 0; i < SIZEXY; i++)
    {
        for (int j = 0; j < SIZEXY; j++)
        {
            piece[i][j] = EMPTY;
        }
    }
}

int Tetromino::getRot()
{
    return rot;
}

int Tetromino::getRotNum()
{
    return rotnum;
}

array<array<int, 4>, 4> Tetromino::getPiece()
{
    return piece;
}

const int Tetromino::getSIZEXY()
{
    return SIZEXY;
}

void I::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        for (int i = 0; i < SIZEXY; i++)
        {
            for (int j = 0; j < SIZEXY; j++)
            {
                if (j == 0)
                    piece[i][j] = colors::LIGHTBLUE;
                else
                    piece[i][j] = 0;
            }
        }
        rot = 1;
        break;
    case 2:
        for (int i = 0; i < SIZEXY; i++)
        {
            for (int j = 0; j < SIZEXY; j++)
            {
                if (i == 0)
                    piece[i][j] = colors::LIGHTBLUE;
                else
                    piece[i][j] = 0;
            }
        }
        rot = 2;
        break;
    default:
        break;
    }
}

I::I()
{
    rotate(1);
    rotnum = 2;
}

I::~I() {};

void J::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        clear();
        piece[2][0] = colors::BLUE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[i][1] = colors::BLUE;
        }
        rot = 1;
        break;
    case 2:
        clear();
        piece[0][0] = colors::BLUE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[1][i] = colors::BLUE;
        }
        rot = 2;
        break;
    case 3:
        clear();
        piece[0][1] = colors::BLUE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[i][0] = colors::BLUE;
        }
        rot = 3;
        break;
    case 4:
        clear();
        piece[1][2] = colors::BLUE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[0][i] = colors::BLUE;
        }
        rot = 4;
        break;
    default:
        break;
    }
}

J::J()
{
    rotate(1);
    rotnum = 4;
}

J::~J() {};

void L::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        clear();
        piece[2][1] = colors::ORANGE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[i][0] = colors::ORANGE;
        }
        rot = 1;
        break;
    case 2:
        clear();
        piece[1][0] = colors::ORANGE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[0][i] = colors::ORANGE;
        }
        rot = 2;
        break;
    case 3:
        clear();
        piece[0][0] = colors::ORANGE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[i][1] = colors::ORANGE;
        }
        rot = 3;
        break;
    case 4:
        clear();
        piece[0][2] = colors::ORANGE;

        for (int i = 0; i <SIZEXY - 1; i++)
        {
            piece[1][i] = colors::ORANGE;
        }
        rot = 4;
        break;
    default:
        break;
    }
}

L::L()
{
    rotate(1);
    rotnum = 4;
}

L::~L() {};

void O::rotate(int rotation)
{
    if (rotation == 1)
    {
        clear();
        piece[0][0] = colors::YELLOW;
        piece[1][0] = colors::YELLOW;
        piece[0][1] = colors::YELLOW;
        piece[1][1] = colors::YELLOW;
    }
}

O::O()
{
    rotate(1);
    rotnum = 1;
}

O::~O() {};

void S::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        clear();
        piece[1][0] = colors::GREEN;
        piece[0][1] = colors::GREEN;
        piece[1][1] = colors::GREEN;
        piece[0][2] = colors::GREEN;
        rot = 1;
        break;
    case 2:
        clear();
        piece[0][0] = colors::GREEN;
        piece[1][0] = colors::GREEN;
        piece[1][1] = colors::GREEN;
        piece[2][1] = colors::GREEN;
        rot = 2;
        break;
    default:
        break;
    }
}

S::S()
{
    rotate(1);
    rotnum = 2;
}

S::~S() {};

void T::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        clear();
        piece[0][1] = colors::VIOLET;

        for (int i = 0; i < SIZEXY - 1; i++)
        {
            piece[1][i] = colors::VIOLET;
        }
        rot = 1;
        break;
    case 2:
        clear();
        piece[1][1] = colors::VIOLET;

        for (int i = 0; i < SIZEXY - 1; i++)
        {
            piece[i][0] = colors::VIOLET;
        }
        rot = 2;
        break;
    case 3:
        clear();
        piece[1][1] = colors::VIOLET;

        for (int i = 0; i < SIZEXY - 1; i++)
        {
            piece[0][i] = colors::VIOLET;
        }
        rot = 3;
        break;
    case 4:
        clear();
        piece[1][0] = colors::VIOLET;

        for (int i = 0; i < SIZEXY - 1; i++)
        {
            piece[i][1] = colors::VIOLET;
        }
        rot = 4;
        break;

    default:
        break;
    }
}

T::T()
{
    rotate(1);
    rotnum = 4;
}

T::~T() {};

void Z::rotate(int rotation)
{
    switch (rotation)
    {
    case 1:
        clear();
        piece[0][0] = colors::RED;
        piece[0][1] = colors::RED;
        piece[1][1] = colors::RED;
        piece[1][2] = colors::RED;
        rot = 1;
        break;
    case 2:
        clear();
        piece[0][1] = colors::RED;
        piece[1][1] = colors::RED;
        piece[1][0] = colors::RED;
        piece[2][0] = colors::RED;
        rot = 2;
        break;
    default:
        break;
    }
}

Z::Z()
{
    rotate(1);
    rotnum = 2;
}

Z::~Z() {};
