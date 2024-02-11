
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
static void LIST_traverse(const List* list, void (*callback)(MemoryNode*));

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
    l_temp->head_ = NULL;
    l_temp->tail_ = NULL;
    

    return l_temp;
}

s16 LIST_destroy(List* list) {

    if (NULL == list)
    {
        return kErrorCode_ListNull;
    }
    if (NULL == list->storage_)
    {
        MM->free(list);
        return kErrorCode_NodeNull;
    }
    for (u16 i = 0; i < list->length_; i++)
    {
        //list->storage_[i+1].next_= list->storage_[i].next_;
        if (NULL != list->storage_[i].data_) {
            MM->free(list->storage_[i].data_);
        }
        MM->free(&list->storage_[i]);

    }
    //MM->free(list->storage_);
    MM->free(list);

    return kErrorCode_Ok;



}
s16 LIST_reset(List* list) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = 0; i < list->length_; i++) {
        //list->storage_[i + 1].next_ = list->storage_[i].next_;
        list->storage_[i].ops_->reset(&list->storage_[i]);
        MM->free(&list->storage_[i]);
    }
    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;

    return  kErrorCode_Ok;

}
s16 LIST_softReset(List* list) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = 0; i < list->length_; i++) {
        //list->storage_[i + 1].next_ = list->storage_[i].next_;
        MM->free(&list->storage_[i]);
    }
    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;
    list->storage_ = NULL;
    return  kErrorCode_Ok;


}
s16 LIST_resize(List* list, u16 newCapacity) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->storage_) {
        return kErrorCode_NodeNull;
    }

    if (0 == newCapacity) {
        return kErrorCode_SizeNull;
    }

    if (list->capacity_ == newCapacity) {
        return kErrorCode_EqualCapacity;
    }

    u16 elements_to_copy = 0;

    if (list->length_ > newCapacity) {
        elements_to_copy = newCapacity;
        list->length_ = newCapacity;
    }
    else {
        elements_to_copy = list->length_;
    }
    List* aux = MM->malloc(sizeof(List));
    aux->storage_ = MM->malloc(sizeof(MemoryNode) * newCapacity);

    if (NULL == aux) {
        return kErrorCode_MallocNull;
    }

    for (u16 i = 0; i < newCapacity; i++) {
        MEMNODE_createLite(&aux[i]);
    }
    for (u16 i = 0; i < elements_to_copy; i++) {
        list->storage_->ops_->memCopy(&aux[i], list->storage_[i].data_, list->storage_[i].size_);
        aux->storage_[i].next_= list->storage_[i].next_;
    }
    for (u16 i = elements_to_copy; i < list->length_; i++) {
        if (NULL != list->storage_[i].data_) {
            MM->free(list->storage_[i].data_);
        }
        list->storage_[i].next_ = NULL;
        MM->free(&list->storage_[i]);
        
    }
    
    list->storage_ = aux;
    list->storage_[list->length_-1].next_ = NULL;
    list->tail_ = &list->storage_[list->length_ - 1];
    list->capacity_ = newCapacity;
    

    return kErrorCode_Ok;

}

u16 LIST_capacity(const List* list) {
    if (NULL == list) {
        return 0;
    }
    return list->capacity_;
}
u16 LIST_length(const List* list) {
    if (NULL == list) {
        return 0;
    }
    return list->length_;
}
s16 LIST_isEmpty(const List* list) {
    if (NULL == list) {
        return 0;
    }
    return list->length_ == 0;
}
s16 LIST_isFull(const List* list) {
    if (NULL == list) {
        return 0;
    }
    return list->length_ == list->capacity_;
}

void* LIST_first(const List* list){

    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->storage_) {
        return NULL;
    }

    return list->storage_[0].data_;

}
void* LIST_last(const List* list){
    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->storage_) {
        return NULL;
    }

    if (list->length_ == 0) {
        return NULL;
    }

    return list->storage_[list->length_-1].data_;


}
void* LIST_at(const List* list, u16 index){

    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->storage_) {
        return NULL;
    }

    if (index < 0){
        return NULL;
    }

    return list->storage_[index].data_;

}

//s16 LIST_insertFirst(List* list){}
//s16 LIST_insertLast(List* list, void* data){}
//s16 LIST_insertAt(List* list, u16 index, void* data){}

//s16 LIST_extractFirst(List* list){}
//s16 LIST_extractLast(List* list, void* data){}
//s16 LIST_extractAt(List* list, u16 index, void* data){}

s16 LIST_concat(List* list1, const List* list2) {



    if (NULL == list1 || NULL == list2)
    {
        return kErrorCode_VectorNull;
    }
    if (NULL == list1->storage_ || NULL == list2->storage_)
    {
        return kErrorCode_NodeNull;
    }
    u16 new_capacity = list1->capacity_ + list2->capacity_;
    list1->ops_->resize(list1, new_capacity);
    u16 index = list1->tail_;
    for (u16 i = 0; i < list2->length_; i++) {
        list1->storage_->ops_->memCopy(&list1->storage_[index], list2->storage_[i].data_, list2->storage_[i].size_);
        index++;

    }
    list1->length_ += list2->length_;
    return kErrorCode_Ok;



}
void LIST_traverse(const List* list, void (*callback)(MemoryNode*)) {
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->storage_) {
        return kErrorCode_StorageNull;
    }

    for (s16 i = 0; i < list->length_; i++) {

        callback(&list->storage_[i]);
    }

    return kErrorCode_Ok;


}

//MemoryNode* LIST_next(List* list){}
/MemoryNode* LIST_previous(List* list){}
//void LIST_setNext(MemoryNode* node, MemoryNode* nextNode){}
//void LIST_setPrevious(MemoryNode* node, MemoryNode* previousNode){}

//void LIST_print(List* list);





