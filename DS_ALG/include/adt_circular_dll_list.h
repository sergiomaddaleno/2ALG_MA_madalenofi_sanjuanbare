// adt_list.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

typedef struct adt_dll_list_s {
	MemoryNode* head_;
	MemoryNode* tail_; 
	u16 length_;
	u16 capacity_;
	//MemoryNode* storage_;
	struct dll_list_ops_s* ops_;
} List;

struct dll_list_ops_s {

    s16(*destroy)(List* list);
    s16(*reset)(List* list);
    s16(*softReset)(List* list);
    s16(*resize)(List* list, u16 new_size);

    u16(*capacity)(const List* list);
    u16(*length)(const List* list);
    s16(*isEmpty)(const List* list);
    s16(*isFull)(const List* list);

    void* (*first)(const List* list);
    void* (*last)(const List* list);
    void* (*at)(const List* list, u16 position);

    s16(*insertFirst)(List* list, void* data, u16 bytes);
    s16(*insertLast)(List* list, void* data, u16 bytes);
    s16(*insertAt)(List* list, void* data, u16 bytes, u16 position);

    void* (*extractFirst)(List* list);
    void* (*extractLast)(List* list);
    void* (*extractAt)(List* list, u16 position);

    s16(*concat)(List* list, const List* list_src);
    s16 (*traverse)(const List* list, void (*callback)(MemoryNode*));

    void (*print)(List* list);
};

List* DLL_LIST_create(u16 capacity);

#endif //__ADT_LIST_H__
