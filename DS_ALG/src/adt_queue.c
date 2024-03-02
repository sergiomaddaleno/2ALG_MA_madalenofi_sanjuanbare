
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_queue.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Static prototypes
static s16 QUEUE_enqueue(Queue* queue, void* data, u16 bytes);
static void* QUEUE_dequeue(Queue* queue);
static void* QUEUE_back(const Queue* queue);
static void* QUEUE_front(const Queue* queue);

static s16 QUEUE_destroy(Queue* queue);
static s16 QUEUE_reset(Queue* queue);
static s16 QUEUE_resize(Queue* queue, u16 new_size);

static u16 QUEUE_capacity(const Queue* queue);
static u16 QUEUE_length(const Queue* queue);
static s16 QUEUE_isEmpty(const Queue* queue);
static s16 QUEUE_isFull(const Queue* queue);
static s16 QUEUE_concat(Queue* queue, const Queue* queue_src);

static void QUEUE_print(Queue* queue);

// Memory Node's API Definitions
struct queue_ops_s queue_ops = {
    .enqueue = QUEUE_enqueue,
    .dequeue = QUEUE_dequeue,
    .back = QUEUE_back,
    .front = QUEUE_front,

    .destroy = QUEUE_destroy,
    .reset = QUEUE_reset,
    .resize = QUEUE_resize,
    .capacity = QUEUE_capacity,
    .length = QUEUE_length,
    .isEmpty = QUEUE_isEmpty,
    .isFull = QUEUE_isFull,
    .concat = QUEUE_concat,
    .print = QUEUE_print
};

Queue* QUEUE_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Queue* q_temp = MM->malloc(sizeof(Queue));
    if (NULL == q_temp) {
        MM->free(q_temp);
        return NULL;
    }

    q_temp->storage_ = LIST_create(capacity);
    q_temp->ops_ = &queue_ops;

    return q_temp;
}

s16 QUEUE_enqueue(Queue* queue, void* data, u16 bytes) {
    /*if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }

    queue->storage_->ops_->insertFirst(queue, data, bytes);

    return kErrorCode_Ok;*/

}

void* QUEUE_dequeue(Queue* queue) {

}

void* QUEUE_back(const Queue* queue) {

}

void* QUEUE_front(const Queue* queue) {

}

//---

s16 QUEUE_destroy(Queue* queue) {

    
}

s16 QUEUE_reset(Queue* queue) {

    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }
    if (NULL == queue->storage_)
    {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->ops_->reset(queue->storage_);
}

s16 QUEUE_resize(Queue* queue, u16 new_size) {

}

u16 QUEUE_capacity(const Queue* queue) {
   
}

u16 QUEUE_length(const Queue* queue) {
    
}

s16 QUEUE_isEmpty(const Queue* queue) {
    
}

s16 QUEUE_isFull(const Queue* queue) {
    
}


s16 QUEUE_concat(Queue* queue, const Queue* queue_src) {

  
}

void QUEUE_print(Queue* queue) {
    if (NULL == queue) {
        printf("\t[Queue Info] queue: NULL\n");
        return;
    }

    queue->storage_->ops_->print(queue->storage_);
}






