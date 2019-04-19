#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <iostream>

using namespace std;

class Tetromino
{
public:
    Tetromino();
    virtual ~Tetromino();
    virtual void rotate(const int rot)=0;

    int getRot();
    int getRotNum();
    array<array<int, 4>, 4> getPiece();
    const int getSIZEXY();

protected:
    void clear();
    int rot,    // Rotation state of the tetormino
        rotnum; // Max number of rotations of the tetromino
    array<array<int, 4>, 4> piece = {};
    const int SIZEXY = 4;
};

class I: public Tetromino
{
public:
    void rotate(const int rotation);
    I();
    ~I();
};

class J: public Tetromino
{
public:
    void rotate(const int rot);
    J();
    ~J();
};

class L :public Tetromino
{
public:
    void rotate(const int rot);
    L();
    ~L();
};

class O :public Tetromino
{
public:
    void rotate(const int rot);
    O();
    ~O();
};

class S :public Tetromino
{
public:
    void rotate(const int rot);
    S();
    ~S();
};

class T :public Tetromino
{
public:
    void rotate(const int rot);
    T();
    ~T();
};

class Z :public Tetromino
{
public:
    void rotate(const int rot);
    Z();
    ~Z();
};

#endif
