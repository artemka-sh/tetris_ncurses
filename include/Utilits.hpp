#ifndef __Utilits
#define __Utilits

#include <iostream>

#define SQU(x) ((x) * (x))
#define LOG(x) (std::cerr << x << std::endl)

struct Vector2
{
    Vector2(const int &x = 0, const int &y = 0): x(x), y(y) {}
    Vector2(const Vector2 &other):x(other.x), y(other.y) {}
    void operator()(const Vector2 &tocopy){x = tocopy.x; y = tocopy.y;}
    void operator()(const int &x = 0, const int &y = 0){this->x = x, this->y = y;}
    void operator=(const Vector2 &other){this->x = other.x, this->y = other.y;};
    Vector2 operator/(int number){return Vector2(this->x / number, this->y /= number);}
    int x;
    int y;
};

enum Sides{
    Left = 0,
    Right = 1,
    Up = 2,
    Down = 3
};

#endif // __Utilits