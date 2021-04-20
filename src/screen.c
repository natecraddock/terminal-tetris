#include <stdbool.h>

#include <ncurses.h>

#include "screen.h"

void init_curses() {
    initscr();
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);
}

void cleanup_curses() {
    // Make everything work again :)
    nocbreak();
    echo();
    nl();
    keypad(stdscr, false);
    endwin();
}

void get_screen_size(int *y, int *x) {
    // getmaxyx is a macro so it automatically adds the & before
    // y and x, so dereference is necessary here.
    getmaxyx(stdscr, *y, *x);
}

void draw() {}
