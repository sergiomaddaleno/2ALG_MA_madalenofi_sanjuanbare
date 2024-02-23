
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Static prototypes
static s16 LIST_destroy(List* list);
static s16 LIST_reset(List* list);
static s16 LIST_softReset(List* list);
static s16 LIST_resize(List* list, u16 new_size);   

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

static void* LIST_extractFirst(List* list); 
static void* LIST_extractLast(List* list); 
static void* LIST_extractAt(List* list, u16 position); 

static s16 LIST_concat(List* list, const List* list_src); 
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
    .extractFirst = LIST_extractFirst,
    .extractLast = LIST_extractLast,
    .extractAt = LIST_extractAt,
    .concat = LIST_concat,
    .traverse = LIST_traverse,
    .print = LIST_print

};

List* LIST_create(u16 capacity) {
    
    if (capacity <= 0) {
        return NULL;
    }

    List* l_temp = MM->malloc(sizeof(List));
    if (NULL == l_temp) {
        MM->free(l_temp);
        return NULL;
    }

    l_temp->length_ = 0;
    l_temp->capacity_ = capacity;
    l_temp->head_ = NULL;
    l_temp->tail_ = NULL;
    //l_temp->storage_ = NULL;
    l_temp->ops_ = &list_ops;
    
    return l_temp;
}

s16 LIST_destroy(List* list) {

    if(NULL == list) {
        return kErrorCode_ListNull;
    }

    MemoryNode* current = list->head_;
    MemoryNode* next;

    while (current != NULL) {
        next = current->next_;
        
        MM->free(current->data_);
        MM->free(current);
        current = next;
    }

    MM->free(list);

    return kErrorCode_Ok;
}

s16 LIST_reset(List* list) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }
    
    // ALopezESAT: Creating a memory node to then point aux to something else is a memory leak
    // LIST_reset should not have any malloc at all.
    MemoryNode* aux = list->head_;

    while (NULL != list->head_) {
       
        MM->free(list->head_->data_);
        
        aux = list->head_->next_;
        MM->free(list->head_);
        list->head_ = aux;
    }

    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;
    //list->storage_ = NULL;
    return  kErrorCode_Ok;
}

s16 LIST_softReset(List* list) {

    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    // ALopezESAT: Same as in LIST_reset
    MemoryNode* aux = list->head_;

    while (NULL != list->head_) {

        aux = list->head_->next_;
        MM->free(list->head_);
       
        list->head_ = aux;
    }

    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;
    //list->storage_ = NULL;
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

    if (list->length_ > new_size) {
        
        
        list->capacity_ = new_size;
        
        // ALopezESAT: Same as in LIST_reset
        MemoryNode* countaux = list->head_;
        MemoryNode* aux = list->head_;
        if (countaux == NULL) {
            return kErrorCode_MallocNull;
        }

        if (new_size > 1) {

            countaux = list->head_;

            int count = 0;

            while (count < new_size - 1) {
                countaux = countaux->next_;
                count++;
            }

            aux = countaux;

            while (count < list->length_ - 1) {
                countaux = countaux->next_;
                MM->free(countaux->data_);
                MM->free(countaux);
                count++;
            }

            list->length_ = new_size;
            list->capacity_ = new_size;
            list->tail_ = aux;
            aux->next_ = NULL;
        }
        else {
            int count = 0;
            
            aux = list->head_;
            countaux = list->head_;
            
            while (count < list->length_ - 1) {
                countaux = countaux->next_;
                MM->free(countaux->data_);
                MM->free(countaux);
               
                count++;
            }
            
            list->length_ = new_size;
            list->capacity_ = new_size;
            list->tail_ = aux;
            list->head_ = aux;
            aux->next_ = NULL;

        }
    }
    else {
        list->capacity_ = new_size;
    }

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

    if (NULL == list->head_) {
        return NULL;
    }

    return list->head_->data_;
}

void* LIST_last(const List* list){
    if (NULL == list) {
        return NULL;
    }
    if (NULL == list->head_) {
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

    if (NULL == list->head_) {
        return NULL;
    }

    // ALopezESAT: Position is unsigned, it will never be less than 0
    /*if (position < 0){
        return NULL;
    }*/

    MemoryNode* countaux = list->head_;
    int count = 0;

    while (count < position ) {
        countaux = countaux->next_;
        count++;
    }

    return countaux->data_;
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
        if (NULL == aux) {
            return 0;
        }
        aux->data_ = data;
        aux->size_ = bytes;

        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;

        list->length_++;
    }
    else {

        MemoryNode* aux = MM->malloc(sizeof(MemoryNode) * 1);
        if (NULL == aux) {
            return 0;
        }
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

        list->tail_->next_ = aux;
        list->tail_ = aux;
        list->tail_->next_ = NULL;

        aux->data_ = data;
        aux->size_ = bytes;

        list->length_++;
    }
    return kErrorCode_Ok;
}

s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position) {
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

    if (position > list->length_) {
        position = list->length_;
    }

    MemoryNode* aux = MM->malloc(sizeof(MemoryNode));
    if (aux == NULL) {
        return kErrorCode_MallocNull;
    }

    aux->data_ = data;
    aux->size_ = bytes;

    if (NULL == list->head_) {
        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;
    }
    else {
        if (position == 0) {
            aux->next_ = list->head_;
            list->head_ = aux;
        }
        else {
            MemoryNode* countaux = list->head_;
            int count = 0;

            while (count < position - 1) {
                countaux = countaux->next_;
                count++;
            }

            aux->next_ = countaux->next_;
            countaux->next_ = aux;
        }

        if (aux->next_ == NULL) {
            list->tail_ = aux;
        }
    }
    list->length_++;

    return kErrorCode_Ok;
}


