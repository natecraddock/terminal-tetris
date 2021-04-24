#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "screen.h"

int main() {
    srand(time(NULL));

    init_screen();

    int y, x;
    get_screen_size(&y, &x);

    if (!check_screen_size()) {
        cleanup_screen();
        fprintf(stderr, "Your terminal size is too small, please resize it and re-run the program.\n");
        return 1;
    }

    start_game();

    cleanup_screen();
    return 0;
}
