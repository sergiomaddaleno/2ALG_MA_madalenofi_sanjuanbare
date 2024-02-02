// adt_stack.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

typedef struct adt_list_s {
	MemoryNode* head_;
	MemoryNode* tail_; 
	u16 length_;
	u16 capacity_;
	MemoryNode* storage_;
	struct list_ops_s* ops_;
} List;

struct list_ops_s {

	s16 (*destroy)(List* list);

	MemoryNode* (*next)(List* list);


}

#endif //__ADT_STACK_H__
