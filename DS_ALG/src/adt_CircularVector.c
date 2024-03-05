/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_CircularVector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

//Static prototipes
static s16 C_VECTOR_destroy(C_Vector* vector);
static s16 C_VECTOR_softReset(C_Vector* vector);
static s16 C_VECTOR_reset(C_Vector* vector);
static s16 C_VECTOR_resize(C_Vector* vector, u16 new_size);
static u16 C_VECTOR_capacity(C_Vector* vector);
static u16 C_VECTOR_length(C_Vector* vector);
static boolean C_VECTOR_isEmpty(C_Vector* vector);
static boolean C_VECTOR_isFull(C_Vector* vector);
static void* C_VECTOR_first(C_Vector* vector);
static void* C_VECTOR_at(C_Vector* vector,u16 position);
static void* C_VECTOR_last(C_Vector* vector);
static s16 C_VECTOR_insertFirst(C_Vector* vector, void* data, u16 bytes);
static s16 C_VECTOR_insertLast(C_Vector* vector, void* data, u16 bytes);
static s16 C_VECTOR_insertAt(C_Vector* vector, void* data, u16 bytes,u16 position);
static void* C_VECTOR_extractFirst(C_Vector* vector);
static void* C_VECTOR_extractLast(C_Vector* vector);
static void* C_VECTOR_extractAt(C_Vector* vector, u16 position);
static s16 C_VECTOR_traverse(C_Vector* vector, void (*callback)(MemoryNode*));
static s16 C_VECTOR_concat(C_Vector* vector, C_Vector* vector_src);
static void C_VECTOR_print(C_Vector* vector);

// Memory Node's API Definitions
struct vector_ops_s vector_ops = {
    .destroy = C_VECTOR_destroy,
    .softReset = C_VECTOR_softReset,
    .reset = C_VECTOR_reset,
    .resize = C_VECTOR_resize,
    .capacity = C_VECTOR_capacity,
    .length = C_VECTOR_length,
    .isEmpty = C_VECTOR_isEmpty,
    .isFull = C_VECTOR_isFull,
    .first = C_VECTOR_first,
    .last = C_VECTOR_last,
    .at = C_VECTOR_at,
    
    .insertFirst = C_VECTOR_insertFirst,
    .insertLast = C_VECTOR_insertLast,
    .insertAt = C_VECTOR_insertAt,
    
    .extractFirst = C_VECTOR_extractFirst,
    .extractLast = C_VECTOR_extractLast,
   
    .extractAt = C_VECTOR_extractAt,
    .concat = C_VECTOR_concat,
    .traverse = C_VECTOR_traverse,
    .print = C_VECTOR_print,
};

//Function definitions:

C_Vector* VECTOR_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    C_Vector* v_temp = MM->malloc(sizeof(C_Vector));
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

s16 C_VECTOR_reset(C_Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return kErrorCode_Ok;
    }

    

    if (vector->head_ < vector->tail_) {
       
        for (u16 i = vector->head_; i < vector->tail_; i++) {
            vector->storage_[i].ops_->reset(&vector->storage_[i]);
        }
    }
    else {
       
        for (u16 i = vector->head_; i < vector->capacity_; i++) {
            vector->storage_[i].ops_->reset(&vector->storage_[i]);
        }
        for (u16 i = 0; i < vector->tail_; i++) {
            vector->storage_[i].ops_->reset(&vector->storage_[i]);
        }
    }

    vector->tail_ = 0;
    vector->head_ = 0;
    return kErrorCode_Ok;
}

s16 C_VECTOR_softReset(C_Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return kErrorCode_Ok; 
    }

    s16 start = vector->head_;
    s16 end = vector->tail_;

    if (start < end) {
       
        for (s16 i = start; i < end; i++) {
            vector->storage_[i].data_ = NULL;
            vector->storage_[i].size_ = 0;
        }
    }
    else {
       
        for (s16 i = start; i < vector->capacity_; i++) {
            vector->storage_[i].data_ = NULL;
            vector->storage_[i].size_ = 0;
        }
        for (s16 i = 0; i < end; i++) {
            vector->storage_[i].data_ = NULL;
            vector->storage_[i].size_ = 0;
        }
    }

    vector->tail_ =0;
    vector->head_ = 0;
    return kErrorCode_Ok;
}
                                      
