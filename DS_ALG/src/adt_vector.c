/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

//Static prototipes
static s16 VECTOR_destroy(Vector* vector);
static s16 VECTOR_softReset(Vector* vector);
static s16 VECTOR_reset(Vector* vector);
static s16 VECTOR_resize(Vector* vector, u16 new_size);
static u16 VECTOR_capacity(Vector* vector);
static u16 VECTOR_length(Vector* vector);
static boolean VECTOR_isEmpty(Vector* vector);
static boolean VECTOR_isFull(Vector* vector);
static void* VECTOR_first(Vector* vector);
static void* VECTOR_at(Vector* vector,u16 position);
static void* VECTOR_last(Vector* vector);
static s16 VECTOR_insertFirst(Vector* vector, void* data, u16 bytes);
static s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes);
static s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes,u16 position);
static void* VECTOR_extractFirst(Vector* vector);
static void* VECTOR_extractLast(Vector* vector);
static void* VECTOR_extractAt(Vector* vector, u16 position);
static s16 VECTOR_traverse(Vector* vector, void (*callback)(MemoryNode*));
static s16 VECTOR_concat(Vector* vector, Vector* vector_src);
static void VECTOR_print(Vector* vector);

// Memory Node's API Definitions
struct vector_ops_s vector_ops = {
    .destroy = VECTOR_destroy,
    .softReset = VECTOR_softReset,
    .reset = VECTOR_reset,
    .resize = VECTOR_resize,
    .capacity = VECTOR_capacity,
    .length = VECTOR_length,
    .isEmpty = VECTOR_isEmpty,
    .isFull = VECTOR_isFull,
    .first = VECTOR_first,
    .last = VECTOR_last,
    .at = VECTOR_at,
    
    .insertFirst = VECTOR_insertFirst,
    .insertLast = VECTOR_insertLast,
    .insertAt = VECTOR_insertAt,
    
    .extractFirst = VECTOR_extractFirst,
    .extractLast = VECTOR_extractLast,
   
    .extractAt = VECTOR_extractAt,
    .concat = VECTOR_concat,
    .traverse = VECTOR_traverse,
    .print = VECTOR_print,

                                             
};

//Function definitions:

Vector* VECTOR_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Vector* v_temp = MM->malloc(sizeof(Vector));
    if (NULL == v_temp) {
        return NULL;
    }

    v_temp->storage_ = MM->malloc(sizeof(MemoryNode) * capacity);
    if (NULL == v_temp->storage_) {
        MM->free(v_temp);
        return NULL;
    }

    for (s16 i = 0; i < capacity; i++) {
        MEMNODE_createLite(&v_temp->storage_[i]);
    }

    v_temp->tail_ = 0;
    v_temp->head_ = 0;
    v_temp->capacity_ = capacity;
    v_temp->ops_ = &vector_ops;

    return v_temp;
}

s16 VECTOR_reset(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        vector->storage_[i].ops_->reset(&vector->storage_[i]);
    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;
}

s16 VECTOR_softReset(Vector* vector) {

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
                                      
//revisar
s16 VECTOR_resize(Vector* vector, u16 new_size) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }
    if (NULL == vector->storage_) {
        return kErrorCode_NodeNull;
    }
    if (0 == new_size) {
        return kErrorCode_SizeNull;
    }
    u16 top = 0;
    if (vector->tail_ > new_size) {
        top = new_size;
        vector->tail_ = new_size;
    }
    else {
        top = vector->tail_;
    }
    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * new_size);
    for (u16 i = 0; i < new_size; i++) {
        MEMNODE_createLite(&aux[i]);
    }
    for (u16 i = 0; i < top; i++) {
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


s16 VECTOR_destroy(Vector* vector)
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

u16 VECTOR_capacity(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    return vector->capacity_;
}

u16 VECTOR_length(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    return vector->tail_- vector->head_;
}

boolean VECTOR_isEmpty(Vector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->head_ == vector->tail_) {
        return True;
    }

    return False;
}

boolean VECTOR_isFull(Vector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->tail_ == vector->capacity_) {
        return True;
    }

    return False;
}

void* VECTOR_first(Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[vector->head_].data_;
}

void* VECTOR_at(Vector* vector,u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[position].data_;
}

void* VECTOR_last(Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[vector->tail_ - 1].data_;
}

s16 VECTOR_insertFirst(Vector* vector, void* data, u16 bytes) {

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

s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes) {

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

s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes,u16 position) {

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
        position = vector->tail_ ;
    }

    for (u16 i = vector->tail_; i > position; i--) {

        vector->storage_[i].ops_->setData(&vector->storage_[i], vector->storage_[i - 1].data_, vector->storage_[i - 1].size_);
    }

    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;

    vector->tail_++;

    return  kErrorCode_Ok;
}

void* VECTOR_extractFirst(Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (VECTOR_isEmpty(vector)) {

        return NULL;
    }

    void* tmp = vector->storage_[vector->head_].data_;

    for(u16 i = vector->head_+1; i < vector->tail_; i++) {

        vector->storage_[i-1] = vector->storage_[i];
    }

    
    vector->tail_--;

    return tmp;
}

void* VECTOR_extractLast(Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (VECTOR_isEmpty(vector)) {

        return  NULL;
    }

    if (vector->tail_<=0) {

        return  NULL;
    }

    void* tmp = vector->storage_[vector->tail_-1].data_;

    //vector->storage_[vector->tail_-1].ops_->softReset(&vector->storage_[vector->tail_-1]);
    vector->tail_--;

    return tmp;
}

void* VECTOR_extractAt(Vector* vector, u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (VECTOR_isEmpty(vector)) {

        return NULL;
    }

    void* tmp = NULL;

    if (position >= vector->tail_) {

        position = vector->tail_ ;
         tmp = vector->storage_[position-1].data_;
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


s16 VECTOR_traverse(Vector* vector, void (*callback)(MemoryNode*)){
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

s16 VECTOR_concat(Vector* vector, Vector* vector_src)
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


//revisar
void VECTOR_print(Vector* vector) {
    if (NULL == vector) {
        printf("\t[Vector Info] vector: NULL\n");
        return;
    }

    printf("\t[Vector info] Address: %p\n", vector);
    printf("\t[Vector info] Head: %d\n", vector->head_);
    printf("\t[Vector info] Tail: %d\n", vector->tail_);
    printf("\t[Vector info] Capacity: %d\n", vector->capacity_);
    printf("\t[Vector info] Address: %p\n", vector->ops_);

    if (NULL == vector->storage_) {
        printf("\t[Storage Info] vector storage: NULL\n");
        return;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {
        printf("\t  [Vector Info] storage: #%d\n", i);
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

