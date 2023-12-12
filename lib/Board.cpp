#include "Board.h"
#include <memory>

constexpr int snakey = 21;
constexpr int snakex = 78;

void
Board::initialize()
{
    initscr();
    cbreak();
    noecho();

    win_ = newwin(snakey, snakex, 0, 0);
    refresh();

    box(win_, 0, 0);
    wrefresh(win_);

    welcome_screen();

    getch();

    game_over_screen();
    getch();
    endwin();
}

void
Board::welcome_screen() const
{
    mvwprintw(win_, snakey/2, 1, "Press Anything to start...");
    wrefresh(win_);
}

void
Board::game_over_screen() const
{
    mvwprintw(win_, snakey/2, 1, "/n GAME OVER!!! /n");
    wrefresh(win_);

}

int main()
{
    Board bb;
    bb.initialize();
}
