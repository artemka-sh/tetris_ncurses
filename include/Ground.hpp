#ifndef __Ground
#define __Ground


#include <ncurses.h>
#include <vector>
#include "Utilits.hpp"
#include "Bricks.hpp"


class Brick;
class Ground
{
public:
    Vector2 position;
    Vector2 size;
    std::vector<char> massive;
public:
    Ground(Vector2 _size);
    void setPosition(Vector2 _position);
    friend class Brick;
    bool checkIntersection(const Brick* brick);
    void draw();
    void freeze(Brick *brick);
    ushort clean();
    

};

#endif