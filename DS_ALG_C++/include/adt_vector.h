// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "adt_memory_node.h"

class adt_vector_s {

public:

	u16 head_;
	u16 tail_; // Corresponds to the first free place of the vector
	u16 capacity_;
	memory_node_s *storage_;

	adt_vector_s();
	~adt_vector_s();
	
	s16 destroy(adt_vector_s *vector);	// Destroys the vector and its data

	s16 softReset(adt_vector_s *vector);

	s16 reset(adt_vector_s *vector);

	s16 resize(adt_vector_s *vector, u16 new_size);

	u16 capacity(adt_vector_s *vector);

	u16 length(adt_vector_s *vector);

	boolean isEmpty(adt_vector_s *vector);

	boolean isFull(adt_vector_s *vector);

	void* first(adt_vector_s *vector); 

	void* last(adt_vector_s *vector); 

	void* at(adt_vector_s *vector, u16 position);

	s16 insertFirst(adt_vector_s *vector, void *data, u16 bytes); 

	s16 insertLast(adt_vector_s *vector, void *data, u16 bytes); 

	s16 insertAt(adt_vector_s *vector, void *data, u16 bytes, u16 position); 

	void* extractFirst(adt_vector_s *vector);

	void* extractLast(adt_vector_s *vector);

	void* extractAt(adt_vector_s *vector, u16 position);

	s16 concat(adt_vector_s *vector, adt_vector_s *vector_src); 

	s16 traverse(adt_vector_s *vector, void (*callback)(memory_node_s*));

	void print(adt_vector_s *vector);
};

//adt_vector_s* VECTOR_create(u16 capacity);

#endif //__ADT_VECTOR_H__
