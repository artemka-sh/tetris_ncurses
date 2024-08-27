#ifndef __Bricks
#define __Bricks

//#pragma warning (disable : ) 

#include <ncurses.h>
#include <vector>
#include "Utilits.hpp"
#include "Ground.hpp"
#include "Window.hpp"

class Ground;
class Brick
{
protected:
    Vector2 position;
    std::vector<bool> mask;
    int maskSide = 4;
    char skin = 0;
public:
    Brick(const Vector2 &_position);
    void fillMask(bool *toFill, std::initializer_list<bool> templat);
    friend class Ground;
    bool moveTo(Sides side, Ground& ground);
    void HardMove(Sides side);
    bool rotate(bool clockwise, Ground& ground);
    void HardRotate(bool clockwise);
    void cyclicShift();
    void draw();
    void wdraw(Window &win);
};



class LBrick: public Brick
{
public:
    LBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = '#';
        mask = {1, 0, 0, 0,
                1, 0, 0, 0,
                1, 1, 0, 0,
                0, 0, 0, 0};
        
    }
};


class IBrick: public Brick
{
public:
    IBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = '@';
        mask = {1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0,
                1, 0, 0, 0};
    }
};


class TBrick: public Brick
{
public:
    TBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = 'W';
        mask = {0, 1, 0, 0,
                1, 1, 1, 0,
                0, 0, 0, 0,
                0, 0, 0, 0};
    }
};

#endif