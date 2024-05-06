
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"
#include "adt_memory_node.h"
#include "EDK_MemoryManager/edk_memory_manager.h"



adt_list_s::adt_list_s(u16 capacity)
{
   
     head_=NULL;
     tail_=NULL;
     length_=0;
     capacity_=capacity;

}

adt_list_s::~adt_list_s()
{
}

s16 adt_list_s::destroy(adt_list_s* list)
{
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    memory_node_s* current = list->head_;
    memory_node_s* next;

    while (current != NULL) {
        next = current->next_;

        delete[] current->data_;
        delete[] current;
        current = next;
    }

    //delete[] list;

    return kErrorCode_Ok;
}

s16 adt_list_s::reset(adt_list_s* list)
{
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    memory_node_s* aux = list->head_;
    int i = 0;
    while (NULL != list->head_) {
        if (NULL != list->head_->data_) {
            list->head_[i].reset(&list->head_[i]);
         
        }

        aux = list->head_->next_;
        if (list->head_ != NULL) {
           // delete[] list->head_;
        }
        list->head_ = aux;
        i++;
    }

    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;

    return  kErrorCode_Ok;
}

s16 adt_list_s::softReset(adt_list_s* list)
{
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    memory_node_s* aux = list->head_;

    while (NULL != list->head_) {

        aux = list->head_->next_;
        delete list->head_;

        list->head_ = aux;
    }

    list->length_ = 0;
    list->head_ = NULL;
    list->tail_ = NULL;

    return  kErrorCode_Ok;
}

s16 adt_list_s::resize(adt_list_s* list, u16 new_size)
{
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

        memory_node_s* countaux = list->head_;
        memory_node_s* aux = list->head_;

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

             

               delete[] countaux->data_;
                //delete[] countaux;
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
                delete[] countaux->data_;
                delete[] countaux;

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

u16 adt_list_s::capacity(const adt_list_s* list)
{
    if (NULL == list) {
        return 0;
    }
    return list->capacity_;
}

u16 adt_list_s::length(const adt_list_s* list)
{
    if (NULL == list) {
        return 0;
    }
    return list->length_;
}

s16 adt_list_s::isEmpty(const adt_list_s* list)
{
    if (NULL == list) {
        return 0;
    }
    return list->length_ == 0;
}

s16 adt_list_s::isFull(const adt_list_s* list)
{
    if (NULL == list) {
        return 0;
    }
    return list->length_ == list->capacity_;
}

void* adt_list_s::first(const adt_list_s* list)
{
    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->head_) {
        return NULL;
    }

    return list->head_->data_;
}

