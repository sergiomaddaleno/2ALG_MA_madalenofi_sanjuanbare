// adt_stack.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__

#include "adt_memory_node.h"
#include "adt_vector.h"

typedef struct adt_stack_s {
	Vector* storage_;
	struct stack_ops_s* ops_;
} Stack;

struct stack_ops_s {
	s16(*push)(Stack* stack, void* data, u16 size);
	void* (*pop)(Stack* stack);
	void* (*top)(Stack* stack);

	s16(*reset)(Stack* stack);
	u16 (*capacity)(Stack* stack);
	s16 (*resize)(Stack* stack, u16 new_size);
	s16 (*length)(Stack* stack);

	boolean (*isEmpty)(Stack* stack);
	boolean (*isFull)(Stack* stack);

	s16 (*concat)(Stack* stack, Stack* stack_src);
	s16 (*destroy)(Stack* stack);

	void (*print)(Stack* stack);
};

Stack* STACK_create(u16 capacity);

#endif //__ADT_STACK_H__
