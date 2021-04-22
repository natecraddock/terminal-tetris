#include <curses.h>

#include "events.h"

Event get_event() {
    /**
     * in screen.c input is set to be non-blocking
     */
    int keycode = getch();
    flushinp();

    switch (keycode) {
        case ERR:
            return EVENT_NONE;

        case KEY_UP:
        case 'k':
            return EVENT_ROTATE;

        case KEY_LEFT:
        case 'h':
            return EVENT_LEFT;

        case KEY_RIGHT:
        case 'l':
            return EVENT_RIGHT;

        case KEY_DOWN:
        case 'j':
            return EVENT_DROP_SOFT;

        case ' ':
            return EVENT_DROP_HARD;

        case 'p':
            return EVENT_PAUSE;

        case 'q':
            return EVENT_QUIT;

        case 'b':
            return EVENT_HOLD;

        case '\n':
        case '\r':
        case KEY_ENTER:
            return EVENT_SELECT;
    }

    return EVENT_NONE;
}

const char *event_to_string(Event event) {
    switch (event) {
        case EVENT_NONE:
            return "EVENT_NONE";

        case EVENT_ROTATE:
            return "EVENT_ROTATE";

        case EVENT_LEFT:
            return "EVENT_LEFT";

        case EVENT_RIGHT:
            return "EVENT_RIGHT";

        case EVENT_DROP_SOFT:
            return "EVENT_DROP_SOFT";

        case EVENT_DROP_HARD:
            return "EVENT_DROP_HARD";

        case EVENT_PAUSE:
            return "EVENT_PAUSE";

        case EVENT_QUIT:
            return "EVENT_QUIT";

        case EVENT_HOLD:
            return "EVENT_HOLD";

        case EVENT_SELECT:
            return "EVENT_SELECT";
    }
    return "EVENT_NONE";
}
