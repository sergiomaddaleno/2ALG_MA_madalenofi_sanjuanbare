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
static s16 STACK_length(Stack* stack);

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

    s_temp->storage_ = VECTOR_create(capacity);
    s_temp->ops_ = &stack_ops;

    /*if (NULL == s_temp->storage_) {
        return NULL;
    } mIRAR */ 

    return s_temp;
}

s16 STACK_push(Stack* stack, void* data, u16 size) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    return stack->storage_->ops_->insertLast(stack->storage_, data, size);
}

s16 STACK_pop(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    return stack->storage_->ops_->extractLast(stack->storage_);
}

s16 STACK_top(Stack* stack) {

}

s16 STACK_reset(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }
    //assert(stack->storsge_);
    return stack->storage_->ops_->reset(stack->storage_);
}

u16 STACK_capacity(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    return stack->storage_->ops_->capacity(stack->storage_);
}

s16 STACK_resize(Stack* stack, u16 new_size) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    return stack->storage_->ops_->resize(stack->storage_, new_size);
}

s16 STACK_length(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    return stack->storage_->ops_->length(stack->storage_);
}

boolean STACK_isEmpty(Stack* stack) {
    if (stack->storage_->ops_->isEmpty(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

boolean STACK_isFull(Stack* stack) {
    if (stack->storage_->ops_->isFull(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

s16 STACK_concat(Stack* stack, Stack* stack_src) {

}

s16 STACK_destroy(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }
    
    stack->storage_->ops_->destroy(stack->storage_);

    return kErrorCode_Ok;
}

void STACK_print(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_VectorNull;
    }

    stack->storage_->ops_->print(stack->storage_);
}