s16 C_VECTOR_resize(C_Vector* vector, u16 new_size) {
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

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * new_size);

    if (NULL == aux) {
        return kErrorCode_MallocNull;
    }

   u16 elements_to_copy;
       
   if (new_size < vector->capacity_) {
       elements_to_copy = new_size;
   }
   else {
       elements_to_copy = vector->capacity_;
   }

    
    for (u16 i = 0; i < elements_to_copy; i++) {
        u16 index = (vector->head_ + i) % vector->capacity_; 
        aux[i].data_ = vector->storage_[index].data_;
        aux[i].size_ = vector->storage_[index].size_;
    }

    
    for (u16 i = 0; i < vector->capacity_; i++) {
        if (NULL != vector->storage_[i].data_) {
            MM->free(vector->storage_[i].data_);
        }
    }

    MM->free(vector->storage_);

   
    vector->capacity_ = new_size;
    vector->head_ = 0;
    vector->tail_ = elements_to_copy;
    vector->storage_ = aux;

    return kErrorCode_Ok;
}

s16 C_VECTOR_destroy(C_Vector* vector)
{
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }
    if (NULL == vector->storage_) {
        MM->free(vector);
        return kErrorCode_NodeNull;
    }
    if (C_VECTOR_isEmpty(vector)) {
        MM->free(vector->storage_);
        MM->free(vector);
        return kErrorCode_Ok;
    }

    s16 start = vector->head_;
    s16 end = vector->tail_;

    if (start < end) {
       
        for (s16 i = start; i < end; i++) {
            if (NULL != vector->storage_[i].data_) {
                MM->free(vector->storage_[i].data_);
            }
        }
    }
    else {
   
        for (s16 i = start; i < vector->capacity_; i++) {
            if (NULL != vector->storage_[i].data_) {
                MM->free(vector->storage_[i].data_);
            }
        }
        for (s16 i = 0; i < end; i++) {
            if (NULL != vector->storage_[i].data_) {
                MM->free(vector->storage_[i].data_);
            }
        }
    }

    MM->free(vector->storage_);
    MM->free(vector);

    return kErrorCode_Ok;
}

u16 C_VECTOR_capacity(C_Vector* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->capacity_;
}

u16 C_VECTOR_length(C_Vector* vector) {
    if (NULL == vector) {
        return 0;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return 0; 
    }

    if (vector->head_ <= vector->tail_) {
        
        return vector->tail_ - vector->head_;
    }
    else {
       
        return vector->capacity_ - vector->head_ + vector->tail_;
    }
}

boolean C_VECTOR_isEmpty(C_Vector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->head_ == vector->tail_) {
        return True;
    }

    return False;
}

boolean C_VECTOR_isFull(C_Vector* vector) {
    if (NULL == vector) {
        return False; 
    }

    if ((vector->tail_ + 1) % vector->capacity_ == vector->head_) {
        return True;
    }

    return False; 
}

void* C_VECTOR_first(C_Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    return vector->storage_[vector->head_].data_;
}

void* C_VECTOR_at(C_Vector* vector,u16 position) {

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

void* C_VECTOR_last(C_Vector* vector) {

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

s16 C_VECTOR_insertFirst(C_Vector* vector, void* data, u16 bytes) {

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

    if (C_VECTOR_isFull(vector)) {
        return kErrorCode_VectorFull;
    }

    
    s16 position = (vector->head_ - 1 + vector->capacity_) % vector->capacity_;

    /*
    for (s16 i = vector->tail_; i > position; i--) {
        s16 current_index = (i + vector->capacity_) % vector->capacity_;
        s16 previous_index = (current_index - 1 + vector->capacity_) % vector->capacity_;
        vector->storage_[current_index] = vector->storage_[previous_index];
    }
    */
    
    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;

    
    vector->head_ = position;
    

    return kErrorCode_Ok;
}

s16 C_VECTOR_insertLast(C_Vector* vector, void* data, u16 bytes) {

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

    if (C_VECTOR_isFull(vector)) {
        return kErrorCode_VectorFull;
    }

    
    s16 position = vector->tail_;

    
    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;

    
    vector->tail_ = (vector->tail_ + 1) % vector->capacity_;

    return kErrorCode_Ok;
}

s16 C_VECTOR_insertAt(C_Vector* vector, void* data, u16 bytes,u16 position) {

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

    if (C_VECTOR_isFull(vector)) {
        return kErrorCode_VectorFull;
    }

    if (position > vector->tail_) {

        position = vector->tail_;
    }
    
    if (position >= vector->head_) {

        for (s16 i = vector->head_; i <= position; i++) {

            vector->storage_[i - 1] = vector->storage_[i];
        }
        vector->storage_[position].data_ = data;
        vector->storage_[position].size_ = bytes;
        vector->head_--;
    }
    else {
      
           for(s16 i = vector->tail_; i >= position; i--) {

               vector->storage_[i + 1] = vector->storage_[i];
           }
           vector->storage_[position].data_ = data;
           vector->storage_[position].size_ = bytes;
           vector->tail_++;
   
        

    }
   

    return kErrorCode_Ok;
}

void* C_VECTOR_extractFirst(C_Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return NULL;
    }

    
    void* tmp = vector->storage_[vector->head_].data_;

   
    for (u16 i = vector->head_ + 1; i < vector->tail_; i++) {
        s16 current_index = (i + vector->capacity_) % vector->capacity_;
        s16 previous_index = (current_index - 1 + vector->capacity_) % vector->capacity_;
        vector->storage_[previous_index] = vector->storage_[current_index];
    }

    
    vector->tail_ = (vector->tail_ - 1 + vector->capacity_) % vector->capacity_;

    return tmp;
}

void* C_VECTOR_extractLast(C_Vector* vector) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return NULL;
    }

    
    void* tmp = vector->storage_[(vector->tail_ - 1 + vector->capacity_) % vector->capacity_].data_;

   
    vector->tail_ = (vector->tail_ - 1 + vector->capacity_) % vector->capacity_;

    return tmp;
}

