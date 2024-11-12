#ifndef _SETTINGS
#define _SETTINGS

#include "Main.hpp"
#include "Window.hpp"
#include <ncurses.h>
#include <menu.h>
#include <vector>
#include <string>

class Settings
{
private:
    Window menuWin;
    MENU *menu;
    ITEM **items;
    std::vector<std::string> choices;

public:
    Settings();
    void run();
    void render();
};


#endif //_SETTINGS