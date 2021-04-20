#include <stdio.h>
#include <unistd.h>

#include "screen.h"

int main() {
    init_curses();

    int y, x;
    get_screen_size(&y, &x);

    //min 26 rows
    //min 58 cols

    if ((y < 26) || (x < 58)) {
        cleanup_curses();
        fprintf(stderr, "Your terminal size is too small, please resize it and re-run the program.\n");
        return 1;
    }

    sleep(2);
    draw();
    sleep(2);
    cleanup_curses();
    return 0;
}
