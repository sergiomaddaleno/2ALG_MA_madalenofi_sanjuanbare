
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"

#include "adt_queue.h"
#include "adt_list.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Static prototypes
static s16 QUEUE_destroy(List* list);
static s16 QUEUE_reset(List* list);
static s16 QUEUE_softReset(List* list);
static s16 QUEUE_resize(List* list, u16 new_size);   

static u16 QUEUE_capacity(const List* list);
static u16 QUEUE_length(const List* list);
static s16 QUEUE_isEmpty(const List* list);
static s16 QUEUE_isFull(const List* list);

static void* QUEUE_first(const List* list);
static void* QUEUE_last(const List* list);
static void* QUEUE_at(const List* list, u16 position);

static s16 QUEUE_insertFirst(List* list, void* data, u16 bytes);
static s16 QUEUE_insertLast(List* list, void* data, u16 bytes);
static s16 QUEUE_insertAt(List* list, void* data, u16 bytes, u16 position);

static void* QUEUE_extractFirst(List* list); 
static void* QUEUE_extractLast(List* list); 
static void* QUEUE_extractAt(List* list, u16 position); 

static s16 QUEUE_concat(List* list, const List* list_src); 
static s16 QUEUE_traverse(const List* list, void (*callback)(MemoryNode*));

static void QUEUE_print(List* list);

// Memory Node's API Definitions
struct queue_ops_s queue_ops = {
    .destroy = QUEUE_destroy,
    .reset = QUEUE_reset,
    .softReset = QUEUE_softReset,
    .resize = QUEUE_resize,
    .capacity = QUEUE_capacity,
    .length = QUEUE_length,
    .isEmpty = QUEUE_isEmpty,
    .isFull = QUEUE_isFull,
    .first = QUEUE_first,
    .last = QUEUE_last,
    .at = QUEUE_at,
    .insertFirst = QUEUE_insertFirst,
    .insertLast = QUEUE_insertLast,
    .insertAt = QUEUE_insertAt,
    .extractFirst = QUEUE_extractFirst,
    .extractLast = QUEUE_extractLast,
    .extractAt = QUEUE_extractAt,
    .concat = QUEUE_concat,
    .traverse = QUEUE_traverse,
    .print = QUEUE_print

};

List* QUEUE_create(u16 capacity) {

}

s16 QUEUE_destroy(List* list) {

    
}

s16 QUEUE_reset(List* list) {


}

s16 QUEUE_softReset(List* list) {

   
}

s16 QUEUE_resize(List* list, u16 new_size) {

}

u16 QUEUE_capacity(const List* list) {
   
}

u16 QUEUE_length(const List* list) {
    
}

s16 QUEUE_isEmpty(const List* list) {
    
}

s16 QUEUE_isFull(const List* list) {
    
}

void* QUEUE_first(const List* list){

}

void* QUEUE_last(const List* list){

}

void* QUEUE_at(const List* list, u16 position){

}

s16 QUEUE_insertFirst(List* list, void* data, u16 bytes){

}

s16 QUEUE_insertLast(List* list, void* data, u16 bytes){


}

s16 QUEUE_insertAt(List* list, void* data, u16 bytes, u16 position) {
   
}

void* QUEUE_extractFirst(List* list) {
   
}

void* QUEUE_extractLast(List* list) {
   
}

void* QUEUE_extractAt(List* list, u16 position){

  
}

s16 QUEUE_concat(List* list, const List* list_src) {

  
}

s16 QUEUE_traverse(const List* list, void (*callback)(MemoryNode*)) {
    
   
}


void QUEUE_print(List* list) {

   
}






