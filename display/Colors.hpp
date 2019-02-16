#pragma once
#include <ncurses.h>

struct Colors {

    static short current_pair;
    static const short WHITE_BLACK = 1;
    static const short BLACK_WHITE = 2;
    static const short YELLOW_BLACK = 3;

    static void init() {
        start_color();
        init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
        init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
        init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
    }

    static void color_on(short pair_code) {
        attron(COLOR_PAIR(pair_code));
        current_pair = pair_code;
    }

    static void color_on(WINDOW* w, short pair_code) {
        wattron(w, COLOR_PAIR(pair_code));
        current_pair = pair_code;
    }

    static void color_off() {
        attroff(COLOR_PAIR(current_pair));
        current_pair = 0;
    }

    static void color_off(WINDOW* w) {
        wattroff(w, COLOR_PAIR(current_pair));
        current_pair = 0;
    }
};


