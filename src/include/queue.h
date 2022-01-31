#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "piece.h"

#define QUEUE_CAPACITY 7

typedef struct Queue {
    Piece data[QUEUE_CAPACITY];
    int size;
} Queue;

void queue_add(Queue *queue, Piece item);
bool queue_pop(Queue *queue, Piece *piece);
void queue_shuffle(Queue *queue);
bool queue_to_queue_copy(Queue *queueOne, Queue * queueTwo);

#endif
