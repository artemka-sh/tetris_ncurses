#include "Main.hpp"

int main()
{
    initscr();

    // colors 

    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));
    Main game;
    return 0;
}