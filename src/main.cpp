#include "Main.hpp"

int main()
{
    initscr();

    // colors 

    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    //     wattron(win.window, COLOR_PAIR(1)); // Включаем цветовую пару
    // wattroff(win.window, COLOR_PAIR(1)); // Выключаем цветовую пару     // передавать в print параметр цвета (enum) если такой же то не отключать watrron + если параметра нет, отключить 
                                                                            // *доп перегруженная функция
    Main game;
    return 0;
}
