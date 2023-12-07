#pragma once
#include <ncurses.h>


class Board 
{
    public:
        void initialize();
        void welcome_screen() const;
        void game_over_screen() const;
        // void game_won_screen() const;
    private:
        WINDOW* win_;
};
