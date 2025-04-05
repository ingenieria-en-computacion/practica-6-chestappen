#include "biqueue_array.h"
#include <stdio.h>
#include <stdlib.h>

BiCQueueArray* biqueue_array_create() {
    BiCQueueArray* queue = (BiCQueueArray*)malloc(sizeof(BiCQueueArray));
    if (queue == NULL) {
        perror("Error al crear la bicola");
        return NULL;
    }
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

void biqueue_array_destroy(BiCQueueArray* q) {
    if (q != NULL) {
        free(q);
    }
}

void biqueue_array_enqueue_front(BiCQueueArray* q, void* data) {
    if (q == NULL || biqueue_array_is_full(q)) {
        return; // No inserta si está llena o es NULL
    }

    q->front = (q->front - 1 + MAX_SIZE) % MAX_BIQUEUE_SIZE; 
    q->data[q->front] = data;
    q->size++;
}

void biqueue_array_enqueue_rear(BiCQueueArray* q, void* data) {
    if (q == NULL || biqueue_array_is_full(q)) {
        return; // No inserta si está llena o es NULL
    }

    q->data[q->rear] = data;
    q->rear = (q->rear + 1) % MAX_SIZE; 
    q->size++;
}

void* biqueue_array_dequeue_front(BiCQueueArray* q) {
    if (q == NULL || biqueue_array_is_empty(q)) {
        return NULL; // No elimina si está vacía o es NULL
    }

    void* value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE; 
    q->size--;
    return value;
}

void* biqueue_array_dequeue_rear(BiCQueueArray* q) {
    if (q == NULL || biqueue_array_is_empty(q)) {
        return NULL; // No elimina si está vacía o es NULL
    }

    q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE; 
    void* value = q->data[q->rear];
    q->size--;
    return value;
}

bool biqueue_array_is_empty(BiCQueueArray* q) {
    return (q != NULL && q->size == 0);
}

bool biqueue_array_is_full(BiCQueueArray* q) {
    return (q != NULL && q->size == MAX_SIZE);
}

void biqueue_array_print(BiCQueueArray* q) {
    if (q == NULL || biqueue_array_is_empty(q)) {
        printf("La bicola está vacía.\n");
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
