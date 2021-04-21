#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "events.h"
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

    draw_menu();

    sleep(2);
    while (1) {
        Event e = get_event();

        const char *test = event_to_string(e);

        draw(test);
        sleep(1);
    }

    cleanup_curses();
    return 0;
}
