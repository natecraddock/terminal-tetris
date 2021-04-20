#include <stdio.h>
#include <unistd.h>

#include "screen.h"

int main() {
    init_curses();

    int y, x;
    get_screen_size(&y, &x);

    printf("y: %d x: %d\n", y, x);

    sleep(2);
    cleanup_curses();
    return 0;
}
