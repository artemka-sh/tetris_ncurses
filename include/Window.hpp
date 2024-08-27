#ifndef _Window
#define _Window

#include <ncurses.h>
#include <string>

class Window {
private:
    WINDOW *window; // Указатель на структуру окна

public:
    // Конструктор
    Window(int h, int w, int y, int x) {
        window = newwin(h, w, y, x);
    }

    void draw() {
        box(window, 0, 0); // Рисует границы окна
        wrefresh(window); 
    }

    void getPosition(int &y, int &x) const {
        getbegyx(window, y, x); 
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

// int main() {
//     initscr(); // Инициализация ncurses
//     cbreak();
//     noecho(); // Отключаем отображение вводимых символов

//     Window win(10, 40, 5, 5); // Создаем окно

//     win.print("Press 'q' to exit", 1, 1); // Печатаем текст в окне

//     char a = 0;
//     while (a != 'q') {
//         win.draw(); // Рисуем окно
//         a = getchar(); // Ждем ввода
//     }

//     endwin(); // Завершаем работу с ncurses
//     return 0;
// }


#endif //_Window