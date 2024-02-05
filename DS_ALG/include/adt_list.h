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

    s16(*destroy)(List* list);
    s16(*reset)(List* list);
    s16(*softReset)(List* list);
    s16(*resize)(List* list, u16 newCapacity);

    u16(*capacity)(const List* list);
    u16(*length)(const List* list);
    s16(*isEmpty)(const List* list);
    s16(*isFull)(const List* list);

    MemoryNode* (*first)(const List* list);
    MemoryNode* (*last)(const List* list);
    MemoryNode* (*at)(const List* list, u16 index);

    s16(*insertFirst)(List* list);
    s16(*insertLast)(List* list, void* data);
    s16(*insertAt)(List* list, u16 index, void* data);

    s16(*extractFirst)(List* list);
    s16(*extractLast)(List* list);
    s16(*extractAt)(List* list, u16 position);

    s16(*concat)(List* list1, const List* list2);
    void (*traverse)(const List* list, void (*visit)(void* data));

    MemoryNode* (*next)(List* list);
    MemoryNode* (*previous)(List* list);
    void (*setNext)(MemoryNode* node, MemoryNode* nextNode);
    void (*setPrevious)(MemoryNode* node, MemoryNode* previousNode);

    void (*print)(List* list);
};


#endif //__ADT_STACK_H__
