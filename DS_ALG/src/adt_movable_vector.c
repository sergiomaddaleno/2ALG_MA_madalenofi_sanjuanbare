/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_movable_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

//Static prototipes
static s16 MOVABLE_VECTOR_destroy(MovableVector * vector);
static s16 MOVABLE_VECTOR_softReset(MovableVector * vector);
static s16 MOVABLE_VECTOR_reset(MovableVector * vector);
static s16 MOVABLE_VECTOR_resize(MovableVector * vector, u16 new_size);
static u16 MOVABLE_VECTOR_capacity(MovableVector * vector);
static u16 MOVABLE_VECTOR_length(MovableVector * vector);
static boolean MOVABLE_VECTOR_isEmpty(MovableVector * vector);
static boolean MOVABLE_VECTOR_isFull(MovableVector * vector);
static void* MOVABLE_VECTOR_first(MovableVector * vector);
static void* MOVABLE_VECTOR_at(MovableVector * vector,u16 position);
static void* MOVABLE_VECTOR_last(MovableVector * vector);
static s16 MOVABLE_VECTOR_insertFirst(MovableVector * vector, void* data, u16 bytes);
static s16 MOVABLE_VECTOR_insertLast(MovableVector * vector, void* data, u16 bytes);
static s16 MOVABLE_VECTOR_insertAt(MovableVector * vector, void* data, u16 bytes,u16 position);
static void* MOVABLE_VECTOR_extractFirst(MovableVector * vector);
static void* MOVABLE_VECTOR_extractLast(MovableVector * vector);
static void* MOVABLE_VECTOR_extractAt(MovableVector * vector, u16 position);
static s16 MOVABLE_VECTOR_traverse(MovableVector * vector, void (*callback)(MemoryNode*));
static s16 MOVABLE_VECTOR_concat(MovableVector * vector, MovableVector * vector_src);
static void MOVABLE_VECTOR_print(MovableVector * vector);

// Memory Node's API Definitions
struct movable_vector_ops_s movable_vector_ops = {
    .destroy = MOVABLE_VECTOR_destroy,
    .softReset = MOVABLE_VECTOR_softReset,
    .reset = MOVABLE_VECTOR_reset,
    .resize = MOVABLE_VECTOR_resize,
    .capacity = MOVABLE_VECTOR_capacity,
    .length = MOVABLE_VECTOR_length,
    .isEmpty = MOVABLE_VECTOR_isEmpty,
    .isFull = MOVABLE_VECTOR_isFull,
    .first = MOVABLE_VECTOR_first,
    .last = MOVABLE_VECTOR_last,
    .at = MOVABLE_VECTOR_at,
    
    .insertFirst = MOVABLE_VECTOR_insertFirst,
    .insertLast = MOVABLE_VECTOR_insertLast,
    .insertAt = MOVABLE_VECTOR_insertAt,
    
    .extractFirst = MOVABLE_VECTOR_extractFirst,
    .extractLast = MOVABLE_VECTOR_extractLast,
   
    .extractAt = MOVABLE_VECTOR_extractAt,
    .concat = MOVABLE_VECTOR_concat,
    .traverse = MOVABLE_VECTOR_traverse,
    .print = MOVABLE_VECTOR_print,                        
};

//Function definitions:

MovableVector* MOVABLE_VECTOR_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    MovableVector* v_temp = MM->malloc(sizeof(MovableVector));
    if (NULL == v_temp) {
        return NULL;
    }

    v_temp->storage_ = MM->malloc(sizeof(MemoryNode) * capacity* 2);
    if (NULL == v_temp->storage_) {
        MM->free(v_temp);
        return NULL;
    }

    for (s16 i = 0; i < capacity*2; i++) {
        MEMNODE_createLite(&v_temp->storage_[i]);
    }

    v_temp->tail_ = 0;
    v_temp->head_ = 0;
    v_temp->capacity_ = capacity;
    v_temp->ops_ = &movable_vector_ops;

    return v_temp;
}

s16 MOVABLE_VECTOR_reset(MovableVector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = vector->head_+ vector->capacity_/2; i < (vector->tail_)+ (vector->capacity_ / 2) + ; i++) {

        vector->storage_[i].ops_->reset(&vector->storage_[i]);
    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;
}

