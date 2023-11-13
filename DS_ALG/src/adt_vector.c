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
    /*.first = VECTOR_first,
    .last = VECTOR_last,
    .at = VECTOR_at,
    .insertFirst = VECTOR_insertFirst,
    .insertLast = VECTOR_insertLast,
    .insertAt = VECTOR_insertAt,
    .extractFirst = VECTOR_extractFirst,
    .extractLast = VECTOR_extractLast,
    .extractAt = VECTOR_extractAt,
    .concat = VECTOR_concat;
    .traverse = VECTOR_traverse;
    .print = VECTOR_print;*/

                                             
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

s16 VECTOR_destroy(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    for (s16 i = 0; vector->tail_; i++) {
        MM->free(&vector->storage_[i].data_);
    }
    for (s16 i = 0; vector->capacity_; i++) {
        MM->free(&vector->storage_[i]);
    }
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

    return vector->tail_;
}

boolean VECTOR_isEmpty(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (vector->head_ == vector->tail_) {
        return 1;
    }

    return 0;
}

boolean VECTOR_isFull(Vector* vector) {
    if (NULL == vector) {
        return kErrorCode_VectorNull;
    }

    if (vector->tail_ == vector->capacity_) {
        return 1;
    }

    return 0;
}