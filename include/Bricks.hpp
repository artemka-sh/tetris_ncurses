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
    int maskSide = 0;
    char skin = 0;
public:
    Brick(const Vector2 &_position);
    void fillMask(bool *toFill, std::initializer_list<bool> templat);
    friend class Ground;
    bool moveTo(Sides side, Ground& ground);
    void HardMove(Sides side);
    bool rotate(bool clockwise, Ground& ground);
    virtual void HardRotate(bool clockwise);
    void cyclicShift();
    void draw();
    void wdraw(Window &win);
    virtual ~Brick() {} 
};



class LBrick: public Brick
{
public:
    LBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = '#';
        maskSide = 3;
        mask = {1, 0, 0,
                1, 0, 0,
                1, 1, 0};
        
    }
};


class IBrick: public Brick
{
public:
    IBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = '@';
        maskSide = 4;
        mask = {0, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0,
                0, 1, 0, 0};
    }
    bool rotationState = 0;
    void HardRotate(bool clockwise) override;
};


class TBrick: public Brick
{
public:
    TBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = 'W';
        maskSide = 3;
        mask = {0, 1, 0,
                1, 1, 1,
                0, 0, 0};
    }
};

class JBrick: public Brick
{
public:
    JBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = '#';
        maskSide = 3;
        mask = {0, 1, 0,
                0, 1, 0,
                1, 1, 0};
        
    }
};

class CBrick: public Brick
{
public:
    CBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = 'M';
        maskSide = 2;
        mask = {1, 1, 
                1, 1};
        
    }
    void HardRotate(bool clockwise) override;
};

class ZBrick: public Brick
{
public:
    ZBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = 'Z';
        maskSide = 3;
        mask = {1, 1, 0,
                0, 1, 1,
                0, 0, 0};
        
    }
};

class SBrick: public Brick
{
public:
    SBrick(const Vector2 &_position): Brick(_position) 
    {
        skin = 'Z';
        maskSide = 3;
        mask = {0, 1, 1,
                1, 1, 0,
                0, 0, 0};
        
    }
};

#endif