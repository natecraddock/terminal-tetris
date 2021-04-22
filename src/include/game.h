typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_PAUSE,
} State;

typedef struct Game {
    State state;
} Game;

void start_game();
