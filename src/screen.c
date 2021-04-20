#include <locale.h>
#include <stdbool.h>
#include <unistd.h>

#include <ncurses.h>

#include "screen.h"

//min 26 rows
//min 58 cols

#define LINE_H "\u2500"
#define LINE_V "\u2502"
#define CORNER_NW "\u256D"
#define CORNER_NE "\u256E"
#define CORNER_SE "\u256F"
#define CORNER_SW "\u2570"

/**
 * Given a top left y, x coordinate, and a height and width
 * draw a border around that box.
 * If a 5x5 box is desired, the borders will be drawn as a 7x7 box.
 */
static void draw_box(int y, int x, int h, int w) {
    y -= 1;
    x -= 1;
    h += 1;
    w += 1;

    // Corners
    mvwaddstr(stdscr, y, x, CORNER_NW);
    mvwaddstr(stdscr, y, x + w, CORNER_NE);
    mvwaddstr(stdscr, y + h, x + w, CORNER_SE);
    mvwaddstr(stdscr, y + h, x, CORNER_SW);

    // Top and Bottom Borders
    for (int i = x + 1; i < x + w; i++) {
        mvwaddstr(stdscr, y, i, LINE_H);
        mvwaddstr(stdscr, y + h, i, LINE_H);
    }

    // Left and Right Borders
    for (int i = y + 1; i < y + h; i++) {
        mvwaddstr(stdscr, i, x, LINE_V);
        mvwaddstr(stdscr, i, x + w, LINE_V);
    }
}

void init_curses() {
    // Required for unicode
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    curs_set(0);
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

    draw_box(2, 2, y - 4, x - 4);
    draw_box(20, 10, 20, 20);

    refresh();
}
