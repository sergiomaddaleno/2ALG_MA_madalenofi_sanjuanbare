// adt_queue.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__

#include "adt_memory_node.h"
#include "adt_list.h"

typedef struct adt_queue_s {
    List* storage_;
	struct queue_ops_s* ops_;
} Queue;

struct queue_ops_s {

    s16(*enqueue)(Queue* queue, void* data, u16 bytes);
    void* (*dequeue)(Queue* queue);
    void* (*back)(const Queue* queue);
    void* (*front)(const Queue* queue);

    s16(*destroy)(Queue* queue);
    s16(*reset)(Queue* queue);
    s16(*resize)(Queue* queue, u16 new_size);
    u16(*capacity)(const Queue* queue);
    u16(*length)(const Queue* queue);
    s16(*isEmpty)(const Queue* queue);
    s16(*isFull)(const Queue* queue);
  
    s16(*concat)(Queue* queue, const Queue* queue_src);
    void (*print)(Queue* queue);
};

Queue* QUEUE_create(u16 capacity);

#endif //__ADT_QUEUE_H__
