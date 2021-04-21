#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "screen.h"

int main() {
    init_curses();

    int y, x;
    get_screen_size(&y, &x);

    if (!check_screen_size()) {
        cleanup_curses();
        fprintf(stderr, "Your terminal size is too small, please resize it and re-run the program.\n");
        return 1;
    }

    draw();

    sleep(2);

    cleanup_curses();
    return 0;
}
