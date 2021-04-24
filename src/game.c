#include <unistd.h>

#include "game.h"
#include "events.h"
#include "screen.h"

typedef enum {
    PIECE_O,
    PIECE_I,
    PIECE_T,
    PIECE_L,
    PIECE_J,
    PIECE_S,
    PIECE_Z,
} PieceType;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point location;
    Point blocks[4];
    PieceType type;
} Piece;

static void point_set(Point *point, int x, int y){
    point->x = x;
    point->y = y;
}

static void piece_new(Piece *piece, PieceType type){
    piece->type = type;

    switch (type){
        case PIECE_O:
            point_set(&piece->blocks[0], 1, 0);
            point_set(&piece->blocks[1], 2, 0);
            point_set(&piece->blocks[2], 1, 1);
            point_set(&piece->blocks[3], 2, 1);
            break;

        case PIECE_I:
            point_set(&piece->blocks[0], 1, 0);
            point_set(&piece->blocks[1], 1, 1);
            point_set(&piece->blocks[2], 1, 2);
            point_set(&piece->blocks[3], 1, 3);
            break;

        case PIECE_T:
            point_set(&piece->blocks[0], 1, 0);
            point_set(&piece->blocks[1], 0, 1);
            point_set(&piece->blocks[2], 1, 1);
            point_set(&piece->blocks[3], 2, 1);
            break;

        case PIECE_L:
            point_set(&piece->blocks[0], 2, 0);
            point_set(&piece->blocks[1], 0, 1);
            point_set(&piece->blocks[2], 1, 1);
            point_set(&piece->blocks[3], 2, 1);
            break;

        case PIECE_J:
            point_set(&piece->blocks[0], 0, 0);
            point_set(&piece->blocks[1], 0, 1);
            point_set(&piece->blocks[2], 1, 1);
            point_set(&piece->blocks[3], 2, 1);
            break;

        case PIECE_S:
            point_set(&piece->blocks[0], 1, 0);
            point_set(&piece->blocks[1], 2, 0);
            point_set(&piece->blocks[2], 0, 1);
            point_set(&piece->blocks[3], 1, 1);
            break;

        case PIECE_Z:
            point_set(&piece->blocks[0], 0, 0);
            point_set(&piece->blocks[1], 1, 0);
            point_set(&piece->blocks[2], 1, 1);
            point_set(&piece->blocks[3], 1, 2);
            break;
    }
}

static void handle_menu_event(Game *game, Event event) {
    if (event == EVENT_SELECT) {
        game->state = STATE_PLAY;
    }
    draw_menu();
}

static void handle_play_event(Game *game, Event event) {
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

        sleep(1);
    }
}

static void fill_bag(Queue *queue) {
    queue_add(queue, PIECE_O);
    queue_add(queue, PIECE_I);
    queue_add(queue, PIECE_T);
    queue_add(queue, PIECE_L);
    queue_add(queue, PIECE_J);
    queue_add(queue, PIECE_S);
    queue_add(queue, PIECE_Z);

    queue_shuffle(queue);
}

void start_game() {
    Game game;
    game.state = STATE_MENU;

    // Initialize bag and next queue
    fill_bag(&game.bag);
    game.next_queue = game.bag;
    fill_bag(&game.bag);

    gameloop(&game);
}

