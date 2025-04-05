#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_BIQUEUE(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
        struct Node_##TYPE* prev; \
    } Node_##TYPE; \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } BiQueue_##TYPE; \
    \
    BiQueue_##TYPE* biqueue_##TYPE##_create(void); \
    void biqueue_##TYPE##_destroy(BiQueue_##TYPE* queue); \
    bool biqueue_##TYPE##_push_front(BiQueue_##TYPE* queue, TYPE data); \
    bool biqueue_##TYPE##_push_back(BiQueue_##TYPE* queue, TYPE data); \
    bool biqueue_##TYPE##_pop_front(BiQueue_##TYPE* queue); \
    bool biqueue_##TYPE##_pop_back(BiQueue_##TYPE* queue); \
    size_t biqueue_##TYPE##_length(const BiQueue_##TYPE* queue); \
    void biqueue_##TYPE##_print(const BiQueue_##TYPE* queue, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_BIQUEUE(TYPE) \
    BiQueue_##TYPE* biqueue_##TYPE##_create(void) { \
        BiQueue_##TYPE* queue = malloc(sizeof(BiQueue_##TYPE)); \
        if (!queue) return NULL; \
        queue->head = queue->tail = NULL; \
        queue->length = 0; \
        return queue; \
    } \
    \
    void biqueue_##TYPE##_destroy(BiQueue_##TYPE* queue) { \
        if (!queue) return; \
        Node_##TYPE* current = queue->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(queue); \
    } \
    \
    bool biqueue_##TYPE##_push_front(BiQueue_##TYPE* queue, TYPE data) { \
        if (!queue) return false; \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return false; \
        new_node->data = data; \
        new_node->next = queue->head; \
        new_node->prev = NULL; \
        if (queue->head) queue->head->prev = new_node; \
        queue->head = new_node; \
        if (!queue->tail) queue->tail = new_node; \
        queue->length++; \
        return true; \
    } \
    \
    bool biqueue_##TYPE##_push_back(BiQueue_##TYPE* queue, TYPE data) { \
        if (!queue) return false; \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return false; \
        new_node->data = data; \
        new_node->next = NULL; \
        new_node->prev = queue->tail; \
        if (queue->tail) queue->tail->next = new_node; \
        queue->tail = new_node; \
        if (!queue->head) queue->head = new_node; \
        queue->length++; \
        return true; \
    } \
    \
    bool biqueue_##TYPE##_pop_front(BiQueue_##TYPE* queue) { \
        if (!queue || !queue->head) return false; \
        Node_##TYPE* to_delete = queue->head; \
        queue->head = queue->head->next; \
        if (queue->head) queue->head->prev = NULL; \
        if (!queue->head) queue->tail = NULL; \
        free(to_delete); \
        queue->length--; \
        return true; \
    } \
    \
    bool biqueue_##TYPE##_pop_back(BiQueue_##TYPE* queue) { \
        if (!queue || !queue->tail) return false; \
        Node_##TYPE* to_delete = queue->tail; \
        queue->tail = queue->tail->prev; \
        if (queue->tail) queue->tail->next = NULL; \
        if (!queue->tail) queue->head = NULL; \
        free(to_delete); \
        queue->length--; \
        return true; \
    } \
    \
    size_t biqueue_##TYPE##_length(const BiQueue_##TYPE* queue) { \
        return queue ? queue->length : 0; \
    } \
    \
    void biqueue_##TYPE##_print(const BiQueue_##TYPE* queue, void (*print_fn)(TYPE)) { \
        if (!queue || !print_fn) return; \
        printf("["); \
        Node_##TYPE* current = queue->head; \
        while (current) { \
            print_fn(current->data); \
            if (current->next) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }

// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_BIQUEUE(int)
DECLARE_BIQUEUE(char)
DECLARE_BIQUEUE(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef BIQUEUE_IMPLEMENTATION
IMPLEMENT_BIQUEUE(int)
IMPLEMENT_BIQUEUE(char)
IMPLEMENT_BIQUEUE(float)
#endif
