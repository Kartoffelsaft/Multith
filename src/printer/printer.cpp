#include <curses.h>

#include "./printer.hpp"

Printer::Printer()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
}

Printer::~Printer()
{
    endwin();
}

void Printer::printTest()
{
    clear();
    mvaddch(5, 3, 'l');
    refresh();
}
