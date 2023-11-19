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
static Vector* VECTOR_create(u16 capacity);
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
    if (0 <= capacity) {
        return kErrorCode_CapacityZero;
    }

    Vector* v_temp = MM->malloc(sizeof(Vector));
    if (NULL == v_temp) {
        return kErrorCode_MallocNull;
    }

    v_temp->storage_ = MM->malloc(sizeof(MemoryNode) * capacity);
    if (NULL == v_temp->storage_) {
        MM->free(v_temp);
        return kErrorCode_MallocNull;
    }

    for (s16 i = 0; i < v_temp->tail_; i++) {
        MEMNODE_createLite(&v_temp->storage_[i]);
    }

    v_temp->tail_ = 0;
    v_temp->head_ = 0;
    v_temp->capacity_ = capacity;

    return v_temp;
}

s16 VECTOR_reset(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        MEMNODE_reset(vector->storage_[i]);

    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;

}

s16 VECTOR_softReset(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {
        vector->storage_[i].data_ = NULL;
        vector->storage_[i].size_ = 0;
    }
    vector->tail_ = 0;

    return  kErrorCode_Ok;
}
                                      

s16 VECTOR_resize(Vector* vector, u16 new_size) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    MemoryNode* tmp = MM->malloc(sizeof(MemoryNode) * new_size);
    
    for (s16 i = 0; i < new_size; i++) {

        MEMNODE_createLite(&tmp[i]);

    }
    vector->tail_ = new_size;

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        tmp[i] = vector->storage_[i];

    }

    for (s16 i = vector->tail_; i < vector->capacity_; i++) {

        MEMNODE_reset(vector->storage_[i]);

    }


    MM->free(vector->storage_);

    vector->capacity_ = new_size;

    return  kErrorCode_Ok;
}

s16 VECTOR_destroy(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    

    for (s16 i = 0; i < vector->tail_; i++) {
        if (&vector->storage_[i].data_ != NULL) {
            MM->free(&vector->storage_[i].data_);
        }
        else {
            return kErrorCode_Data_StorageNull;
        }
    }
    
    MM->free(&vector->storage_);
    
    MM->free(vector);

    return kErrorCode_Ok;
}

u16 VECTOR_capacity(Vector* vector) {
    if (NULL == vector) {
        return 0;
    }

    return vector->capacity_;
}

u16 VECTOR_length(Vector* vector) {
    if (NULL == vector) {
        return 0;
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

    return 0;
}

boolean VECTOR_isFull(Vector* vector) {
    if (NULL == vector) {
        return False;
    }

    if (vector->tail_ == vector->capacity_) {
        return True;
    }

    return 0;
}


void* VECTOR_first(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    return &vector->storage_[vector->head_].data_;


}

void* VECTOR_at(Vector* vector,u16 position) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    return &vector->storage_[position].data_;


}

void* VECTOR_last(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    return &vector->storage_[vector->tail_].data_;


}

s16 VECTOR_insertFirst(Vector* vector, void* data, u16 bytes) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
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
    
    vector->tail_++;

    for (s16 i = vector->tail_; i < vector->head_; i--) {

        vector->storage_[i] = vector->storage_[i-1];

       

    }

    vector->storage_[vector->head_].data_ = data;
    vector->storage_[vector->head_].size_ = bytes;

    
    return  kErrorCode_Ok;


}


s16 VECTOR_insertLast(Vector* vector, void* data, u16 bytes) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
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

    vector->tail_++;

    vector->storage_[vector->tail_].data_ = data;
    vector->storage_[vector->tail_].size_ = bytes;

      
    return  kErrorCode_Ok;


}

s16 VECTOR_insertAt(Vector* vector, void* data, u16 bytes,u16 position) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if (position > vector->tail_) {

        position = vector->tail_;
    }

    vector->tail_++;

    
    for (s16 i = vector->tail_; i < position; i--) {

        vector->storage_[i] = vector->storage_[i - 1];
      
    }

    vector->storage_[position].data_ = data;
    vector->storage_[position].size_ = bytes;


    return  kErrorCode_Ok;


}

