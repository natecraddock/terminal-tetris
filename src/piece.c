#include "piece.h"

void point_set(Point *point, int x, int y) {
    point->x = x;
    point->y = y;
}

Piece piece_new(PieceType type) {
    Piece piece;
    piece.type = type;

    switch (type){
        case PIECE_O:
            point_set(&piece.blocks[0], 0, 0);
            point_set(&piece.blocks[1], 1, 0);
            point_set(&piece.blocks[2], 0, 1);
            point_set(&piece.blocks[3], 1, 1);
            break;

        case PIECE_I:
            point_set(&piece.blocks[0], 0, 1);
            point_set(&piece.blocks[1], 1, 1);
            point_set(&piece.blocks[2], 2, 1);
            point_set(&piece.blocks[3], 3, 1);
            break;

        case PIECE_T:
            point_set(&piece.blocks[0], 1, 0);
            point_set(&piece.blocks[1], 0, 1);
            point_set(&piece.blocks[2], 1, 1);
            point_set(&piece.blocks[3], 2, 1);
            break;

        case PIECE_L:
            point_set(&piece.blocks[0], 2, 0);
            point_set(&piece.blocks[1], 0, 1);
            point_set(&piece.blocks[2], 1, 1);
            point_set(&piece.blocks[3], 2, 1);
            break;

        case PIECE_J:
            point_set(&piece.blocks[0], 0, 0);
            point_set(&piece.blocks[1], 0, 1);
            point_set(&piece.blocks[2], 1, 1);
            point_set(&piece.blocks[3], 2, 1);
            break;

        case PIECE_S:
            point_set(&piece.blocks[0], 1, 0);
            point_set(&piece.blocks[1], 2, 0);
            point_set(&piece.blocks[2], 0, 1);
            point_set(&piece.blocks[3], 1, 1);
            break;

        case PIECE_Z:
            point_set(&piece.blocks[0], 0, 0);
            point_set(&piece.blocks[1], 1, 0);
            point_set(&piece.blocks[2], 1, 1);
            point_set(&piece.blocks[3], 2, 1);
            break;
    }

    return piece;
}
