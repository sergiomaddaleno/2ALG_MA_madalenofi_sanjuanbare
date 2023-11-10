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

// Memory Node's API Definitions
struct vector_ops_s vector_ops = { .destroy = VECTOR_destroy,
                                   .softReset = VECTOR_softReset,
                                   .reset = VECTOR_reset,
                                   .resize = VECTOR_resize,
                                             
};

//Function definitions:
