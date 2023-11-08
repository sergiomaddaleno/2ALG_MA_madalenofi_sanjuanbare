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


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node);	// inits a MN with no checks
static void* MEMNODE_data(MemoryNode *node);	// returns a reference to data_
static u16 MEMNODE_size(MemoryNode *node);		// returns data size

static s16 MEMNODE_SetData(MemoryNode *node, void* src, u16 bytes);
static s16 MEMNODE_reset(MemoryNode* node);     // reset content of memory node
static s16 MEMNODE_softReset(MemoryNode* node); // reset content of memory node without freeing the data
static s16 MEMNODE_free(MemoryNode* node);		// free memory, both data and node
static s16 MEMNODE_softFree(MemoryNode* node);	// free only the node (its mmory, not its data)

static s16 MEMNODE_memSet(MemoryNode* node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes);
static s16 MEMNODE_memMask(MemoryNode* node, u8 mask);

static void MEMNODE_print(MemoryNode* node);

// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops = { .data = MEMNODE_data,
                                             .size = MEMNODE_size,
                                             .setData = MEMNODE_SetData,
                                             .reset = MEMNODE_reset,
                                             .softReset = MEMNODE_softReset,
                                             .free = MEMNODE_free,
                                             .softFree = MEMNODE_softFree,
                                             .memSet = MEMNODE_memSet,
                                             .memCopy = MEMNODE_memCopy,
                                             .memConcat = MEMNODE_memConcat,
                                             .memMask = MEMNODE_memMask,
                                             .print = MEMNODE_print,
};

// Memory Node Definitions
MemoryNode* MEMNODE_create() {
  MemoryNode *node = MM->malloc(sizeof(MemoryNode));
  if (NULL == node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_initWithoutCheck(node);
  return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
  *node = MEMNODE_create();
  
  if (NULL == *node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  return kErrorCode_Ok;
}

s16 MEMNODE_initWithoutCheck(MemoryNode *node) {
  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;
  return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) { // returns a reference to data_
  if (NULL == node) {
      return NULL;
  }
  return node->data_;
}

u16	MEMNODE_size(MemoryNode *node) { // returns data size
  if (NULL == node) {
      return 0;
  }
  return node->size_;
}

s16 MEMNODE_SetData(MemoryNode* node, void* src, u16 bytes) {
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

s16 MEMNODE_reset(MemoryNode* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
      return kErrorCode_DataNull;
    }
    MM->free(node->data_);
    node->data_ = NULL;
    node->size_ = 0;
    return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode* node) {
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

s16 MEMNODE_free(MemoryNode* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    if (NULL != node->data_) {
        MM->free(node->data_);
    }
    MM->free(node);
    return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode* node) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    MM->free(node);

    return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode* node, u8 value) {
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

s16 MEMNODE_memCopy(MemoryNode* node, void* src, u16 bytes) {
    if (NULL == node) {
        return kErrorCode_NodeNull;
    }
    
    if (NULL == src) {
        return kErrorCode_SrcNull;
    }
    if (0 == bytes) {
        return kErrorCode_BytesZero;
    }

    u8* tmp = MM->malloc(bytes);
    if (NULL == tmp) {
        return kErrorCode_MallocNull;
    }

    u8* aux = (u8*)src;
    for (s32 i = 0; i < bytes; i++) {
        tmp[i] = aux[i];
    }
    if (NULL != node->data_) {
        MM->free(node->data_);
    }
    node->data_ = tmp;
    node->size_ = bytes;

    return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode* node, void* src, u16 bytes) {
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

    u8* tmp = MM->malloc(new_size);
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

    MM->free(node->data_);
    node->data_ = tmp;
    node->size_ = new_size;

    return kErrorCode_Ok;
}


s16 MEMNODE_memMask(MemoryNode* node, u8 mask) {
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


void MEMNODE_print(MemoryNode* node) {
    if (NULL == node) {
        
        return kErrorCode_NodeNull;
    }
    if (NULL == node->data_) {
        
        return kErrorCode_DataNull;
    }
    if (0 == node->size_) {
        return kErrorCode_SizeNull;
    }
   
    printf("\n[Node info] Adress: %p \n", &node);
    printf("[Node info] Size: %d \n", node->size_);
    printf("[Node info] Data Address: %p \n", &node->data_);
    printf("[Node info] Data content:");
    u8* aux_data = (u8*)node->data_;
    for (s8 i = 0; i < node->size_;i++) {
        
        printf("%c", aux_data[i]);
    }
    
    printf("\n");
}