
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Static prototypes
static s16 LIST_destroy(List* list);
static s16 LIST_reset(List* list);
static s16 LIST_softReset(List* list);
static s16 LIST_resize(List* list, u16 new_size);   //repasar

static u16 LIST_capacity(const List* list);
static u16 LIST_length(const List* list);
static s16 LIST_isEmpty(const List* list);
static s16 LIST_isFull(const List* list);

static void* LIST_first(const List* list);
static void* LIST_last(const List* list);
static void* LIST_at(const List* list, u16 position);

static s16 LIST_insertFirst(List* list, void* data, u16 bytes);
static s16 LIST_insertLast(List* list, void* data, u16 bytes);
static s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position);

static void* LIST_extractFirst(List* list); //hacer
static void* LIST_extractLast(List* list); //hacer
static void* LIST_extractAt(List* list, u16 position); //hacer

static s16 LIST_concat(List* list, const List* list_src); //repasar
static s16 LIST_traverse(const List* list, void (*callback)(MemoryNode*));

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
    //.extractFirst = LIST_extractFirst,
    //.extractLast = LIST_extractLast,
    //.extractAt = LIST_extractAt,
    .concat = LIST_concat,
    .traverse = LIST_traverse,
    //.print = LIST_print

};

List* LIST_create(u16 capacity) {
    
    if (capacity <= 0) {
        return NULL;
    }

    List* l_temp = MM->malloc(sizeof(List));
    if (NULL == l_temp) {
        return NULL;
    }

    l_temp->length_ = 0;
    l_temp->capacity_ = capacity;
    l_temp->head_ = NULL;
    l_temp->tail_ = NULL;

    l_temp->ops_ = &list_ops;
    
    return l_temp;
}

s16 LIST_destroy(List* list) {

    if (NULL == list)
    {
        return kErrorCode_ListNull;
    }
    if (NULL == list->head_)
    {
        MM->free(list);
        return kErrorCode_StorageNull;
    }

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);
   
    while (NULL != list->head_) {

        MM->free(list->head_->data_);
        aux = list->head_->next_;
        MM->free(list->head_);
        list->head_ = aux;
    }
    
    MM->free(list);

    return kErrorCode_Ok;
}

s16 LIST_reset(List* list) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);

    while (NULL != list->head_) {

        MM->free(list->head_->data_);
        aux = list->head_->next_;
        MM->free(list->head_);
        list->head_ = aux;
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

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);

    while (NULL != list->head_) {

      
        aux = list->head_->next_;
        MM->free(list->head_);
        list->head_ = aux;
    }

    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;
    list->storage_ = NULL;
    return  kErrorCode_Ok;
}

s16 LIST_resize(List* list, u16 new_size) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    if (0 == new_size) {
        return kErrorCode_SizeNull;
    }

    if (list->capacity_ == new_size) {
        return kErrorCode_EqualCapacity;
    }

    u16 elements_to_copy = 0;

    if (list->length_ > new_size) {
        elements_to_copy = new_size;
        list->length_ = new_size;
    }
    else {
        elements_to_copy = list->length_;
    }

    List* aux = MM->malloc(sizeof(List));
    aux->storage_ = MM->malloc(sizeof(MemoryNode) * new_size);

    if (NULL == aux) {
        return kErrorCode_MallocNull;
    }

    for (u16 i = 0; i < new_size; i++) {
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
    list->capacity_ = new_size;
    
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

    if (list->head_) {
        return NULL;
    }

    return list->head_->data_;
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

    return list->tail_->data_;
}

void* LIST_at(const List* list, u16 position){

    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->storage_) {
        return NULL;
    }

    if (position < 0){
        return NULL;
    }

    return list->storage_[position].data_;
}

s16 LIST_insertFirst(List* list, void* data, u16 bytes){
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (list->capacity_ == list->length_) {
        return kErrorCode_EqualCapacity;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if(NULL==list->head_){
        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);

        aux->data_ = data;
        aux->size_ = bytes;

        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;

        list->length_++;
    }
    else {

        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);

        aux->data_ = data;
        aux->size_ = bytes;

        aux->next_ = list->head_;
        list->head_ = aux;

        list->length_++;
    }
    return kErrorCode_Ok;
}

