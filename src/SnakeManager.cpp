#include "SnakeManager.h"
#include <memory>
#include <iostream>
#include <ctime>
#include <array>

void
SnakeManager::start()
{
    std::srand(static_cast<unsigned>(std::time(0)));
    generate_initial_snake();
    generate_food();

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    win_ = newwin(AXIS_Y, AXIS_X, 0, 0);
    refresh();

    welcome_screen();
    getch();

    nodelay(stdscr, true);
    while(!game_over_ && !game_won_)
    {
        auto ch = getch();
        if((ch == KEY_UP && direction_ != KEY_DOWN)
            ||(ch == KEY_DOWN && direction_ != KEY_UP)
            ||(ch == KEY_LEFT && direction_ != KEY_RIGHT)
            ||(ch == KEY_RIGHT && direction_ != KEY_LEFT))
        {
            direction_ = ch;
        }
        
        snake_move();
        print_gameplay();
        usleep(sdelay_);
    }

    game_won_ ? game_won_screen() : game_over_screen();
    nodelay(stdscr, false);
    getch();
    endwin();
}

void
SnakeManager::win_reset() const
{
    wclear(win_);
    box(win_, 0, 0);
}

void
SnakeManager::welcome_screen() const
{
    win_reset();
    std::array<std::string, 9> welcome = 
    {
        "          /^\\/^\\",
        "         _|__|  O|",
        " /     /~     \\_/ \\",
        " \\____|__________/  \\",
        "        \\_______      \\",
        "                `\\     \\",
        "Welcome to the game of snake",
        "(use the arrows to control the snake)",
        "Press any key to start..."
    };

    int x_offset = (AXIS_X - 22) / 2;
    int y_offset = (AXIS_Y - 9) / 2;

    for (int i = 0; i < welcome.size(); ++i) {
        mvwprintw(win_, y_offset + i, x_offset, "%s", welcome[i].c_str());
    }

    wrefresh(win_);
}

void
SnakeManager::game_over_screen() const
{
    win_reset();
    std::array<std::string, 8> game_over ={
        "____ ____ _  _ ____ ",
        "| __ |__| |\\/| |___ ",
        "|__] |  | |  | |___ ",
        "                    ",
        "____ _  _ ____ ____ ",
        "|  | |  | |___ |__/ ",
        "|__|  \\/  |___ |  \\ "
    };

    int x_offset = (AXIS_X - 20) / 2;
    int y_offset = (AXIS_Y - 7) / 2;
    for (int i = 0; i < game_over.size(); ++i) 
    {
        mvwprintw(win_, y_offset + i, x_offset, "%s", game_over[i].c_str());
    }

    wrefresh(win_);
}

void
SnakeManager::game_won_screen() const
{
    win_reset();
    std::array<std::string, 3> game_won ={
        "_ _ _ _ _  _ _  _ ____ ____   /  /  /",
        "| | | | |\\ | |\\ | |___ |__/  /  /  /",
        "|_|_| | | \\| | \\| |___ |  \\ .  .  ."
    };

    int x_offset = (AXIS_X - 35) / 2;
    int y_offset = (AXIS_Y - 3) / 2;
    for (int i = 0; i < game_won.size(); ++i) 
    {
        mvwprintw(win_, y_offset + i, x_offset, "%s", game_won[i].c_str());
    }

    wrefresh(win_);
}

void
SnakeManager::print_gameplay() const
{
    win_reset();
    mvwprintw(win_, food_.y, food_.x, "F");

    for(const auto& snode : snake_)
    {
        mvwprintw(win_, snode.y, snode.x, "O");
    }

    wrefresh(win_);
}

void
SnakeManager::snake_move()
{
    auto new_head = snake_.back();
    switch(direction_)
    {
        case KEY_RIGHT:
            new_head.x++;
            break;
        case KEY_LEFT:
            new_head.x--;
            break;
        case KEY_UP:
            new_head.y--;
            break;
        case KEY_DOWN:
            new_head.y++;
            break;
    }

    if(new_head == food_)
    {
        if(sdelay_ - SNAKE_DELAY_DECREMENTS >= INIT_SNAKE_DELAY / 2);
        {
            sdelay_-= SNAKE_DELAY_DECREMENTS;
        }

        generate_food();
    }
    else
    {
        check_snake_.erase(snake_.front());
        snake_.pop_front();
    }

    if(check_snake_.contains(new_head) 
            || new_head.x <= 0 || new_head.x >= AXIS_X - 1 
            || new_head.y <= 0 || new_head.y >= AXIS_Y - 1)
    {
        game_over_ = true;
    }

    snake_.push_back(new_head);
    check_snake_.insert(new_head);
    game_won_ = snake_.size() >= MAX_SNAKE_LEN;
}

void
SnakeManager::generate_initial_snake()
{
    Point stail{rand() % (AXIS_X - 1 - INIT_SNAKE_LEN), rand() % (AXIS_Y - 1)};
    for(int i = 0; i < INIT_SNAKE_LEN; ++i)
    {
        snake_.push_back(stail);
        check_snake_.insert(stail);
        ++stail.x;
    }
}

void
SnakeManager::generate_food()
{
    do
    {
        food_.x = 1 + rand() % (AXIS_X - 2);
        food_.y = 1 + rand() % (AXIS_Y - 2);
    }
    while(check_snake_.contains(food_));
}


int main()
{
    SnakeManager bb;
    bb.start();
}
