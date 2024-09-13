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

// double mutex stop or something, when new brick does't happen 
// убрать renderguard и расширить breakguard