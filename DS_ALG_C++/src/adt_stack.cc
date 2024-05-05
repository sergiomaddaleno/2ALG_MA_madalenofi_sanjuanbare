/***/

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_stack.h"
#include "adt_vector.h"

#include "EDK_MemoryManager/edk_memory_manager.h"


adt_stack_s::adt_stack_s(u16 capacity)
{
    if (capacity > 0) {
        storage_= new adt_vector_s(capacity);
    }
    else {
        storage_ = NULL;
    }

}

adt_stack_s::~adt_stack_s(){}

s16 adt_stack_s::push(adt_stack_s* stack, void* data, u16 size) {
    // ALopezESAT: Can be made inline
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->insertLast(stack->storage_, data, size);
}

void* adt_stack_s::pop(adt_stack_s* stack) {
    // ALopezESAT: Can be made inline
    if (NULL == stack ) {
        return NULL;
    }
    
    return stack->storage_->extractLast(stack->storage_);
}

void* adt_stack_s::top(adt_stack_s* stack) {
    // ALopezESAT: Same here and after, just check them all
    if (NULL == stack)
    {
        return NULL;
    }

    return stack->storage_->last(stack->storage_);
}

s16 adt_stack_s::reset(adt_stack_s* stack) {
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
    return stack->storage_->reset(stack->storage_);
}

u16 adt_stack_s::capacity(adt_stack_s* stack) {
    if (NULL == stack)
    {
        return 0;
    }

    return stack->storage_->capacity(stack->storage_);
}

s16 adt_stack_s::resize(adt_stack_s* stack, u16 new_size) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->resize(stack->storage_, new_size);
}

// ALopezESAT: I am quite sure length returns u16 from vector, so you should do the same (and also change the .h)
// Or modify vector to also return s16 and error codes, your call...
s16 adt_stack_s::length(adt_stack_s* stack) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    return stack->storage_->length(stack->storage_);
}

boolean adt_stack_s::isEmpty(adt_stack_s* stack) {
    // ALopezESAT: Check "NULL != stack" as you have done before
    // Also this if else is redundant, you already get a boolean return, you can return that
    if (stack->storage_->isEmpty(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

boolean adt_stack_s::isFull(adt_stack_s* stack) {
    // ALopezESAT: Same as above
    if (stack->storage_->isFull(stack->storage_)) {
        return True;
    }
    else {
        return False;
    }
}

s16 adt_stack_s::concat(adt_stack_s* stack, adt_stack_s* stack_src) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }
    if (NULL == stack_src)
    {
        return kErrorCode_StackNull;
    }
    // ALopezESAT: I am quite sure this is not what you do when you concat... right?
    return stack->storage_->isEmpty(stack->storage_);
}

s16 adt_stack_s::destroy(adt_stack_s* stack) {
    if (NULL == stack)
    {
        return kErrorCode_StackNull;
    }

    // ALopezESAT: Destroy returns an error code, you can check it just in case
    stack->storage_->destroy(stack->storage_);
    delete stack;

    return kErrorCode_Ok;
}

void adt_stack_s::print(adt_stack_s* stack) {
    if (NULL == stack)
    {
        printf("\t[Stack Info] stack: NULL\n");
        return;
    }
    // ALopezESAT: You might want to print some info about the stack itself (at least a memory address for the stack
    // wrapping struct.
    stack->storage_->print(stack->storage_);
}
