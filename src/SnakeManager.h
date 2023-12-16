#pragma once
#include <ncurses.h>
#include <list>
#include <unordered_set>

constexpr int AXIS_X = 90;
constexpr int AXIS_Y = 30;
constexpr int MAX_SNAKE_LEN = (AXIS_X - 2) * (AXIS_Y - 2);
constexpr int INIT_SNAKE_LEN = 4;
constexpr int INIT_SNAKE_DELAY = 100000;
constexpr int SNAKE_DELAY_DECREMENTS = 10;

struct Point
{
    int x;
    int y;
    bool operator==(const Point& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    };

    struct Hash 
    {
        size_t operator()(const Point& p) const 
        {
            return (std::hash<int>()(p.x) * 31) ^ (std::hash<int>()(p.y) * 17);
        }
    };
};

class SnakeManager 
{
    public:
        void start();

    private:
        void win_reset() const;
        void welcome_screen() const;
        void game_over_screen() const;
        void print_gameplay() const;
        void game_won_screen() const;
        void generate_initial_snake();
        void generate_food();
        void check_collision();
        void snake_move();

        WINDOW* win_;
        bool game_over_{false};
        bool game_won_{false};
        int direction_{KEY_RIGHT};
        int sdelay_{INIT_SNAKE_DELAY};
        std::list<Point> snake_;
        std::unordered_set<Point, Point::Hash> check_snake_;
        Point food_;
};
