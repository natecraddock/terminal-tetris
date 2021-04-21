typedef enum {
    EVENT_NONE,
    EVENT_ROTATE,
    EVENT_LEFT,
    EVENT_RIGHT,
    EVENT_DROP_HARD,
    EVENT_DROP_SOFT,
    EVENT_PAUSE,
    EVENT_QUIT,
    EVENT_HOLD,
} Event;

Event get_event();

const char *event_to_string(Event event);
