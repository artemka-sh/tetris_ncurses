#ifndef _MENU
#define _MENU

#include "Main.hpp"
#include "Window.hpp"
#include <ncurses.h>
#include <menu.h>
#include <vector>
#include <string>

class Menu
{
private:
    Window menuWin;
    MENU *menu;
    ITEM **items;
    std::vector<std::string> choices;

public:
    Menu();
    void run();
    void render();
};


#endif //_MENU