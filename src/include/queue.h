#define QUEUE_CAPACITY 7

typedef struct Queue {
    int data[QUEUE_CAPACITY];
    int size;
} Queue;

void queue_add(Queue *queue, int item);
int queue_pop(Queue *queue);
void queue_shuffle(Queue *queue);