void* VECTOR_extractFirst(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    if (NULL == vector->storage_[vector->head_].data_) {
        return kErrorCode_DataNull;
    }

    if (VECTOR_isEmpty(vector)) {

        return kErrorCode_VectorEmpty;
    }

    void* tmp = vector->storage_[vector->head_].data_;

    vector->tail_--;
    

    for (s16 i = vector->tail_; i < vector->head_; i--) {

        vector->storage_[i] = vector->storage_[i - 1];

    }

    MEMNODE_softReset(vector->storage_[vector->tail_]);

    return tmp;



}

void* VECTOR_extractLast(Vector* vector) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    if (NULL == vector->storage_->data_) {
        return kErrorCode_DataNull;
    }

    if (VECTOR_isEmpty(vector)) {

        return kErrorCode_VectorEmpty;
    }

    if (vector->tail_<=0) {

        return kErrorCode_TailZero;
    }

    void* tmp = vector->storage_[vector->tail_].data_;

    vector->tail_--;


    MEMNODE_softReset(vector->storage_[vector->tail_]);

    return tmp;



}


void* VECTOR_extractAt(Vector* vector, u16 position) {

    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    if (NULL == vector->storage_->data_) {
        return kErrorCode_DataNull;
    }

    if (VECTOR_isEmpty(vector)) {

        return kErrorCode_VectorEmpty;
    }

    if (position > vector->tail_) {

        position = vector->tail_;
    }

    void* tmp = vector->storage_[position].data_;
    
    vector->tail_--;

    for (s16 i = vector->tail_; i < position; i--) {
        
        vector->storage_[i] = vector->storage_[i - 1];
        
    }

    MEMNODE_softReset(vector->storage_[vector->tail_]);

    return tmp;

}

s16 VECTOR_traverse(Vector* vector, void (*callback)(MemoryNode*)){
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_) {
        return kErrorCode_StrorageNull;
    }

    for (s16 i = vector->head_; i < vector->tail_; i++) {

        callback(&vector->storage_[i]);

    }

    return kErrorCode_Ok;

}

s16 VECTOR_concat(Vector* vector, Vector* vector_src) {
    if (NULL == vector && NULL == vector_src) {
        return kErrorCode_VectorNull;
    }

    if (NULL == vector->storage_ && NULL == vector_src->storage_) {
        return kErrorCode_StrorageNull;
    }

    MemoryNode* tmp = MM->malloc(sizeof(MemoryNode) * (vector->capacity_ + vector_src->capacity_));
    if (NULL == tmp) {
        return kErrorCode_MallocNull;
    }
    MEMNODE_createLite(tmp);

    MEMNODE_SetData(&tmp, &vector->storage_->data_, vector->storage_->size_);
    MEMNODE_memConcat(&tmp, &vector_src->storage_->data_, vector_src->storage_->size_);

    vector_src->storage_ = tmp;
    vector_src->tail_ += vector->tail_;
    vector_src->capacity_ += vector->capacity_;
    MM->free(vector);

    return kErrorCode_Ok;
}

void VECTOR_print(Vector* vector) {
    if (NULL == vector) {
        printf("\t[Vector Info] vector: NULL\n");
        return;
    }

    if (NULL == vector->storage_) {
        printf("\t[Storage Info] vector storage: NULL\n");
        return;
    }

    printf("\t[Vector info] Address: %p\n", vector);
    printf("\t[Vector info] Head: %d\n", vector->head_);
    printf("\t[Vector info] Tail: %d\n", vector->tail_);
    printf("\t[Vector info] Capacity: %d\n", vector->capacity_);
    printf("\t[Vector info] Address: %p\n", vector->ops_);

    for (s16 i = vector->head_; vector->tail_; i++) {
        printf("\t[Node info] Storgae: %d\n", i);
        printf("\t[Node info] Address: %p\n", vector->storage_[i]);
        printf("\t[Node info] Size: %p\n", vector->storage_[i].size_);
        printf("\t[Node info] Data: %p\n", vector->storage_[i].data_);

        printf("\t[Node info] Data Content: ");
        u8* aux = (u8*)vector->storage_[i].data_;
        for (int i = 0; i < vector->storage_[i].size_; i++) {
            printf("%c\n", aux[i]);
        }
        printf("\t[Node info] Next Address: %p\n", vector->storage_[i].ops_);
    }
}
