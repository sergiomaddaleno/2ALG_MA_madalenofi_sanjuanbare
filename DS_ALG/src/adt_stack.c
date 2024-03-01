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

struct stack_ops_s stack_ops = {
	.push = STACK_push,
	.pop = STACK_pop,
	.top = STACK_top
};
