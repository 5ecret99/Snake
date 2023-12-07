#include "SnakeMap.h"
#include <ncurses.h>

void
SnakeMap::welcome_screen()
{

}

int main()
{
    initscr();
    refresh();
    getch();
    endwin();
}
