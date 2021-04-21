/**
 * Initializes curses
 */
void init_curses();

/**
 * Cleanup curses and return terminal to normal state
 */
void cleanup_curses();

/**
 * Places the current screen dimensions in the arguments y and x.
 */
void get_screen_size(int *y, int *x);

/**
 * Check if screen size is large enough to display the game area.
 */
bool check_screen_size();

void draw(const char *debug);
void draw_menu();

