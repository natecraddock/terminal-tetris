#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

#include "game.h"

/**
 * Color defines
 */

#define COLOR_PIECE_O 1
#define COLOR_PIECE_I 2
#define COLOR_PIECE_T 3
#define COLOR_PIECE_L 4
#define COLOR_PIECE_J 5
#define COLOR_PIECE_S 6
#define COLOR_PIECE_Z 7

/**
 * Initializes curses
 */
void init_screen();

/**
 * Cleanup curses and return terminal to normal state
 */
void cleanup_screen();

/**
 * Places the current screen dimensions in the arguments y and x.
 */
void get_screen_size(int *y, int *x);

/**
 * Check if screen size is large enough to display the game area.
 */
bool check_screen_size();

void erase_screen();

void update_screen();

void draw_game(Game *game);
void draw_menu();

#if DEBUG_LINE
void draw_debug_line(const char *event);
#endif

#endif
