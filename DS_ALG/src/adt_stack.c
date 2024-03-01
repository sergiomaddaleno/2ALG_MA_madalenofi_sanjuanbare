/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_stack.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 STACK_push(Stack* stack, void* data, u16 size);
static s16 STACK_pop(Stack* stack);
static s16 STACK_top(Stack* stack);

static s16 STACK_reset(Stack* stack);
static u16 STACK_capacity(Stack* stack);
static s16 STACK_resize(Stack* stack, u16 new_size);
static u16 STACK_length(Stack* stack);

static boolean STACK_isEmpty(Stack* stack);
static boolean STACK_isFull(Stack* stack);

static s16 STACK_concat(Stack* stack, Stack* stack_src);
static s16 STACK_destroy(Stack* stack);

static void STACK_print(Stack* stack);


struct stack_ops_s stack_ops = {
	.push = STACK_push,
	.pop = STACK_pop,
	.top = STACK_top,

    .reset = STACK_reset,
    .capacity = STACK_capacity,
    .resize = STACK_resize,
    .length = STACK_length,

    .isEmpty = STACK_isEmpty,
    .isFull = STACK_isFull,

    .concat = STACK_concat,
    .destroy = STACK_destroy,

    .print = STACK_print
};

Stack* STACK_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    Stack* s_temp = MM->malloc(sizeof(Stack));
    if (NULL == s_temp) {
        return NULL;
    }

    s_temp->storage_ = MM->malloc(sizeof(Vector) * capacity);
    if (NULL == s_temp->storage_) {
        MM->free(s_temp);
        return NULL;
    }

    for (s16 i = 0; i < capacity; i++) {
        MEMNODE_createLite(&s_temp->storage_[i]);
    }

    s_temp->tail_ = 0;
    s_temp->head_ = 0;
    s_temp->capacity_ = capacity;
    s_temp->ops_ = &stack_ops;

    return s_temp;
}

s16 STACK_push(Stack* stack, void* data, u16 size) {

}

s16 STACK_pop(Stack* stack) {

}

s16 STACK_top(Stack* stack) {

}

s16 STACK_reset(Stack* stack) {

}

u16 STACK_capacity(Stack* stack) {

}

s16 STACK_resize(Stack* stack, u16 new_size) {

}

u16 STACK_length(Stack* stack) {

}

boolean STACK_isEmpty(Stack* stack) {

}

boolean STACK_isFull(Stack* stack) {

}

s16 STACK_concat(Stack* stack, Stack* stack_src) {

}

s16 STACK_destroy(Stack* stack) {

}

void VECTOR_print(Vector* vector) {
    if (NULL == vector) {
        printf("\t[Vector Info] vector: NULL\n");
        return;
    }

    
}