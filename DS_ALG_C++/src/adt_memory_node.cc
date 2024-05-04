// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

static s16 MEMNODE_initWithoutCheck(memory_node_s *node);	// inits a MN with no checks

memory_node_s::memory_node_s() {
    data_ = NULL;
    size_ = 0;
    next_ = NULL;
    previous_ = NULL;
}
memory_node_s::~memory_node_s() {}

// Memory Node Definitions


s16 MEMNODE_createFromRef(memory_node_s **node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
  *node = new  memory_node_s();
  
  if (NULL == *node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  return kErrorCode_Ok;
}

s16 MEMNODE_createLite(memory_node_s* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    node->data_ = NULL;
    node->size_ = 0;
    node->next_ = NULL;
    node->previous_ = NULL;

    return kErrorCode_Ok;
}

s16 MEMNODE_initWithoutCheck(memory_node_s *node) {
  node->data_ = NULL;
  node->size_ = 0;
  return kErrorCode_Ok;
}


void* memory_node_s::data(memory_node_s* node)
{
    if (NULL == node) {
          return NULL;
    }

    return node->data_;
}

u16	memory_node_s::size(memory_node_s *node) { // returns data size
  if (NULL == node) {
      return 0;
  }
  return node->size_;
}

s16 memory_node_s::setData(memory_node_s* node, void* src, u16 bytes) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == src) {
        return kErrorCode_SrcNull;
    }
    if (0 == bytes) {
        return kErrorCode_BytesZero;
    }

    node->data_ = src;
    node->size_ = bytes;
    return kErrorCode_Ok;
}

s16 memory_node_s::reset(memory_node_s* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
      return kErrorCode_DataNull;
    }
    delete node->data_;
    node->data_ = NULL;
    node->size_ = 0;
    return kErrorCode_Ok;
}

s16 memory_node_s::softReset(memory_node_s* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
        return kErrorCode_DataNull;
    }

    node->data_ = NULL;
    node->size_ = 0;
    return kErrorCode_Ok;
}

s16 memory_node_s::free(memory_node_s* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL != node->data_) {
        delete node->data_;
    }
    delete node;
    return kErrorCode_Ok;
}

s16 memory_node_s::softFree(memory_node_s* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    delete node;

    return kErrorCode_Ok;
}

s16 memory_node_s::memSet(memory_node_s* node, u8 value) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
        return kErrorCode_DataNull;
    }

    u8* aux = (u8*)node->data_;

    for (s32 i = 0; i < node->size_; i++) {
        aux[i] = value;
    }

    return kErrorCode_Ok;
}

s16 memory_node_s::memCopy(memory_node_s* node, void* src, u16 bytes) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    
    if (NULL == src) {
        return kErrorCode_SrcNull;
    }
    if (0 == bytes) {
        return kErrorCode_BytesZero;
    }

    u8* tmp = new u8[bytes];
    if (NULL == tmp) {
        return kErrorCode_MallocNull;
    }

    u8* aux = (u8*)src;
    for (s32 i = 0; i < bytes; i++) {
        tmp[i] = aux[i];
    }
    if (NULL != node->data_) {
        delete node->data_;
    }
    node->data_ = tmp;
    node->size_ = bytes;

    return kErrorCode_Ok;
}

s16 memory_node_s::memConcat(memory_node_s* node, void* src, u16 bytes) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
        return kErrorCode_DataNull;
    }
    if (0 == node->size_) {
        return kErrorCode_SizeNull;
    }

    u16 new_size = node->size_ + bytes;

    u8* tmp = new u8[new_size];
    if (NULL == tmp) {
        return kErrorCode_MallocNull;
    }

    u8* aux_src = (u8*)src;
    u8* aux_data = (u8*)node->data_;

    for (s32 i = 0; i < new_size; i++) {
        if (i < node->size_) {
            tmp[i] = aux_data[i];
        }
        else {
            tmp[i] = aux_src[i - node->size_];
        }
    }

    delete node->data_;
    node->data_ = tmp;
    node->size_ = new_size;

    return kErrorCode_Ok;
}

s16 memory_node_s::memMask(memory_node_s* node, u8 mask) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
        return kErrorCode_DataNull;
    }
    if (0 == node->size_) {
        return kErrorCode_SizeNull;
    }

    u8* aux_data = (u8*)node->data_;

    for (s16 i = 0; i < node->size_; i++) {
        aux_data[i] = aux_data[i] & mask;
    }

    return kErrorCode_Ok;
}

void memory_node_s::print(memory_node_s* node) {
    if (NULL == node) {
        printf("\t[Node Info] Address: NULL\n");
        return;
    }
    printf("\t[Node Info] Address: %p\n", node);
    printf("\t[Node Info] Size: %d\n", node->size_);
    if (NULL == node->data_) {
        printf("\t[Node Info] Data Address: NULL\n");
        return ;
    }
    printf("\t[Node Info] Data Address: %p\n", node->data_);
    printf("\t[Node Info] Data Content: ");
    u8* aux = (u8*)node->data_;
    for (int i = 0; i < node->size_; i++) {
        printf("%c", aux[i]);
    }
    printf("\n");
}

                                
memory_node_s* memory_node_s::next(memory_node_s* node) {

    if (NULL == node) {
        return NULL;
    }

    return node->next_;
}

memory_node_s* memory_node_s::previous(memory_node_s* node) {
    if (NULL == node) {
        return NULL;
    }

    return node->previous_;
}

void memory_node_s::setNext(memory_node_s* node, memory_node_s* next_node){
   
    if (NULL == node) {
        return;
    }

    node->next_ = next_node->next_;
}

void memory_node_s::setPrevious(memory_node_s* node, memory_node_s* previous_node){
    if (NULL == node) {
        return;
    }

    node->previous_ = previous_node->previous_;
}


