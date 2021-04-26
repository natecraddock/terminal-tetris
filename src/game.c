#include <unistd.h>

#include "game.h"
#include "events.h"
#include "screen.h"
#include "piece.h"


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
    queue_add(queue, piece_new(PIECE_O));
    queue_add(queue, piece_new(PIECE_I));
    queue_add(queue, piece_new(PIECE_T));
    queue_add(queue, piece_new(PIECE_L));
    queue_add(queue, piece_new(PIECE_J));
    queue_add(queue, piece_new(PIECE_S));
    queue_add(queue, piece_new(PIECE_Z));

    queue_shuffle(queue);
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

    gameloop(&game);
}

