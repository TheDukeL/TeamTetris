#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <iostream>

class Tetromino
{
public:
    Tetromino();
    virtual ~Tetromino();
    
    void rotate();
    void shiftLeft();
    void shiftRight();
    void shiftDown();
    int getBoundsTop();
    int getBoundsBottom();
    int getBoundsLeft();
    int getBoundsRight();
    int getSIZEXY();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
    std::array<std::array<int, 4>, 4> getShape();

protected:
    const int SIZEXY = 4; //represents the side length of the actual tetris piece array
    std::array<std::array<int, 4>, 4> shape = {};
    int position[2];
};

class IBlock: public Tetromino
{
public:
    IBlock();
    ~IBlock();
};

class JBlock: public Tetromino
{
public:
    JBlock();
    ~JBlock();
};

class LBlock :public Tetromino
{
public:
    LBlock();
    ~LBlock();
};

class OBlock :public Tetromino
{
public:
    OBlock();
    ~OBlock();
};

class SBlock :public Tetromino
{
public:
    SBlock();
    ~SBlock();
};

class ZBlock :public Tetromino
{
public:
    ZBlock();
    ~ZBlock();
};

class TBlock :public Tetromino
{
public:
    TBlock();
    ~TBlock();
};

#endif