s16 MOVABLE_VECTOR_softReset(MovableVector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {
        vector->storage_[i].data_ = NULL;
        vector->storage_[i].size_ = 0;
    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;
}

s16 MOVABLE_VECTOR_resize(MovableVector* vector, u16 new_size) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_NodeNull;
    }

    if (0 == new_size) {
        return kErrorCode_SizeNull;
    }

    if (vector->capacity_ == new_size) {
        return kErrorCode_EqualCapacity;
    }

    u16 elements_to_copy = 0;

    if (vector->tail_ > new_size) {
        elements_to_copy = new_size;
        vector->tail_ = new_size;
    }
    else {
        elements_to_copy = vector->tail_;
    }

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * new_size);

    if (NULL == aux) {
        return kErrorCode_MallocNull;
    }

    for (u16 i = 0; i < new_size; i++) {
        MEMNODE_createLite(&aux[i]);
    }
    for (u16 i = 0; i < elements_to_copy; i++) {
        vector->storage_->ops_->memCopy(&aux[i], vector->storage_[i].data_, vector->storage_[i].size_);
    }
    for (u16 i = 0; i < vector->capacity_; i++) {
        if (NULL != vector->storage_[i].data_) {
            MM->free(vector->storage_[i].data_);
        }
    }

    MM->free(vector->storage_);
    vector->capacity_ = new_size;
    vector->storage_ = aux;

    return kErrorCode_Ok;
}

s16 MOVABLE_VECTOR_destroy(MovableVector* vector)
{
    if (NULL == vector)
    {
        return kErrorCode_VectorNull;
    }
    if (NULL == vector->storage_)
    {
        MM->free(vector);
        return kErrorCode_NodeNull;
    }
    for (u16 i = vector->head_; i < vector->tail_; i++)
    {
        if (NULL != vector->storage_[i].data_) {
            MM->free(vector->storage_[i].data_);
        }
    }
    MM->free(vector->storage_);
    MM->free(vector);

    return kErrorCode_Ok;
}

u16 MOVABLE_VECTOR_capacity(MovableVector* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->capacity_;
}

u16 MOVABLE_VECTOR_length(MovableVector* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->tail_ - vector->head_;
}

boolean MOVABLE_VECTOR_isEmpty(MovableVector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->head_ == vector->tail_) {
        return True;
    }

    return False;
}

boolean MOVABLE_VECTOR_isFull(MovableVector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->tail_ == vector->capacity_) {
        return True;
    }

    return False;
}

void* MOVABLE_VECTOR_first(MovableVector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[vector->head_].data_;
}

void* MOVABLE_VECTOR_at(MovableVector* vector, u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (position < 0) {
        return NULL;
    }

    return vector->storage_[position].data_;
}

void* MOVABLE_VECTOR_last(MovableVector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (vector->tail_ == 0) {
        return NULL;
    }

    return vector->storage_[vector->tail_ - 1].data_;
}

s16 MOVABLE_VECTOR_insertFirst(MovableVector* vector, void* data, u16 bytes) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if (vector->tail_ == vector->capacity_) {
        return kErrorCode_VectorFull;
    }

    for (u16 i = vector->tail_; i > vector->head_; i--) {
        vector->storage_[i] = vector->storage_[i - 1];
    }

    vector->storage_[vector->head_].data_ = data;
    vector->storage_[vector->head_].size_ = bytes;

    vector->tail_++;
    return  kErrorCode_Ok;
}

s16 MOVABLE_VECTOR_insertLast(MovableVector* vector, void* data, u16 bytes) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if (vector->tail_ == vector->capacity_) {
        return kErrorCode_VectorFull;
    }

    vector->storage_[vector->tail_].data_ = data;
    vector->storage_[vector->tail_].size_ = bytes;
    vector->tail_++;
    return  kErrorCode_Ok;
}

