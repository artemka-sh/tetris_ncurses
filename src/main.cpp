#include "Main.hpp"
#include "Utilits.hpp"
#include <vector>
#include <string>

bool exitst = false;

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));
    while(!exitst)
    {
        Main game;
    }
        
    return 0;
    
}
