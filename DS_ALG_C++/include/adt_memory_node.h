// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "EDK_MemoryManager/edk_platform_types.h"

// Memory Node type
class memory_node_s{
public:
	memory_node_s();
	~memory_node_s();

	void* data_;
	u16 size_;
	memory_node_s* next_;
	memory_node_s* previous_;

	void* data(memory_node_s* node);

	s16 setData(memory_node_s* node, void* src, u16 bytes);

	u16 size(memory_node_s* node);

	s16 reset(memory_node_s* node);

	s16 softReset(memory_node_s* node);

	s16 free(memory_node_s* node);

	s16 softFree(memory_node_s* node);

	s16 memSet(memory_node_s* node, u8 value);

	s16 memCopy(memory_node_s* node, void* src, u16 bytes);

	s16 memConcat(memory_node_s* node, void* src, u16 bytes);

	s16 memMask(memory_node_s* node, u8 mask);

	void print(memory_node_s* node);

	memory_node_s* next(memory_node_s* node);

	memory_node_s* previous(memory_node_s* node);

	void setNext(memory_node_s* node, memory_node_s* next_node);

	void setPrevious(memory_node_s* node, memory_node_s* previous_node);
};

memory_node_s* MEMNODE_create();

s16 MEMNODE_createFromRef(memory_node_s** node);

s16 MEMNODE_createLite(memory_node_s* node);

#endif // __ADT_MEMORY_NODE_H__
