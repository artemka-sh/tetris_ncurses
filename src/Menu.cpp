#include "Menu.hpp"

Menu::Menu(): menuWin( 10, 40, 4, 4)
{
   choices = {          "Play!",
                        "Settings",
                        "Exit",
                                            };

    items = new ITEM*[choices.size() + 1 ];


    for(uint i = 0; i < choices.size(); ++i)
            items[i] = new_item(choices[i].c_str(), 0);
    items[choices.size()] = (ITEM *)NULL;

	menu = new_menu((ITEM **)items);


    set_menu_win(menu, menuWin.window);
    set_menu_sub(menu, derwin(menuWin.window, 6, 38, 3, 1));
    set_menu_format(menu, choices.size(), 1);
    set_menu_mark(menu, " * ");
    box(menuWin.window, 0, 0);
    menuWin.setPositionCentered();
    menu_driver(menu, REQ_FIRST_ITEM);


    render();
}




void Menu::render() {
    post_menu(menu);
    menuWin.draw();
    menuWin.refresh();
    refresh();
}


void Menu::run() 
{
    render();
    char input;
    while((input = getch()) != '`')
    {
        
        if(input == 's')
            menu_driver(menu, REQ_DOWN_ITEM);
        if(input == 'w')
            menu_driver(menu, REQ_UP_ITEM);
        if(input == ' ')
        {
            clear();
            Main game;
            game.run();
        }
            
        render();
    }	

}