#include <stdbool.h>

#include <ncurses.h>

#include "screen.h"

//min 26 rows
//min 58 cols

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

void draw() {
    
    int y, x;

    get_screen_size(&y, &x);

    for (int i = 2; i < x - 2; i++) {
        mvwaddch(stdscr, y, i, '-');
    }

    refresh();
}