void* C_VECTOR_extractAt(C_Vector* vector, u16 position) {

    if (NULL == vector) {
        return NULL;
    }

    if (NULL == vector->storage_) {
        return NULL;
    }

    if (C_VECTOR_isEmpty(vector)) {
        return NULL;
    }

    
    if (position >= vector->tail_) {
        return NULL; 
    }

    
    void* tmp = vector->storage_[position].data_;

    
    for (u16 i = position; i < vector->tail_ - 1; i++) {
        s16 current_index = (i + vector->capacity_) % vector->capacity_;
        s16 next_index = (current_index + 1) % vector->capacity_;
        vector->storage_[current_index] = vector->storage_[next_index];
    }

   
    vector->tail_ = (vector->tail_ - 1 + vector->capacity_) % vector->capacity_;

    return tmp;
}

s16 C_VECTOR_traverse(C_Vector* vector, void (*callback)(MemoryNode*)){
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StorageNull;
    }

   
    u16 elements_to_traverse = C_VECTOR_length(vector);

    
    for (u16 i = 0; i < elements_to_traverse; i++) {
       
        u16 current_index = (vector->head_ + i) % vector->capacity_;
       
        callback(&vector->storage_[current_index]);
    }

    return kErrorCode_Ok;
}

s16 C_VECTOR_concat(C_Vector* vector, C_Vector* vector_src)
{
    if (NULL == vector || NULL == vector_src) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_ || NULL == vector_src->storage_) {
        return kErrorCode_NodeNull;
    }

  
    u16 new_capacity = vector->capacity_ + vector_src->capacity_;

    
    vector->ops_->resize(vector, new_capacity);

   
    u16 index = vector->tail_;

    
    for (u16 i = 0; i < vector_src->tail_; i++) {
      
        u16 current_index = (vector->tail_ + i) % vector->capacity_;
       
        vector->storage_[current_index].ops_->setData(&vector->storage_[current_index], vector_src->storage_[i].data_, vector_src->storage_[i].size_);
    }

    
    vector->tail_ = (vector->tail_ + vector_src->tail_) % vector->capacity_;

    return kErrorCode_Ok;
}

void C_VECTOR_print(C_Vector* vector) {
    if (NULL == vector) {
        printf("\t[Vector Info] vector: NULL\n");
        return;
    }

    printf("\t[Vector info] Address: %p\n", vector);
    printf("\t[Vector info] Head: %d\n", vector->head_);
    printf("\t[Vector info] Tail: %d\n", vector->tail_);
    printf("\t[Vector info] Length: %d\n", C_VECTOR_length(vector));
    printf("\t[Vector info] Capacity: %d\n", vector->capacity_);
    printf("\t[Vector info] Address: %p\n", vector->ops_);

    if (NULL == vector->storage_) {
        printf("\t[Storage Info] vector storage: NULL\n");
        return;
    }

    
    u16 elements_to_print = C_VECTOR_length(vector);

    
    for (u16 i = 0; i < elements_to_print; i++) {
       
        u16 current_index = (vector->head_ + i) % vector->capacity_;

        printf("\t  [Vector Info] storage: #%d\n", current_index);
        printf("\t      [Node info] Address: %p\n", &(vector->storage_[current_index]));
        printf("\t      [Node info] Size: %d\n", vector->storage_[current_index].size_);
        printf("\t      [Node info] Data Address: %p\n", vector->storage_[current_index].data_);
        printf("\t      [Node info] Data Content: ");

        u8* aux = (u8*)vector->storage_[current_index].data_;
        for (int j = 0; j < vector->storage_[current_index].size_; j++) {
            printf("%c", aux[j]);
        }
        printf("\n");
    }
}

