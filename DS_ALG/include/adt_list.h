// adt_list.h
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

    void* (*first)(const List* list);
    void* (*last)(const List* list);
    void* (*at)(const List* list, u16 index);

    s16(*insertFirst)(List* list);
    s16(*insertLast)(List* list, void* data);
    s16(*insertAt)(List* list, u16 index, void* data);

    s16(*extractFirst)(List* list);
    s16(*extractLast)(List* list);
    s16(*extractAt)(List* list, u16 position);

    s16(*concat)(List* list1, const List* list2);
    void (*traverse)(const List* list, void (*callback)(MemoryNode*));

    MemoryNode* (*next)(List* list);
    MemoryNode* (*previous)(List* list);
    void (*setNext)(MemoryNode* node, MemoryNode* nextNode);
    void (*setPrevious)(MemoryNode* node, MemoryNode* previousNode);

    void (*print)(List* list);
};

List* LIST_create(u16 capacity);

#endif //__ADT_LIST_H__
