#include "Main.hpp"
#include "Utilits.hpp"
#include <vector>
#include <string>

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));

    Main game;
    return 0;
    
}
