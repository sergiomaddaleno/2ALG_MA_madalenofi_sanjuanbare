// adt_stack.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__

#include "adt_memory_node.h"
#include "adt_vector.h"

class adt_stack_s {
public:

	adt_stack_s(u16 capacity);
	~adt_stack_s();

	adt_vector_s* storage_;

	s16 push(adt_stack_s* stack, void* data, u16 size);

	void* pop(adt_stack_s* stack);

	void* top(adt_stack_s* stack);

	s16 reset(adt_stack_s* stack);

	u16 capacity(adt_stack_s* stack);

	s16 resize(adt_stack_s* stack, u16 new_size);

	s16 length(adt_stack_s* stack);

	boolean isEmpty(adt_stack_s* stack);

	boolean isFull(adt_stack_s* stack);

	s16 concat(adt_stack_s* stack, adt_stack_s* stack_src);

	s16 destroy(adt_stack_s* stack);

	void print(adt_stack_s* stack);

};

#endif //__ADT_STACK_H__