void* adt_list_s::last(const adt_list_s* list)
{
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

void* adt_list_s::at(const adt_list_s* list, u16 position)
{
    if (NULL == list) {
        return NULL;
    }

    if (NULL == list->head_) {
        return NULL;
    }

    memory_node_s* countaux = list->head_;
    int count = 0;

    while (count < position) {
        countaux = countaux->next_;
        count++;
    }

    return countaux->data_;
}

s16 adt_list_s::insertFirst(adt_list_s* list, void* data, u16 bytes)
{
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
        memory_node_s* aux = new memory_node_s[1];
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

        memory_node_s* aux = new memory_node_s[1];
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

s16 adt_list_s::insertLast(adt_list_s* list, void* data, u16 bytes)
{
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
        memory_node_s* aux = new memory_node_s[1];

        aux->next_ = NULL;
        list->head_ = aux;
        list->tail_ = aux;

        aux->data_ = data;
        aux->size_ = bytes;

        list->length_++;
    }
    else {
        memory_node_s* aux = new memory_node_s[1];

        list->tail_->next_ = aux;
        list->tail_ = aux;
        list->tail_->next_ = NULL;

        aux->data_ = data;
        aux->size_ = bytes;

        list->length_++;
    }
    return kErrorCode_Ok;
}

s16 adt_list_s::insertAt(adt_list_s* list, void* data, u16 bytes, u16 position)
{
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

    memory_node_s* aux = new memory_node_s[1];
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
            memory_node_s* countaux = list->head_;
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

void* adt_list_s::extractFirst(adt_list_s* list)
{
    if (NULL == list) {
        return NULL;
    }

    if (isEmpty(list)) {
        return NULL;
    }

    if (list->head_ == NULL) {

        return NULL;
    }

    memory_node_s* aux = list->head_->next_;
    void* data = list->head_->data_;

    delete[] list->head_;
    
    list->head_ = aux;
    list->length_--;

    return data;
}

void* adt_list_s::extractLast(adt_list_s* list)
{
    if (list == NULL || isEmpty(list) || list->head_ == NULL) {
        return NULL;
    }

    void* data = list->tail_->data_;

    if (list->length_ == 1) {
        delete[] list->tail_;
        list->tail_ = NULL;
        list->head_ = NULL;
    }
    else {
        memory_node_s* secondToLast = list->head_;

        while (secondToLast->next_ != list->tail_) {
            secondToLast = secondToLast->next_;
        }

        delete[] list->tail_;
        list->tail_ = secondToLast;
        list->tail_->next_ = NULL;
    }

    list->length_--;

    return data;
}

void* adt_list_s::extractAt(adt_list_s* list, u16 position)
{
    if (NULL == list) {
        return NULL;
    }

    if (isEmpty(list)) {
        return NULL;
    }

    if (position >= list->length_) {
        position = list->length_;
    }

    if (NULL == list->head_) {

        return NULL;
    }

    memory_node_s* aux = list->head_->next_;
    memory_node_s* countaux = list->head_;
    memory_node_s* deleteaux = list->head_;
    void* data = list->head_->data_;

    int count = 0;

    if (position == 0) {
        aux = list->head_->next_;
        data = list->head_->data_;

        delete[] list->head_;
        list->head_ = aux;
    }
    else {
        if (position + 1 < list->length_ - 1) {

            while (count < position - 1) {
                countaux = countaux->next_;
                count++;
            }
            aux = countaux;

            deleteaux = countaux->next_;
            aux->next_ = deleteaux->next_;

            data = deleteaux->data_;
            delete[] deleteaux;
        }
        else {

            while (count < position - 1) {
                countaux = countaux->next_;
                count++;
            }

            data = list->tail_->data_;
            delete[] list->tail_;

            list->tail_ = countaux;
            countaux->next_ = NULL;
        }
    }
    list->length_--;

    return data;
}

s16 adt_list_s::concat(adt_list_s* list, const adt_list_s* list_src)
{
    if (list_src == NULL || list == NULL)
    {

        return kErrorCode_StorageNull;
    }

    memory_node_s* current_src = list_src->head_;

    while (current_src != NULL) {
        memory_node_s* new_node = new memory_node_s[sizeof(memory_node_s)];

        if (new_node == NULL) {
            delete[] new_node;
            return kErrorCode_StorageNull;
        }

        u8* tmp = new u8[current_src->size_];
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

s16 adt_list_s::traverse(const adt_list_s* list, void(*callback)(memory_node_s*))
{
    if (NULL == list) {
        return kErrorCode_ListNull;
    }

    if (NULL == list->head_) {
        return kErrorCode_StorageNull;
    }

    memory_node_s* countaux = list->head_;

    for (s16 i = 0; i < list->length_ - 1; i++) {

        callback(countaux);
        countaux = countaux->next_;
    }

    return kErrorCode_Ok;
}

void adt_list_s::print(adt_list_s* list)
{
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

    memory_node_s* currentNode = list->head_;
    int count = 0;

    while (currentNode != NULL) {
        printf("\t  [List Info] Storage #%d\n", count);
        // ALopezESAT: There are some casts missing.
        printf("\t      [Node info] Address: %p\n", currentNode);
        printf("\t      [Node info] Size: %d\n", currentNode->size_);
        printf("\t      [Node info] Data Address: %p\n", currentNode->data_);
        printf("\t      [Node info] Data Content: %s\n", (char*)currentNode->data_);

        printf("\t      [Node info] Next address: %p\n", currentNode->next_);

        currentNode = currentNode->next_;
        count++;
    }
}