s16 LIST_insertLast(List* list, void* data, u16 bytes){

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (list->capacity_ == list->length_) {
        return kErrorCode_EqualCapacity;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (bytes <= 0) {
        return kErrorCode_BytesZero;
    }

    if (NULL == list->head_) {
        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);


        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;

        aux->data_ = data;
        aux->size_ = bytes;


        list->length_++;


    }
    else {

        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);


        aux->next_ = list->tail_;
        list->tail_ = aux;


        aux->data_ = data;
        aux->size_ = bytes;


        list->length_++;
    }


    return kErrorCode_Ok;

}


s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position){

    /*if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (list->capacity_ == list->length_) {
        return kErrorCode_EqualCapacity;
    }

    if (NULL == data) {
        return kErrorCode_DataNull;
    }

    if (position < 0) {
        return kErrorCode_BytesZero;
    }

    if (NULL == list->head_) {
        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);

        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;

        aux->data_ = data;
        aux->size_ = bytes;

        list->length_++;
    }
    else {

        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);
        MemoryNode* countaux = MM->malloc(sizeof(MemoryNode) * 1);

        if (position >= list->length_) {
            position = list->length_;
        }

        int count = 0;
        
            while (count < position) {
                if (countaux == NULL) {
                    aux = list->head_;
                    countaux= list->head_;
                }
                else {

                    countaux = aux->next;

                }
                count++;
            }

        aux->next_ = countaux->next;
        countaux->next = aux;
        
        aux->data_ = data;
        aux->size_ = bytes;

        list->length_++;
    }*/
    return kErrorCode_Ok;
}

void* LIST_extractFirst(List* list) {
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (LIST_isEmpty(list)) {
        return NULL;
    }

    MemoryNode* aux = list->head_;
    list->head_ = aux->next_;

    MM->free(aux);

    list->length_--;

    return aux;
}

void* LIST_extractLast(List* list) {

}

//void* LIST_extractAt(List* list, u16 position){}

s16 LIST_concat(List* list, const List* list_src) {

    if (NULL == list || NULL == list_src)
    {
        return kErrorCode_ListNull;
    }
    if (NULL == list->storage_ || NULL == list_src->storage_)
    {
        return kErrorCode_StorageNull;
    }
    u16 new_capacity = list->capacity_ + list_src->capacity_;
    list->ops_->resize(list, new_capacity);
    u16 index = list->tail_;
    for (u16 i = 0; i < list_src->length_; i++) {
        list->storage_->ops_->memCopy(&list->storage_[index], list_src->storage_[i].data_, list_src->storage_[i].size_);
        index++;

    }
    list->length_ += list_src->length_;
    
    return kErrorCode_Ok;
}

s16 LIST_traverse(const List* list, void (*callback)(MemoryNode*)) {
    
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


void LIST_print(List* list) {
    printf("Entering LIST_print function\n");
    if (NULL == list) {
        printf("\t[List Info] list: NULL\n");
        return;
    }

    printf("\t[List Info] Address: %p\n", list);
    printf("\t[List Info] Length: %d\n", list->length_);
    printf("\t[List Info] Capacity: %d\n", list->capacity_);
    printf("\t[List Info] First address: %p\n", list->head_);
    printf("\t[List Info] Last Address: %p\n", list->tail_);

    if (NULL == list->head_) {
        printf("\t[List Info] list is empty\n");
        return;
    }

    MemoryNode* currentNode = list->head_;

    while (currentNode != NULL) {
        printf("\t  [List Info] Storage #%p\n", currentNode);
        printf("\t      [Node info] Address: %p\n", currentNode);
        printf("\t      [Node info] Size: %d\n", currentNode->size_);
        printf("\t      [Node info] Data Address: %p\n", currentNode->data_);
        printf("\t      [Node info] Data Content: %s\n", currentNode->data_);

        printf("\t      [Node info] Next address: %p\n", currentNode->next_);

        currentNode = currentNode->next_;
    }
}






