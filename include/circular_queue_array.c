#include "circular_queue_array.h"
#include <stdio.h>
#include <stdlib.h>

CQueueArray* cqueue_array_create() {
    CQueueArray* queue = (CQueueArray*)malloc(sizeof(CQueueArray));
    if (queue == NULL) {
        perror("Error al crear la cola");
        return NULL;
    }
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

void cqueue_array_destroy(CQueueArray* q) {
    if (q != NULL) {
        free(q);
    }
}

bool cqueue_array_enqueue(CQueueArray* q, Data value) {
    if (q == NULL) {
        return false;
    }
    if (cqueue_array_is_full(q)) {
        return false; // La cola está llena
    }

    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE; 
    q->size++;
    return true;
}

Data cqueue_array_dequeue(CQueueArray* q) {
    if (q == NULL || cqueue_array_is_empty(q)) {
        return NULL; // Cola vacía
    }

    Data value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE; 
    q->size--;
    return value;
}

bool cqueue_array_is_empty(CQueueArray* q) {
    return (q != NULL && q->size == 0);
}

bool cqueue_array_is_full(CQueueArray* q) {
    return (q != NULL && q->size == MAX_SIZE);
}

void cqueue_array_print(CQueueArray* q) {
    if (q == NULL || cqueue_array_is_empty(q)) {
        printf("La cola está vacía.\n");
        return;
    }

    int i = q->front;
    int count = 0;
    while (count < q->size) {
        printf("%p ", q->data[i]); 
        i = (i + 1) % MAX_SIZE;    
        count++;
    }
    printf("\n");
}
