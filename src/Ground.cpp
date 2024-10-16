#include "Ground.hpp"

Ground::Ground(Vector2 _size): size(_size)
{
    massive.resize(size.x * size.y, '.');
    
}

int Ground::getLines()
{
    return lines;
}


bool Ground::checkIntersection(const Brick* brick)
{
    (void)brick;
    for(int i = 0; i < brick->maskSide; i++)
        for(int j = 0; j < brick->maskSide; j++)
        {
            const bool brickvalue = brick->mask[i * brick->maskSide + j];   
            const bool groundvalue = ('.' != massive[(brick->position.y + i) * size.x 
                                     + brick->position.x + j]);
            
            if(
                (brickvalue == true and (brick->position.y + i) >= size.y)     // isOutOfBounds 
                    or
                ((brick->position.x + j) >= (size.x) and brickvalue)        // isBeyondRight 
                    or
                ((brick->position.x + j) < (0) and brickvalue)              // isBeyondLeft
                    or
                (brickvalue == true and groundvalue == true)                                // isIntersecting
            )
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
            const char symbol = massive[y * size.x + x];
            win.print(symbol, y, x);
        }
    }
}


void Ground::freeze(Brick* brick)
{
    for(int i = 0; i < brick->maskSide; i++)
        for(int j = 0; j < brick->maskSide; j++)
            if(brick->mask[i * brick->maskSide + j] == 1)
                massive[(brick->position.y + i) * size.x + (brick->position.x + j)] = brick->skin;
                
    lines += clean();
}

ushort Ground::clean()
{
    ushort lines = 0;
    for(int i = 0; i < size.y; i++)
        if(
            [&](){
                for(int j = 0; j < size.x; j++)
                {
                    if(massive[i * size.x + j] == '.')
                        return 0;
                }
                return 1;
            }()
        )
        {
            lines++;
            massive.erase(massive.begin() + size.x * i, massive.begin() + size.x * (i+1));
            massive.insert(massive.begin(), size.x, '.');
        }
    return lines;
}

bool Ground::checkGameOver()
{
    for(int i = 0; i < size.x; i++)
    {
        if(massive[i] != '.')
        {
            return 1;
        } 
    }
    return 0;
}