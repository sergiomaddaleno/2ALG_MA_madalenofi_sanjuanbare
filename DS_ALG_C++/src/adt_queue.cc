
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_queue.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"


adt_queue_s::adt_queue_s(u16 capacity)
{
    if (capacity > 0) {
        storage_ = new adt_list_s(capacity);
    }
    else {
        storage_ = NULL;
    }
}

adt_queue_s::~adt_queue_s()
{
}

s16 adt_queue_s::enqueue(adt_queue_s* queue, void* data, u16 bytes)
{
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }

    queue->storage_->insertLast(queue->storage_, data, bytes);

    return kErrorCode_Ok;
}

void* adt_queue_s::dequeue(adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return NULL;
    }

    return queue->storage_->extractFirst(queue->storage_);
}

void* adt_queue_s::back(const adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return NULL;
    }

    return queue->storage_->last(queue->storage_);
}

void* adt_queue_s::front(const adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return NULL;
    }

    return queue->storage_->first(queue->storage_);
}

s16 adt_queue_s::destroy(adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }

    queue->storage_->destroy(queue->storage_);
    //delete[] queue;

    return kErrorCode_Ok;
}

s16 adt_queue_s::reset(adt_queue_s* queue)
{
    if (NULL == queue || NULL == queue->storage_)
    {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->reset(queue->storage_);
}

s16 adt_queue_s::resize(adt_queue_s* queue, u16 new_size)
{
    if (NULL == queue)
    {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->resize(queue->storage_, new_size);
}

u16 adt_queue_s::capacity(const adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return 0;
    }

    return queue->storage_->capacity(queue->storage_);
}

u16 adt_queue_s::length(const adt_queue_s* queue)
{
    if (NULL == queue)
    {
        return 0;
    }

    return queue->storage_->length(queue->storage_);
}

s16 adt_queue_s::isEmpty(const adt_queue_s* queue)
{
    if (NULL == queue) {
        return 0;
    }

    return queue->storage_->isEmpty(queue->storage_);
}

s16 adt_queue_s::isFull(const adt_queue_s* queue)
{
    if (NULL == queue) {
        return 0;
    }

    return queue->storage_->isFull(queue->storage_);
}

s16 adt_queue_s::concat(adt_queue_s* queue, const adt_queue_s* queue_src)
{
    if (NULL == queue || NULL == queue_src) {
        return kErrorCode_QueueNull;
    }

    return queue->storage_->concat(queue->storage_, queue_src->storage_);
}

void adt_queue_s::print(adt_queue_s* queue)
{
    if (NULL == queue) {
        printf("\t[Queue Info] queue: NULL\n");
        return;
    }

    queue->storage_->print(queue->storage_);
}

