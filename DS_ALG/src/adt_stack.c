/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_stack.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 STACK_push(Stack* stack, void* data, u16 size);
static void* STACK_pop(Stack* stack);
static void* STACK_top(Stack* stack);

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
    // ALopezESAT: This could be inline, also no need to have less than if it is unsigned
    if (capacity <= 0) {
        return NULL;
    }

    Stack* s_temp = MM->malloc(sizeof(Stack));
    if (NULL == s_temp) {
        // ALopezESAT: If NULL, then free would fail, you don't need to free anything here
        MM->free(s_temp);
        return NULL;
    }

    s_temp->storage_ = VECTOR_create(capacity);
    // ALopezESAT: Maybe it would be worth checking storage here, and calling free on s_temp if this one fails before
    // returning null.
    s_temp->ops_ = &stack_ops;

    // ALopezESAT: This! But before assigning ops and calling free on s_temp, as you already allocated it therefore
    // to avoid memory leaks you should release it as well.
    /*if (NULL == s_temp->storage_) {
        return NULL;
    } mirar */ 

    return s_temp;
}

s16 STACK_push(Stack* stack, void* data, u16 size) {
    // ALopezESAT: Can be made inline
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->ops_->insertLast(stack->storage_, data, size);
}

void* STACK_pop(Stack* stack) {
    // ALopezESAT: Can be made inline
    if (NULL == stack ) {
        return NULL;
    }
    
    return stack->storage_->ops_->extractLast(stack->storage_);
}

void* STACK_top(Stack* stack) {
    // ALopezESAT: Same here and after, just check them all
    if (NULL == stack)
    {
        return NULL;
    }

    return stack->storage_->ops_->last(stack->storage_);
}

s16 STACK_reset(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }
    // ALopezESAT: This might be not necessary if the stack is functioning as expected, as you either get both
    // the stack and the storage set up or neither.
    // The same goes for the ops, if you assume no one is messing with your structure, they do not need checking.
    if (NULL == stack->storage_)
    {
        return kErrorCode_StackNull;
    }


    return stack->storage_->ops_->reset(stack->storage_);
}

u16 STACK_capacity(Stack* stack) {
    if (NULL == stack)
    {
        return 0;
    }

    return stack->storage_->ops_->capacity(stack->storage_);
}

s16 STACK_resize(Stack* stack, u16 new_size) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->ops_->resize(stack->storage_, new_size);
}

// ALopezESAT: I am quite sure length returns u16 from vector, so you should do the same (and also change the .h)
// Or modify vector to also return s16 and error codes, your call...
s16 STACK_length(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->ops_->length(stack->storage_);
}

boolean STACK_isEmpty(Stack* stack) {
    // ALopezESAT: Check "NULL != stack" as you have done before
    // Also this if else is redundant, you already get a boolean return, you can return that
    if (stack->storage_->ops_->isEmpty(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

boolean STACK_isFull(Stack* stack) {
    // ALopezESAT: Same as above
    if (stack->storage_->ops_->isFull(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

s16 STACK_concat(Stack* stack, Stack* stack_src) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }
    if (NULL == stack_src)
    {
        return kErrorCode_StackNull;
    }
    // ALopezESAT: I am quite sure this is not what you do when you concat... right?
    return stack->storage_->ops_->isEmpty(stack->storage_);
}

s16 STACK_destroy(Stack* stack) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    // ALopezESAT: Destroy returns an error code, you can check it just in case
    stack->storage_->ops_->destroy(stack->storage_);
    MM->free(stack);

    return kErrorCode_Ok;
}

void STACK_print(Stack* stack) {
    if (NULL == stack)
    {
        printf("\t[Stack Info] stack: NULL\n");
        return;
    }
    // ALopezESAT: You might want to print some info about the stack itself (at least a memory address for the stack
    // wrapping struct.
    stack->storage_->ops_->print(stack->storage_);
}
