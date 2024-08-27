#include "Bricks.hpp"
#include "Ground.hpp"

Brick::Brick(const Vector2 &_position):
position(_position)
{

}

void Brick::fillMask(bool *toFill, std::initializer_list<bool> templat)
{
    auto size = templat.size();
    auto it = templat.begin(); 
    for (unsigned i = 0; i < size; i++) {
        toFill[i] = *(it++); 
    }
}

void Brick::HardMove(Sides side)
{
    switch (side)
        {
        case Sides::Left:
        position.x--;
            break;

        case Sides::Right:
        position.x++;
            break;

        case Sides::Up:
        position.y--;
            break;

        case Sides::Down:
        position.y++;
        // При движении вниз нужно сообщить потоку с тиками, чтобы сбросил таймер
            break;
        default:
            break;
        }
}

bool Brick::moveTo(Sides side, Ground& ground)
{
    Brick tocheck(*this);
    tocheck.HardMove(side);
    if(ground.checkIntersection(&tocheck))
    {   
        if(side == Sides::Down)
        {
            ground.freeze(this);
            return false;
        }
        else
        {
            return true;
        }
        
    }
    else
    {
        HardMove(side);
        return true;
    }

}


bool Brick::rotate(bool clockwise, Ground& ground)
{
    Brick tocheck(*this); 
    tocheck.HardRotate(clockwise);  
    if(ground.checkIntersection(&tocheck))
    {   
        return false;
    }
    else
    {
        HardRotate(clockwise);
        return true;
    }
}

void Brick::HardRotate(bool clockwise) 
{
    for (int layer = 0; layer < maskSide / 2; ++layer) 
    {
        int first = layer;
        int last = maskSide - 1 - layer;
        for (int i = first; i < last; ++i) 
        {
            int offset = i - first;
            int top = mask[first * maskSide + i];

            if (clockwise) {
                // left -> top
                mask[first * maskSide + i] = mask[(last - offset) * maskSide + first];
                // bottom -> left
                mask[(last - offset) * maskSide + first] = mask[last * maskSide + (last - offset)];
                // right -> bottom
                mask[last * maskSide + (last - offset)] = mask[i * maskSide + last];
                // top -> right
                mask[i * maskSide + last] = top;
            } 
            else 
            {
                // также но наоборот 
                mask[first * maskSide + i] = mask[i * maskSide + last];
                mask[i * maskSide + last] = mask[last * maskSide + (last - offset)];
                mask[last * maskSide + (last - offset)] = mask[(last - offset) * maskSide + first];
                mask[(last - offset) * maskSide + first] = top;
            }
        }
    }

    cyclicShift();
}


void Brick::cyclicShift()   
{   
    // shift up 
    while 
    (
        [&]() //(условие) в строчке что-то есть 
        {
            
            for(int i = 0; i < maskSide; i++)
            {
                if(mask[i])
                    return false;
            };
            return true;
        }()
    ) 
    {

        
        for (int i = 0; i < maskSide - 1; ++i){
            for (int j = 0; j < maskSide; ++j){
                mask[i * maskSide + j] = mask[(i + 1) * maskSide + j];
            }
        }
        for (int j = 0; j < maskSide; ++j) {
            mask[(maskSide - 1) * maskSide + j] = 0; // fill 0 in last
        }
    }

    //shift left
    while 
    (
        [&]() //если в столбце что-то есть 
        {
            for(int i = 0; i < maskSide; i++)
            {
                if(mask[maskSide * i])
                    return false;
            };
            return true;
        }()
    ) 
    {
        for (int i = 0; i < maskSide; ++i) {
            for (int j = 0; j < maskSide - 1; ++j) {
                mask[i * maskSide + j] = mask[i * maskSide + j + 1];
            }
            mask[i * maskSide + (maskSide - 1)] = 0; //fill 0 in last
        }
    }
}


void Brick::draw()
{
    for(int y = 0; y < maskSide; y++)
    {
        move(position.y + y, position.x);
        for(int x = 0; x < maskSide; x++)
            if(mask[y * maskSide + x]) 
                addch(skin);  
            else 
                move(getcury(stdscr), getcurx(stdscr) + 1);      
    }
}

void Brick::wdraw(Window &win)
{
    for(int y = 0; y < maskSide; y++)
    {
        for(int x = 0; x < maskSide; x++)
        {
            if(mask[y * maskSide + x])  
                win.print(skin, position.y + y, position.x + x);
        }     
    }
}