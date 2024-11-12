#include "Menu.hpp"
#include "Main.hpp"
#include "Utilits.hpp"
#include <vector>
#include <string>
#include <thread>


using namespace std::chrono_literals;

int main()
{  
    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    Menu menu;
    menu.run();

    endwin();
    return 0;
    
}