s16 MOVABLE_VECTOR_insertAt(MovableVector* vector, void* data, u16 bytes, u16 position) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if (vector->tail_ == vector->capacity_) {
        return kErrorCode_VectorFull;
    }

    if (position >= vector->tail_) {
        position = vector->tail_;
    }

    for (u16 i = vector->tail_; i > position; i--) {

        vector->storage_[i].ops_->setData(&vector->storage_[i], vector->storage_[i - 1].data_, vector->storage_[i - 1].size_);
    }

    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;

    vector->tail_++;

    return  kErrorCode_Ok;
}

void* MOVABLE_VECTOR_extractFirst(MovableVector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (MOVABLE_VECTOR_isEmpty(vector)) {

        return NULL;
    }

    void* tmp = vector->storage_[vector->head_].data_;

    for (u16 i = vector->head_ + 1; i < vector->tail_; i++) {

        vector->storage_[i - 1] = vector->storage_[i];
    }


    vector->tail_--;

    return tmp;
}

void* MOVABLE_VECTOR_extractLast(MovableVector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (MOVABLE_VECTOR_isEmpty(vector)) {

        return  NULL;
    }

    if (vector->tail_ <= 0) {

        return  NULL;
    }

    void* tmp = vector->storage_[vector->tail_ - 1].data_;

    //vector->storage_[vector->tail_-1].ops_->softReset(&vector->storage_[vector->tail_-1]);
    vector->tail_--;

    return tmp;
}

void* MOVABLE_VECTOR_extractAt(MovableVector* vector, u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (MOVABLE_VECTOR_isEmpty(vector)) {

        return NULL;
    }

    void* tmp = NULL;

    if (position >= vector->tail_) {

        position = vector->tail_;
        tmp = vector->storage_[position - 1].data_;
    }
    else {

        tmp = vector->storage_[position].data_;
    }



    for (u16 i = position; i < vector->tail_; i++) {

        vector->storage_[i] = vector->storage_[i + 1];
    }

    //vector->storage_[vector->tail_-1].ops_->softReset(&vector->storage_[vector->tail_ - 1]);
    vector->tail_--;

    return tmp;
}

s16 MOVABLE_VECTOR_traverse(MovableVector* vector, void (*callback)(MemoryNode*)) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        callback(&vector->storage_[i]);
    }

    return kErrorCode_Ok;
}


s16 MOVABLE_VECTOR_concat(MovableVector* vector, MovableVector * vector_src)
{
    if (NULL == vector || NULL == vector_src)
    {
        return kErrorCode_VectorNull;
    }
    if (NULL == vector->storage_ || NULL == vector_src->storage_)
    {
        return kErrorCode_NodeNull;
    }
    u16 new_capacity = vector->capacity_ + vector_src->capacity_;
    vector->ops_->resize(vector, new_capacity);
    u16 index = vector->tail_;
    for (u16 i = 0; i < vector_src->tail_; i++) {
        vector->storage_->ops_->memCopy(&vector->storage_[index], vector_src->storage_[i].data_, vector_src->storage_[i].size_);
        index++;
    }
    vector->tail_ += vector_src->tail_;
    return kErrorCode_Ok;
}

void MOVABLE_VECTOR_print(MovableVector* vector) {
    if (NULL == vector) {
        printf("\t[MovableVector Info] vector: NULL\n");
        return;
    }

    printf("\t[MovableVector info] Address: %p\n", vector);
    printf("\t[MovableVector info] Head: %d\n", vector->head_);
    printf("\t[MovableVector info] Tail: %d\n", vector->tail_);
    printf("\t[MovableVector info] Capacity: %d\n", vector->capacity_);
    printf("\t[MovableVector info] Address: %p\n", vector->ops_);

    if (NULL == vector->storage_) {
        printf("\t[Storage Info] vector storage: NULL\n");
        return;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {
        printf("\t  [MovableVector Info] storage: #%d\n", i);
        printf("\t      [Node info] Address: %p\n", &(vector->storage_[i]));
        printf("\t      [Node info] Size: %d\n", vector->storage_[i].size_);
        printf("\t      [Node info] Data Address: %p\n", vector->storage_[i].data_);
        printf("\t      [Node info] Data Content: ");

        u8* aux = (u8*)vector->storage_[i].data_;
        for (int j = 0; j < vector->storage_[i].size_; j++) {
            printf("%c", aux[j]);
        }
        printf("\n");
    }
}


