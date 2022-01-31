#include <stdbool.h>
#include <unistd.h>

#include "game.h"
#include "events.h"
#include "queue.h"
#include "screen.h"
#include "piece.h"

static void fill_bag(Queue *queue) {
    queue_add(queue, piece_new(PIECE_O));
    queue_add(queue, piece_new(PIECE_I));
    queue_add(queue, piece_new(PIECE_T));
    queue_add(queue, piece_new(PIECE_L));
    queue_add(queue, piece_new(PIECE_J));
    queue_add(queue, piece_new(PIECE_S));
    queue_add(queue, piece_new(PIECE_Z));

    queue_shuffle(queue);
}

static bool bottomCollisionCheck(Piece activePiece, char board[BOARD_HEIGHT][BOARD_WIDTH]) {

    // TODO: Check for other blocks in board
    
    // See if it touched bottom of board
    if (activePiece.location.y == BOARD_HEIGHT) {
        return true;

        // TODO: Place active piece on board
    }

    return false;
}

// Moves the game's active piece down in the board
// If the piece hits the bottom it returns true
static bool moveActivePieceDown(Game *game) {
   
    // See if active piece is at bottom
    if (bottomCollisionCheck(game->active_piece, game->board)) {
        return true;   
    }
    
    // Advance the piece downward
    game->active_piece.location.y += 1;
    return false;
}

// Retrieves an an active piece from queue or hold
static void getNewActivePiece(Game *game, bool isHold) {

    // TODO: Check if we are grabing from queue or hold

    queue_pop(&game->next_queue, &game->active_piece);
    point_set(&game->active_piece.location, 4, 0);
    
    // Refill bag if it is empty
    if (game->bag.size == 0) {
        fill_bag(&game->bag);
    }
    
    // Take piece from bag and put it into next_queue
    queue_to_queue_copy(&game->bag, &game->next_queue);
}

static void handle_menu_event(Game *game, Event event) {
    if (event == EVENT_SELECT) {
        game->state = STATE_PLAY;
    }
    draw_menu();
}

static void handle_play_event(Game *game, Event event) {
    if (event == EVENT_QUIT) {
        game->state = STATE_MENU;
        return;
    }
    // Get time and see if block needs to fall
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC_RAW, &current);

    unsigned long delta_us = (current.tv_sec - game->last_fall.tv_sec) * 1000000 + ((current.tv_nsec - game->last_fall.tv_nsec) / 1000);

    if (delta_us > 1000000) {
        game->last_fall = current;

        // Move active piece down
        bool pieceLocked = moveActivePieceDown(game);

        if (pieceLocked) {
            getNewActivePiece(game, false);
        }
    }

    draw_game(game);
}

static void gameloop(Game *game) {
    while (1) {
        Event event = get_event();
        erase_screen();

#if DEBUG_LINE
        const char *event_str = event_to_string(event);
        draw_debug_line(event_str);
#endif

        switch(game->state) {
            case STATE_MENU:
                handle_menu_event(game, event);
                break;

            case STATE_PLAY:
                handle_play_event(game, event);
                break;

            case STATE_PAUSE:
                break;
        }

        update_screen();
        // 100 ms delay
        usleep(100000);
    }
}

static void init_board(char board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board[i][j] = COLOR_NONE;
        }
    }
}

void start_game() {
    Game game;
    game.state = STATE_MENU;

    game.bag.size = 0;
    game.next_queue.size = 0;

    // Initialize bag and next queue
    fill_bag(&game.bag);
    game.next_queue = game.bag;
    fill_bag(&game.bag);

    // Initialize board
    init_board(game.board);

    // Give active piece
    queue_pop(&game.next_queue, &game.active_piece);
    point_set(&game.active_piece.location, 4, 0);

    gameloop(&game);
}
