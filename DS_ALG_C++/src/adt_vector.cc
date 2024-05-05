/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

adt_vector_s::adt_vector_s(u16 capacity){
    head_ = 0;
    tail_ = 0;
    if (capacity > 0) {
        storage_ = new memory_node_s[capacity];
    }
    else {

        storage_ = NULL;
    }
    capacity_ = capacity;
}

adt_vector_s::~adt_vector_s() {}

/*adt_vector_s* VECTOR_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    adt_vector_s* v_temp = new adt_vector_s;
    if (NULL == v_temp) {
        return NULL;
    }

    v_temp->storage_ = new memory_node_s[capacity];
    if (NULL == v_temp->storage_) {
        delete v_temp;
        return NULL;
    }

    for (s16 i = 0; i < capacity; i++) {
        MEMNODE_createLite(&v_temp->storage_[i]);
    }

    v_temp->tail_ = 0;
    v_temp->head_ = 0;
    v_temp->capacity_ = capacity;

    return v_temp;
}*/

s16 adt_vector_s::reset(adt_vector_s* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        vector->storage_[i].reset(&vector->storage_[i]);
    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;
}

s16 adt_vector_s::softReset(adt_vector_s* vector) {

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
                                      
s16 adt_vector_s::resize(adt_vector_s* vector, u16 new_size) {
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
    }else {
        elements_to_copy = vector->tail_;
    }

    memory_node_s* aux = new memory_node_s[new_size];

    if (NULL == aux) {
        return kErrorCode_MallocNull;
    }

    for (u16 i = 0; i < new_size; i++) {
        MEMNODE_createLite(&aux[i]);
    }
    for (u16 i = 0; i < elements_to_copy; i++) {
        vector->storage_->memCopy(&aux[i], vector->storage_[i].data_, vector->storage_[i].size_);
    }
    for (u16 i = 0; i < vector->capacity_; i++) {
        if (NULL != vector->storage_[i].data_) {
            delete vector->storage_[i].data_;
        }
    }

    delete[] vector->storage_;
    vector->capacity_ = new_size;
    vector->storage_ = aux;

    return kErrorCode_Ok;
}

s16 adt_vector_s::destroy(adt_vector_s* vector)
{
    if (NULL == vector)
    {
        return kErrorCode_VectorNull;
    }
    if (NULL == vector->storage_)
    {
        delete vector;
        return kErrorCode_NodeNull;
    }
    for (u16 i = vector->head_; i < vector->tail_; i++)
    {
        if (NULL != vector->storage_[i].data_) {
            delete vector->storage_[i].data_;
        }
    }
    delete[] vector->storage_;
    delete vector;

    return kErrorCode_Ok;
}

u16 adt_vector_s::capacity(adt_vector_s* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->capacity_;
}

u16 adt_vector_s::length(adt_vector_s* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->tail_- vector->head_;
}

boolean adt_vector_s::isEmpty(adt_vector_s* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->head_ == vector->tail_) {
        return True;
    }

    return False;
}

boolean adt_vector_s::isFull(adt_vector_s* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->tail_ == vector->capacity_) {
        return True;
    }

    return False;
}

void* adt_vector_s::first(adt_vector_s* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[vector->head_].data_;
}

void* adt_vector_s::at(adt_vector_s* vector,u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (position < 0){
        return NULL;
    }

    return vector->storage_[position].data_;
}

void* adt_vector_s::last(adt_vector_s* vector) {

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

s16 adt_vector_s::insertFirst(adt_vector_s* vector, void* data, u16 bytes) {

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

s16 adt_vector_s::insertLast(adt_vector_s* vector, void* data, u16 bytes) {

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

s16 adt_vector_s::insertAt(adt_vector_s* vector, void* data, u16 bytes,u16 position) {

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

        vector->storage_[i].setData(&vector->storage_[i], vector->storage_[i - 1].data_, vector->storage_[i - 1].size_);
    }

    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;

    vector->tail_++;

    return  kErrorCode_Ok;
}

void* adt_vector_s::extractFirst(adt_vector_s* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (isEmpty(vector)) {

        return NULL;
    }

    void* tmp = vector->storage_[vector->head_].data_;

    for(u16 i = vector->head_+1; i < vector->tail_; i++) {

        vector->storage_[i-1] = vector->storage_[i];
    }

    vector->tail_--;

    return tmp;
}

void* adt_vector_s::extractLast(adt_vector_s* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (isEmpty(vector)) {
        return  NULL;
    }

    if (vector->tail_<=0) {
        return  NULL;
    }

    void* tmp = vector->storage_[vector->tail_-1].data_;

    vector->tail_--;

    return tmp;
}

void* adt_vector_s::extractAt(adt_vector_s* vector, u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (NULL == vector->storage_->data_) {
        return NULL;
    }

    if (isEmpty(vector)) {
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

    vector->tail_--;

    return tmp;
}

s16 adt_vector_s::traverse(adt_vector_s* vector, void (*callback)(memory_node_s*)){
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

s16 adt_vector_s::concat(adt_vector_s* vector, adt_vector_s* vector_src)
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
    vector->resize(vector, new_capacity);
    u16 index = vector->tail_;
    for (u16 i = 0; i < vector_src->tail_; i++) {
        vector->storage_->memCopy(&vector->storage_[index], vector_src->storage_[i].data_, vector_src->storage_[i].size_);
        index++;
    }
    vector->tail_ += vector_src->tail_;
    return kErrorCode_Ok;
}

void adt_vector_s::print(adt_vector_s* vector) {
    if (NULL == vector) {
        printf("\t[Vector Info] vector: NULL\n");
        return;
    }

    printf("\t[Vector info] Address: %p\n", vector);
    printf("\t[Vector info] Head: %d\n", vector->head_);
    printf("\t[Vector info] Tail: %d\n", vector->tail_);
    printf("\t[Vector info] Capacity: %d\n", vector->capacity_);
    printf("\t[Vector info] Address: %p\n", &vector);

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


