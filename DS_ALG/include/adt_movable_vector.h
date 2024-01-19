// adt_movable_MovableVector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MOVABLE_VECTOR_H__
#define __ADT_MOVABLE_VECTOR_H__

#include "adt_memory_node.h"

typedef struct adt_movable_vector_s {
	u16 head_;
	u16 tail_; // Corresponds to the first free place of the MovableVector
	u16 capacity_;
	MemoryNode *storage_;
	struct movable_vector_ops_s *ops_;
} MovableVector;

struct movable_vector_ops_s {

	s16 (*destroy)(MovableVector *vector);

	s16 (*softReset)(MovableVector *vector);

	s16 (*reset)(MovableVector *vector);

	s16 (*resize)(MovableVector *vector, u16 new_size);

	u16 (*capacity)(MovableVector *vector);	

	u16 (*length)(MovableVector *vector);

	boolean (*isEmpty)(MovableVector *vector);

	boolean (*isFull)(MovableVector *vector);

	void* (*first)(MovableVector *vector); 

	void* (*last)(MovableVector *vector); 

	void* (*at)(MovableVector *vector, u16 position);

	s16 (*insertFirst)(MovableVector *vector, void *data, u16 bytes); 

	s16 (*insertLast)(MovableVector *vector, void *data, u16 bytes); 

	s16 (*insertAt)(MovableVector *vector, void *data, u16 bytes, u16 position); 

	// Extraction
	void* (*extractFirst)(MovableVector *vector);

  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(MovableVector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(MovableVector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */


	void* (*extractLast)(MovableVector *vector);

	void* (*extractAt)(MovableVector *vector, u16 position);

	// Miscellaneous s16 (*concat)(Vector *vector, Vector *vector_src); 
	s16 (*concat)(MovableVector *vector, MovableVector *vector_src);

	s16 (*traverse)(MovableVector *vector, void (*callback)(MemoryNode *)); 

	void (*print)(MovableVector *vector);
};

MovableVector* MOVABLE_VECTOR_create(u16 capacity); // Creates a new MovableVector
#endif //__ADT_MOVABLE_VECTOR_H__
