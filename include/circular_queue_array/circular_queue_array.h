#ifndef __CIRCULAR_QUEUE_ARRAY_H__
#define __CIRCULAR_QUEUE_ARRAY_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 10  // Tamaño máximo del arreglo para la cola

typedef void* Data;  

typedef struct circular_queue_array {
    Data data[MAX_SIZE];  // Arreglo de datos
    int front;             // Frente
    int rear;              // Final
    int size;              // Número de elementos
} CQueueArray;

CQueueArray* cqueue_array_create();                  // Crea
void cqueue_array_destroy(CQueueArray* q);           // Libera
bool cqueue_array_enqueue(CQueueArray* q, Data value);  // Insertaal final 
Data cqueue_array_dequeue(CQueueArray* q);           // Elimina del frente
bool cqueue_array_is_empty(CQueueArray* q);          // Verifica si está vacía
bool cqueue_array_is_full(CQueueArray* q);           // Verifica si está llena
void cqueue_array_print(CQueueArray* q);             // Imprime los elementos

#endif
