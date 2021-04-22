#include <stdbool.h>

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

void draw(const char *debug);
void draw_menu();

#if DEBUG_LINE
void draw_debug_line(const char *event);
#endif
