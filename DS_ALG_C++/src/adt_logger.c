
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"

#include "adt_logger.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Static prototypes
static s16 LOGGER_write(Logger* queue, char* text);
static void* LOGGER_flush(Logger* queue);

static s16 LOGGER_destroy(Logger* queue);
static s16 LOGGER_reset(Logger* queue);
static s16 LOGGER_resize(Logger* queue, u16 new_size);

static u16 LOGGER_capacity(const Logger* queue);
static u16 LOGGER_length(const Logger* queue);
static s16 LOGGER_isEmpty(const Logger* queue);
static s16 LOGGER_isFull(const Logger* queue);
static s16 LOGGER_concat(Logger* queue, const Logger* queue_src);

static void LOGGER_print(Logger* queue);

// Memory Node's API Definitions
struct logger_ops_s logger_ops = {
    .write = LOGGER_write,
    .flush = LOGGER_flush,
    .destroy = LOGGER_destroy,
    .reset = LOGGER_reset,
    .resize = LOGGER_resize,
    .capacity = LOGGER_capacity,
    .length = LOGGER_length,
    .isEmpty = LOGGER_isEmpty,
    .isFull = LOGGER_isFull,
    .concat = LOGGER_concat,
    .print = LOGGER_print
};

Logger* LOGGER_create(u16 capacity) {
    // ALopezESAT: This could be inline, also no need to have less than if it is unsigned
    if (capacity <= 0) {
        return NULL;
    }

    Logger* q_temp = MM->malloc(sizeof(Logger));
    if (NULL == q_temp) {
        // ALopezESAT: Same as stack
        MM->free(q_temp);
        return NULL;
    }

    q_temp->storage_ = LIST_create(capacity);
    // ALopezESAT: Same as stack
    // Ok, from here after, all the comments are the same as in stack so... check stack first and apply them here.
    q_temp->ops_ = &logger_ops;

    return q_temp;
}

s16 LOGGER_write(Logger* queue, char* text) {
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }
    return queue->storage_->ops_->enqueue(queue->storage_, (void*)text, (u16)sizeof(text));

    return kErrorCode_Ok;
}

void* LOGGER_flush(Logger* queue) {
    if (NULL == queue)
    {
        return NULL;
    }

    return queue->storage_->ops_->dequeue(queue->storage_);
}

s16 LOGGER_destroy(Logger* queue) {
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }
    
    queue->storage_->ops_->destroy(queue->storage_);
    MM->free(queue);

    return kErrorCode_Ok;
}

s16 LOGGER_reset(Logger* queue) {

    if (NULL == queue || NULL == queue->storage_)
    {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->ops_->reset(queue->storage_);
}

s16 LOGGER_resize(Logger* queue, u16 new_size) {
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->ops_->resize(queue->storage_, new_size);
}

u16 LOGGER_capacity(const Logger* queue) {
    if (NULL == queue)
    {
        return 0;
    }

    return queue->storage_->ops_->capacity(queue->storage_);
}

u16 LOGGER_length(const Logger* queue) {
    if (NULL == queue)
    {
        return 0;
    }

    return queue->storage_->ops_->length(queue->storage_);
}

s16 LOGGER_isEmpty(const Logger* queue) {
    if (NULL == queue) {
        return 0;
    }

    return queue->storage_->ops_->isEmpty(queue->storage_);
}

s16 LOGGER_isFull(const Logger* queue) {
    if (NULL == queue) {
        return 0;
    }

    return queue->storage_->ops_->isFull(queue->storage_);
}


s16 LOGGER_concat(Logger* queue, const Logger* queue_src) {
    if (NULL == queue || NULL == queue_src) {
        return kErrorCode_QueueNull;
    }
  
    return queue->storage_->ops_->concat(queue->storage_, queue_src->storage_);
}

void LOGGER_print(Logger* queue) {
    if (NULL == queue) {
        printf("\t[Queue Info] queue: NULL\n");
        return;
    }

    queue->storage_->ops_->print(queue->storage_);
}






