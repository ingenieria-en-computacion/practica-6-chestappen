#ifndef CIRCULAR_QUEUE_GENERIC_H
#define CIRCULAR_QUEUE_GENERIC_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

// Macro para declarar la cola circular genérica
#define DECLARE_CIRCULAR_QUEUE(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    \
    typedef struct { \
        Node_##TYPE* front; \
        Node_##TYPE* rear; \
        size_t size; \
        size_t capacity; \
    } CircularQueue_##TYPE; \
    \
    CircularQueue_##TYPE* circular_queue_##TYPE##_create(size_t capacity); \
    bool circular_queue_##TYPE##_enqueue(CircularQueue_##TYPE* queue, TYPE data); \
    bool circular_queue_##TYPE##_dequeue(CircularQueue_##TYPE* queue, TYPE* data); \
    bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue); \
    bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue); \
    void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue); \
    void circular_queue_##TYPE##_print(const CircularQueue_##TYPE* queue, void (*print_fn)(TYPE));

// Macro para implementar las funciones de la cola circular genérica
#define IMPLEMENT_CIRCULAR_QUEUE(TYPE) \
    CircularQueue_##TYPE* circular_queue_##TYPE##_create(size_t capacity) { \
        CircularQueue_##TYPE* queue = malloc(sizeof(CircularQueue_##TYPE)); \
        if (!queue) return NULL; \
        queue->front = queue->rear = NULL; \
        queue->size = 0; \
        queue->capacity = capacity; \
        return queue; \
    } \
    \
    bool circular_queue_##TYPE##_enqueue(CircularQueue_##TYPE* queue, TYPE data) { \
        if (!queue || circular_queue_##TYPE##_is_full(queue)) return false; \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return false; \
        new_node->data = data; \
        if (queue->size == 0) { \
            queue->front = queue->rear = new_node; \
            new_node->next = queue->front; \
        } else { \
            queue->rear->next = new_node; \
            queue->rear = new_node; \
            new_node->next = queue->front; \
        } \
        queue->size++; \
        return true; \
    } \
    \
    bool circular_queue_##TYPE##_dequeue(CircularQueue_##TYPE* queue, TYPE* data) { \
        if (!queue || circular_queue_##TYPE##_is_empty(queue)) return false; \
        Node_##TYPE* temp = queue->front; \
        *data = queue->front->data; \
        if (queue->size == 1) { \
            queue->front = queue->rear = NULL; \
        } else { \
            queue->front = queue->front->next; \
            queue->rear->next = queue->front; \
        } \
        free(temp); \
        queue->size--; \
        return true; \
    } \
    \
    bool circular_queue_##TYPE##_is_empty(const CircularQueue_##TYPE* queue) { \
        return queue->size == 0; \
    } \
    \
    bool circular_queue_##TYPE##_is_full(const CircularQueue_##TYPE* queue) { \
        return queue->size == queue->capacity; \
    } \
    \
    void circular_queue_##TYPE##_destroy(CircularQueue_##TYPE* queue) { \
        if (!queue) return; \
        while (!circular_queue_##TYPE##_is_empty(queue)) { \
            TYPE temp; \
            circular_queue_##TYPE##_dequeue(queue, &temp); \
        } \
        free(queue); \
    } \
    \
    void circular_queue_##TYPE##_print(const CircularQueue_##TYPE* queue, void (*print_fn)(TYPE)) { \
        if (!queue || !print_fn) return; \
        Node_##TYPE* current = queue->front; \
        printf("["); \
        for (size_t i = 0; i < queue->size; i++) { \
            print_fn(current->data); \
            if (i < queue->size - 1) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }

// Declaración para tipos concretos
DECLARE_CIRCULAR_QUEUE(int)
DECLARE_CIRCULAR_QUEUE(char)
DECLARE_CIRCULAR_QUEUE(float)

// Implementación de la cola circular genérica para tipos concretos
#ifdef CIRCULAR_QUEUE_IMPLEMENTATION
IMPLEMENT_CIRCULAR_QUEUE(int)
IMPLEMENT_CIRCULAR_QUEUE(char)
IMPLEMENT_CIRCULAR_QUEUE(float)
#endif
