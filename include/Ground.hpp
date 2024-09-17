#ifndef __Ground
#define __Ground

#include <ncurses.h>
#include <vector>

#include "Utilits.hpp"
#include "Bricks.hpp"
#include "Window.hpp"

class Brick;
class Ground
{
public:
    Vector2 size;
    std::vector<char> massive;
    int lines = 0;
public:
    Ground(Vector2 _size);
    int getLines();
    friend class Brick;
    bool checkIntersection(const Brick* brick);
    void freeze(Brick *brick);
    ushort clean();
    void wdraw(Window &win);
    bool checkGameOver();
};

#endif