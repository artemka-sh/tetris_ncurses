#ifndef _Window
#define _Window

#include <ncurses.h>
#include <string>
#include <Utilits.hpp>

class Window {
private:
    WINDOW *window; 

public:
    Window(int h, int w, int y, int x) {
        window = newwin(h, w, y, x);
    }

    Window() {
        window = newwin(0, 0, 0, 0);
    }

    void draw() {
        box(window, 0, 0);
        wrefresh(window); 
    }

     void setPosition(int y, int x) {
        mvwin(window, y, x); 
        refresh(); 
     }

    void setPositionCentered() {
        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX); 
        int startY = (maxY - window->_maxy) / 2;
        int startX = (maxX - window->_maxx) / 2;  
        setPosition(startY, startX); 
    }

    void getPosition(int &y, int &x) const {
        getbegyx(window, y, x); 
    }

    Vector2 getXYPositions() const {
        int x, y;
        getbegyx(window, y, x); 
        return Vector2(x, y);
    }

    void getSize(int &h, int &w) const {
        getmaxyx(window, h, w); 
    }

    void print(const std::string &text, int y, int x) {
        mvwprintw(window, y, x, "%s", text.c_str());
    }

    void print(const char &ch, int y, int x) {
        mvwprintw(window, y, x, "%c", ch);
    }

    void refresh()
    {
        wrefresh(window); 
    }

    ~Window() {
        delwin(window); 
    }
};


#endif //_Window