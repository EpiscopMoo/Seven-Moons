#pragma once
#include <ncurses.h>
#include "Colors.hpp"

class Display {

public:
    static Display& instance() {
        static Display display;
        return display;
    }

    void init() {
        initscr();
        Colors::init();
        keypad(stdscr, true);
        raw();
        noecho();
        curs_set(0);
    }

    void update() {
        refresh();
    }

    ~Display() {
        endwin();
    }

private:
    Display() = default;
    Display(Display&) = default;
};


