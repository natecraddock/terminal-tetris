#ifndef GAME_H
#define GAME_H

#include "queue.h"

typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_PAUSE,
} State;

typedef struct Game {
    State state;
    Queue next_queue;
    Queue bag;
} Game;

void start_game();

#endif
