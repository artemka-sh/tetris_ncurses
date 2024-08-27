#include "Ground.hpp"

Ground::Ground(Vector2 _size): size(_size)
{
    massive.resize(_size.x * _size.y, '.');
}


bool Ground::checkIntersection(const Brick* brick)
{
    for(int i = 0; i < brick->maskSide; i++)
        for(int j = 0; j < brick->maskSide; j++)
        {
            const bool brickvalue = brick->mask[i * brick->maskSide + j];   
            const bool groundvalue = ('.' != massive[(brick->position.y + i) * size.y 
                                     + brick->position.x + j]);
            
            if(
                ((brick->position.y + i) == true and (brick->position.y + i) >= size.y)     // isOutOfBounds 
                    or
                ((brick->position.x + j) >= (size.x + brick->maskSide) and brickvalue)        // isBeyondRight 
                    or
                ((brick->position.x + j) < (0) and brickvalue)              // isBeyondLeft
                    or
                (brickvalue == true and groundvalue == true)                                // isIntersecting
            )   //ноль для "красоты", не бейте (предложения по оптимизации принимаются)
            {
                return true; // пересечение засечено
            }
            
        }
    return false;
}

 


void Ground::wdraw(Window &win)
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            const char symbol = massive[y * size.y + x];
            win.print(symbol, y, x);
        }
    }
}


void Ground::freeze(Brick* brick)
{
    for(int i = 0; i < brick->maskSide; i++)
        for(int j = 0; j < brick->maskSide; j++)
            if(brick->mask[i * brick->maskSide + j] == 1)
                massive[(brick->position.y + i)
                * size.y + brick->position.x + j]
                = brick->skin;
    clean();
}

ushort Ground::clean()
{
    ushort lines = 0;
    for(int i = 0; i < size.y; i++)
        if(
            [&](){
                for(int j = 0; j < size.x; j++)
                {
                    if(massive[i * size.y + j] == '.')
                        return 0;
                }
                return 1;
            }()
        )
        {
            lines++;
            massive.erase(massive.begin() + size.y * i, massive.begin() + size.y * (i+1));
            massive.insert(massive.begin(), size.x, '.');
        }
    return lines;
}