#ifndef PIECE_H
#define PIECE_H

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

void point_set(Point *point, int x, int y);

Piece piece_new(PieceType type);

#endif
