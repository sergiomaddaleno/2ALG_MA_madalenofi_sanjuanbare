
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

#include <stdlib.h>

// Static prototypes
static s16 LIST_destroy(List* list);
static s16 LIST_reset(List* list);
static s16 LIST_softReset(List* list);
static s16 LIST_resize(List* list, u16 newCapacity);

static u16 LIST_capacity(const List* list);
static u16 LIST_length(const List* list);
static s16 LIST_isEmpty(const List* list);
static s16 LIST_isFull(const List* list);

static void* LIST_first(const List* list);
static void* LIST_last(const List* list);
static void* LIST_at(const List* list, u16 index);

static s16 LIST_insertFirst(List* list);
static s16 LIST_insertLast(List* list, void* data);
static s16 LIST_insertAt(List* list, u16 index, void* data);

static s16 LIST_extractFirst(List* list);
static s16 LIST_extractLast(List* list);
static s16 LIST_extractAt(List* list, u16 position);

static s16 LIST_concat(List* list1, const List* list2);
static void LIST_traverse(const List* list, void (*visit)(void* data));

static MemoryNode* LIST_next(List* list);
static MemoryNode* LIST_previous(List* list);
static void LIST_setNext(MemoryNode* node, MemoryNode* nextNode);
static void LIST_setPrevious(MemoryNode* node, MemoryNode* previousNode);

static void LIST_print(List* list);

// Memory Node's API Definitions
struct list_ops_s list_ops = {
    .destroy = LIST_destroy,
    .reset = LIST_reset,
    .softReset = LIST_softReset,
    .resize = LIST_resize,
    .capacity = LIST_capacity,
    .length = LIST_length,
    .isEmpty = LIST_isEmpty,
    .isFull = LIST_isFull,
    .first = LIST_first,
    .last = LIST_last,
    .at = LIST_at,
    .insertFirst = LIST_insertFirst,
    .insertLast = LIST_insertLast,
    .insertAt = LIST_insertAt,
    .extractFirst = LIST_extractFirst,
    .extractLast = LIST_extractLast,
    .extractAt = LIST_extractAt,
    .concat = LIST_concat,
    .traverse = LIST_traverse,
    .next = LIST_next,
    .previous = LIST_previous,
    .setNext = LIST_setNext,
    .setPrevious = LIST_setPrevious,
    .print = LIST_print
};

List* LIST_create(u16 capacity) {
    if (capacity <= 0) {
        return NULL;
    }

    List* l_temp = MM->malloc(sizeof(List));
    if (NULL == l_temp) {
        return NULL;
    }

    l_temp->storage_ = MM->malloc(sizeof(MemoryNode) * capacity);
    if (NULL == l_temp->storage_) {
        MM->free(l_temp);
        return NULL;
    }

    for (s16 i = 0; i < capacity; i++) {
        MEMNODE_createLite(&l_temp->storage_[i]);
    }

    l_temp->length_ = 0;
    l_temp->capacity_ = 0;
    /*l_temp->head_ = 0;
    l_temp->tail_ = 0;
    */

    return l_temp;
}

//s16 LIST_destroy(List* list) {}
//s16 LIST_reset(List* list) {}
//s16 LIST_softReset(List* list) {}
//s16 LIST_resize(List* list, u16 newCapacity) {}

/*u16 LIST_capacity(const List* list) {
    if (NULL == list) {
        return NULL;
    }
    //return list->capacity_;
}
u16 LIST_length(const List* list) {
    if (NULL == list) {
        return NULL;
    }
    //return list->length_;
}
s16 LIST_isEmpty(const List* list) {
    if (NULL == list) {
        return NULL;
    }
    //return list->length_ == 0;
}
s16 LIST_isFull(const List* list) {
    if (NULL == list) {
        return NULL;
    }
    //return list->length_ == list->capacity_;
}*/

//void* LIST_first(const List* list){}
//void* LIST_last(const List* list){}
//void* LIST_at(const List* list, u16 index){}

//s16 LIST_insertFirst(List* list){}
//s16 LIST_insertLast(List* list, void* data){}
//s16 LIST_insertAt(List* list, u16 index, void* data){}

//s16 LIST_extractFirst(List* list){}
//s16 LIST_extractLast(List* list, void* data){}
//s16 LIST_extractAt(List* list, u16 index, void* data){}

//s16 LIST_concat(List* list1, const List* list2) {}
//void LIST_traverse(const List* list, void (*visit)(void* data)) {}

//MemoryNode* LIST_next(List* list){}
//MemoryNode* LIST_previous(List* list){}
//void LIST_setNext(MemoryNode* node, MemoryNode* nextNode){}
//void LIST_setPrevious(MemoryNode* node, MemoryNode* previousNode){}

//void LIST_print(List* list);