void* LIST_extractFirst(List* list) {
    if (NULL == list) {
        return NULL;
    }

    if (LIST_isEmpty(list)) {
        return NULL;
    }

    if (list->head_ == NULL) {

        return NULL;
    }
    
    // ALopezESAT: Same as in LIST_reset, same for data
    MemoryNode* aux = list->head_->next_;
    void* data = list->head_->data_;

    aux = list->head_->next_;
    data = list->head_->data_;
    MM->free(list->head_);
    
    list->head_ = aux;
    list->length_--;

    return data;
}

void* LIST_extractLast(List* list) {
    if (list == NULL || LIST_isEmpty(list) || list->head_ == NULL) {
        return NULL;
    }

    void* data = list->tail_->data_;

    if (list->length_ == 1) {
        MM->free(list->tail_);
        list->tail_ = NULL;
        list->head_ = NULL;
    }
    else {
        MemoryNode* secondToLast = list->head_;
        while (secondToLast->next_ != list->tail_) {
            secondToLast = secondToLast->next_;
        }

        MM->free(list->tail_);
        list->tail_ = secondToLast;
        list->tail_->next_ = NULL;
    }

    list->length_--;
    
    return data;
}

void* LIST_extractAt(List* list, u16 position){

    if (NULL == list) {
        return NULL;
    }

    if (LIST_isEmpty(list)) {
        return NULL;
    }

    if (position >= list->length_) {
        position = list->length_;
    }

    if (NULL == list->head_) {

        return NULL;
    }

    MemoryNode* aux = list->head_->next_;
    if (aux == NULL) {
        MM->free(aux);
        return NULL;
    }
    
    // ALopezESAT: This part is a bit chaotic, you might want to rewrite this after giving it a think.
    // It also has memory leaks.
    MemoryNode* countaux = list->head_;
    MemoryNode* deleteaux = list->head_;
    void* data = list->head_->data_;
    int count = 0;

        if (position == 0) {
            aux = list->head_->next_;
            data = list->head_->data_;
            MM->free(list->head_);
            list->head_ = aux;

        }
        else {
            if(position+1<list->length_-1){
                
                while (count < position - 1) {
                    countaux = countaux->next_;
                    count++;
                }
                aux = countaux;
                
                deleteaux = countaux->next_;

               aux->next_ = deleteaux->next_;
               data = deleteaux->data_;
               MM->free(deleteaux);
            
            }
            else {
                while (count < position - 1) {
                    countaux = countaux->next_;
                    count++;
                }
                data = list->tail_->data_;
                MM->free(list->tail_);
                list->tail_ = countaux;
                countaux->next_ = NULL;
                

            }
        }   
    list->length_--;

    return data;
}

s16 LIST_concat(List* list, const List* list_src) {

    if(list_src==NULL|| list == NULL)
        {
    
        return kErrorCode_StorageNull;
    }

    MemoryNode* current_src = list_src->head_;

    while (current_src != NULL) {

        MemoryNode* new_node = MM->malloc(sizeof(MemoryNode));
        if (new_node == NULL) {
            MM->free(new_node);
            return kErrorCode_StorageNull;
        }

        u8* tmp = MM->malloc(current_src->size_);
        if (NULL == tmp) {
            return kErrorCode_MallocNull;
        }

        u8* aux = (u8*)current_src->data_;
        for (s32 i = 0; i < current_src->size_; i++) {
            tmp[i] = aux[i];
        }

        new_node->data_ = tmp;
        new_node->size_ = current_src->size_;
        new_node->next_ = NULL;

        if (NULL == list->head_) {
            list->head_ = new_node;
            list->tail_ = new_node;
        }
        else {
            
            list->tail_->next_ = new_node;
            list->tail_ = new_node;
        }

        current_src = current_src->next_;
    }

    list->length_ += list_src->length_;
    list->capacity_ += list_src->capacity_;

    return kErrorCode_Ok;
}

s16 LIST_traverse(const List* list, void (*callback)(MemoryNode*)) {
    
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }
    
    MemoryNode* countaux = list->head_;

    for (s16 i = 0; i < list->length_-1; i++) {
        
        callback(countaux);
        countaux = countaux->next_;

    }

    return kErrorCode_Ok;
}


void LIST_print(List* list) {

    if (NULL == list) {
        printf("\t[List Info] list: NULL\n");
        return;
    }

    // ALopezESAT: There are some casts missing.
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
    int count = 0;

    while (currentNode != NULL) {
        printf("\t  [List Info] Storage #%d\n", count);
        // ALopezESAT: There are some casts missing.
        printf("\t      [Node info] Address: %p\n", currentNode);
        printf("\t      [Node info] Size: %d\n", currentNode->size_);
        printf("\t      [Node info] Data Address: %p\n", currentNode->data_);
        printf("\t      [Node info] Data Content: %s\n", currentNode->data_);

        printf("\t      [Node info] Next address: %p\n", currentNode->next_);

        currentNode = currentNode->next_;
        count++;
    }
}






