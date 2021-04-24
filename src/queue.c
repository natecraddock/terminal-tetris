#include <stdlib.h>

#include "queue.h"

void queue_add(Queue *queue, Piece item) {
    if (queue->size >= QUEUE_CAPACITY) {
        return;
    }

    queue->data[queue->size] = item;
    queue->size += 1;
}

static void shift_down(Queue *queue) {
    for (int i = 0; i < queue->size - 1; i++) {
        queue->data[i] = queue->data[i + 1];
    }
}

bool queue_pop(Queue *queue, Piece *piece) {
    if (queue->size <= 0){
        return false;
    }

    *piece = queue->data[0];
    shift_down(queue);
    queue->size -= 1;

    return true;
}

void queue_shuffle(Queue *queue) {
    int num_iterations = (rand() % 10) + 6;
    for (int i = 0; i < num_iterations; i++) {
        int first = (rand() % queue->size);
        int second = (rand() % queue->size);

        Piece temp = queue->data[first];
        queue->data[first] = queue->data[second];
        queue->data[second] = temp;
    }
}
