#include "Menu.hpp"
#include "Main.hpp"
#include "Utilits.hpp"
#include <vector>
#include <string>
#include <thread>
bool exitst = false;

using namespace std::chrono_literals;

int main()
{
    
    
    srand(time(NULL));
    while(!exitst)
    {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        // Main game;
        // game.run();

        Menu menu;
        menu.run();

        endwin();
        std::this_thread::sleep_for(2000ms);
    }
        
    return 0;
    
}
