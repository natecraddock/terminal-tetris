#include <locale.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

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

#define PADDING 2
#define GAME_AREA_WIDTH 20
#define GAME_AREA_HEIGHT 20
#define HOLD_AREA_WIDTH 12
#define HOLD_AREA_HEIGHT 4
#define QUEUE_AREA_WIDTH 12
#define QUEUE_AREA_HEIGHT 16
#define SCORE_AREA_WIDTH 12
#define SCORE_AREA_HEIGHT 3

#define BORDER(x) (x + 2)

#define MIN_HEIGHT (PADDING + BORDER(GAME_AREA_HEIGHT) + PADDING)
#define MIN_WIDTH (PADDING + BORDER(HOLD_AREA_WIDTH) + PADDING + BORDER(GAME_AREA_WIDTH) + PADDING + BORDER(QUEUE_AREA_WIDTH) + PADDING)

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

/**
  * Same as draw_box, but adds a box label on the top border
  */
static void draw_labeled_box(int y, int x, int h, int w, const char *label) {
    draw_box(y, x, h, w);

    int str_offset = (w + 2 - strlen(label)) / 2;

    mvwaddstr(stdscr, y - 1, x - 1 + str_offset, label);
}

void init_curses() {
    // Required for unicode
    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    nodelay(stdscr, true);
    noecho();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);

    curs_set(0);
}

void cleanup_curses() {
    // Make everything work again :)
    nocbreak();
    nodelay(stdscr, false);
    echo();
    nl();
    keypad(stdscr, false);
    endwin();
}

bool check_screen_size() {
    int y, x;
    get_screen_size(&y, &x);
    return (y > MIN_HEIGHT) && (x > MIN_WIDTH);
}

void get_screen_size(int *height, int *width) {
    // getmaxyx is a macro so it automatically adds the & before
    // height and width, so dereference is necessary here.
    getmaxyx(stdscr, *height, *width);
}

void draw(const char *debug) {
    int height, width;
    get_screen_size(&height, &width);

    int origin_y = (height / 2) - (MIN_HEIGHT / 2);
    int origin_x = (width / 2) - (MIN_WIDTH / 2);

    // draw_box(origin_y, origin_x, MIN_HEIGHT, MIN_WIDTH);
    erase();
    origin_x += 1;

    // Hold box
    draw_labeled_box(origin_y + PADDING, origin_x + PADDING, HOLD_AREA_HEIGHT, HOLD_AREA_WIDTH, "HOLD");

    // Score box
    draw_labeled_box(origin_y + PADDING + BORDER(HOLD_AREA_HEIGHT) + PADDING,
             origin_x + PADDING, SCORE_AREA_HEIGHT, SCORE_AREA_WIDTH, "POINTS");

    origin_x += PADDING + BORDER(HOLD_AREA_WIDTH);

    // Game area
    draw_box(origin_y + PADDING, origin_x + PADDING, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
    origin_x += PADDING + BORDER(GAME_AREA_WIDTH);

    // Queue area
    draw_labeled_box(origin_y + PADDING, origin_x + PADDING, QUEUE_AREA_HEIGHT, QUEUE_AREA_WIDTH, "NEXT");

#if DEBUG_LINE
    // Draw debug info
    mvwaddstr(stdscr, 0, 0, debug);
#endif

    refresh();
}

static void draw_title(int y, int w) {
    const int longest_line = 52;
    const int offset = (w - longest_line) / 2;

    mvwaddstr(stdscr, y + 1, offset, "  _|                  _|                _|");
    mvwaddstr(stdscr, y + 2, offset, "_|_|_|_|    _|_|    _|_|_|_|  _|  _|_|        _|_|_|");
    mvwaddstr(stdscr, y + 3, offset, "  _|      _|_|_|_|    _|      _|_|      _|  _|_|");
    mvwaddstr(stdscr, y + 4, offset, "  _|      _|          _|      _|        _|      _|_|");
    mvwaddstr(stdscr, y + 5, offset, "    _|_|    _|_|_|      _|_|  _|        _|  _|_|_|");
}

void draw_menu() {
    int height, width;
    get_screen_size(&height, &width);

    int origin_y = (height / 2) - (MIN_HEIGHT / 2);

    clear();
    draw_title(origin_y, width);

    refresh();
}
