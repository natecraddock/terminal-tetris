#ifndef GAME_H
#define GAME_H

#include <time.h>

#include "piece.h"
#include "queue.h"

#define BOARD_HEIGHT 20
#define BOARD_WIDTH 10

typedef enum {
    STATE_MENU,
    STATE_PLAY,
    STATE_PAUSE,
} State;

typedef enum {
    COLOR_NONE = 0,
    COLOR_O = PIECE_O,
    COLOR_I = PIECE_I,
    COLOR_T = PIECE_T,
    COLOR_L = PIECE_L,
    COLOR_J = PIECE_J,
    COLOR_S = PIECE_S,
    COLOR_Z = PIECE_Z,
} BoardColor;

typedef struct Game {
    State state;
    Queue next_queue;
    Queue bag;
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    Piece active_piece;
    struct timespec last_fall;
} Game;

void start_game();

#endif
