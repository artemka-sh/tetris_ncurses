#include "Main.hpp"

int main()
{
    initscr();
    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));
    Main game;
    return 0;
}