#ifndef __BICIRCULAR_QUEUE_ARRAY_H__
#define __BICIRCULAR_QUEUE_ARRAY_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_BIQUEUE_SIZE 10  // Tamaño máximo del arreglo para la bicola

typedef struct biqueue_array {
    void* data[MAX_SIZE];  // Arreglo de datos
    int front;             // Frente
    int rear;              // Final 
    int size;              // Número de elementos 
} BiCQueueArray;

BiCQueueArray* biqueue_array_create();                   // Crea
void biqueue_array_destroy(BiCQueueArray* q);            // Libera
void biqueue_array_enqueue_front(BiCQueueArray* q, void* data);  // Inserta al frente
void biqueue_array_enqueue_rear(BiCQueueArray* q, void* data);   // Inserta al final
void* biqueue_array_dequeue_front(BiCQueueArray* q);           // Elimina del frente
void* biqueue_array_dequeue_rear(BiCQueueArray* q);            // Elimina del final
bool biqueue_array_is_empty(BiCQueueArray* q);          // Verificar si está vacía
bool biqueue_array_is_full(BiCQueueArray* q);           // Verificar si está llena
void biqueue_array_print(BiCQueueArray* q);             // Imprimir los elementos 

#endif
