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
    .concat = VECTOR_concat;
    .traverse = VECTOR_traverse;
    .print = VECTOR_print;

                                             
};

//Function definitions:
