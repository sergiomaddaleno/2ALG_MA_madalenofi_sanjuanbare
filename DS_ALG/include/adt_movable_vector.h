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

	/**
 * @brief Destroys a MovableVector and frees its associated memory.
 *
 * This function deallocates the memory associated with a MovableVector,
 * including the storage for its elements and the MovableVector structure itself.
 * It also frees any dynamically allocated data within the memory nodes of the vector.
 *
 * @param vector A pointer to the MovableVector to be destroyed.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The MovableVector was successfully destroyed.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_NodeNull: The storage pointer of the MovableVector is NULL.
 */
	s16 (*destroy)(MovableVector *vector);

	/**
 * @brief Soft resets a MovableVector, clearing all elements without deallocating memory.
 *
 * This function resets a MovableVector to its initial state, clearing all elements
 * without deallocating memory. It sets the head and tail pointers to the middle
 * of the vector's capacity and resets the size of each memory node to zero.
 *
 * @param vector A pointer to the MovableVector to be soft-reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The MovableVector was successfully soft-reset.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 */
	s16 (*softReset)(MovableVector *vector);

	/**
 * @brief Resets a MovableVector, clearing all elements and deallocating associated memory.
 *
 * This function resets a MovableVector to its initial state, clearing all elements
 * and deallocating associated memory. It resets each memory node using its reset operation,
 * then sets the head and tail pointers to the middle of the vector's capacity.
 *
 * @param vector A pointer to the MovableVector to be reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The MovableVector was successfully reset.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 */
	s16 (*reset)(MovableVector *vector);

	/**
 * @brief Resizes a MovableVector to a new specified size.
 *
 * This function resizes a MovableVector to a new specified size. If the new size
 * is greater than the current capacity, the vector's capacity is increased and the
 * existing elements are copied to the new storage. If the new size is smaller than
 * the current capacity, the vector is truncated, and excess elements are removed.
 * Memory allocation and deallocation are handled internally.
 *
 * @param vector A pointer to the MovableVector to be resized.
 * @param new_size The new size to resize the MovableVector to.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The MovableVector was successfully resized.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_NodeNull: The storage pointer of the MovableVector is NULL.
 *         - kErrorCode_SizeNull: The new size provided is 0.
 *         - kErrorCode_EqualCapacity: The new size is equal to the current capacity.
 *         - kErrorCode_MallocNull: Memory allocation failed while resizing the vector.
 */
	s16 (*resize)(MovableVector *vector, u16 new_size);

	/**
 * @brief Retrieves the capacity of a MovableVector.
 *
 * This function returns the capacity of a MovableVector, which represents the maximum number
 * of elements the vector can currently hold without resizing. The capacity is calculated as
 * half of the internal storage capacity of the vector.
 *
 * @param vector A pointer to the MovableVector.
 * @return The capacity of the MovableVector. If the provided pointer to the MovableVector is NULL,
 *         it returns 0.
 */
	u16 (*capacity)(MovableVector *vector);	

	/**
 * @brief Retrieves the number of elements in a MovableVector.
 *
 * This function returns the number of elements currently stored in a MovableVector.
 * It calculates the length by subtracting the index of the head from the index of the tail.
 *
 * @param vector A pointer to the MovableVector.
 * @return The number of elements in the MovableVector. If the provided pointer to the MovableVector
 *         is NULL, it returns 0.
 */
	u16 (*length)(MovableVector *vector);

	/**
 * @brief Checks if a MovableVector is empty.
 *
 * This function checks if a MovableVector is empty by comparing the indices of its head and tail.
 * If the head and tail indices are equal, indicating no elements in the vector, it returns True.
 * Otherwise, it returns False.
 *
 * @param vector A pointer to the MovableVector.
 * @return True if the MovableVector is empty, False otherwise. If the provided pointer to the
 *         MovableVector is NULL, it returns False.
 */
	boolean (*isEmpty)(MovableVector *vector);

	/**
 * @brief Checks if a MovableVector is full.
 *
 * This function checks if a MovableVector is full by comparing the number of elements
 * currently stored in the vector with its capacity. If the number of elements is equal
 * to the capacity, indicating that the vector is full, it returns True. Otherwise, it returns False.
 *
 * @param vector A pointer to the MovableVector.
 * @return True if the MovableVector is full, False otherwise. If the provided pointer to the
 *         MovableVector is NULL, it returns False.
 */
	boolean (*isFull)(MovableVector *vector);

	/**
 * @brief Retrieves the first element of a MovableVector.
 *
 * This function retrieves the first element of a MovableVector, which is the element at the head
 * of the vector's storage. If the MovableVector is empty or if the provided pointer to the vector
 * is NULL, it returns NULL.
 *
 * @param vector A pointer to the MovableVector.
 * @return A pointer to the first element of the MovableVector. If the MovableVector is empty or if
 *         the provided pointer to the MovableVector is NULL, it returns NULL.
 */
	void* (*first)(MovableVector *vector); 

	/**
 * @brief Retrieves the last element of a MovableVector.
 *
 * This function retrieves the last element of a MovableVector, which is the element at the tail
 * of the vector's storage. If the MovableVector is empty, or if the provided pointer to the vector
 * is NULL, or if the tail index is at the beginning of the storage, it returns NULL.
 *
 * @param vector A pointer to the MovableVector.
 * @return A pointer to the last element of the MovableVector. If the MovableVector is empty, or if
 *         the provided pointer to the MovableVector is NULL, or if the tail index is at the beginning
 *         of the storage, it returns NULL.
 */
	void* (*last)(MovableVector *vector); 

	/**
 * @brief Retrieves the element at a specified position in a MovableVector.
 *
 * This function retrieves the element at the specified position in a MovableVector.
 * The position is relative to the head of the vector's storage. If the provided pointer
 * to the vector is NULL, if the storage pointer of the vector is NULL, or if the position
 * is negative, it returns NULL.
 *
 * @param vector A pointer to the MovableVector.
 * @param position The position of the element to retrieve, relative to the head of the vector's storage.
 * @return A pointer to the element at the specified position in the MovableVector.
 *         If the provided pointer to the MovableVector is NULL, if the storage pointer
 *         of the MovableVector is NULL, or if the position is negative, it returns NULL.
 */
	void* (*at)(MovableVector *vector, u16 position);

	/**
 * @brief Inserts an element at the beginning of a MovableVector.
 *
 * This function inserts an element at the beginning of a MovableVector. It shifts existing elements
 * to make space for the new element. If the MovableVector is full, if the provided pointer to the
 * vector is NULL, if the storage pointer of the vector is NULL, if the provided data pointer is NULL,
 * or if the provided size of data is less than or equal to 0, it returns an error code.
 *
 * @param vector A pointer to the MovableVector.
 * @param data A pointer to the data to be inserted.
 * @param bytes The size of the data to be inserted, in bytes.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The element was successfully inserted.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 *         - kErrorCode_DataNull: The provided data pointer is NULL.
 *         - kErrorCode_BytesZero: The provided size of data is less than or equal to 0.
 *         - kErrorCode_VectorFull: The MovableVector is full and cannot accommodate more elements.
 */
	s16 (*insertFirst)(MovableVector *vector, void *data, u16 bytes);

	/**
 * @brief Inserts an element at the end of a MovableVector.
 *
 * This function inserts an element at the end of a MovableVector. If the provided pointer
 * to the vector is NULL, if the storage pointer of the vector is NULL, if the provided data
 * pointer is NULL, or if the number of bytes is less than or equal to 0, it returns an error code.
 * If the vector is full, it returns an error code indicating that the vector is full. Otherwise,
 * it inserts the element at the end of the vector's storage and increments the tail pointer.
 *
 * @param vector A pointer to the MovableVector.
 * @param data A pointer to the data to be inserted.
 * @param bytes The number of bytes of the data to be inserted.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The element was successfully inserted at the end of the vector.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 *         - kErrorCode_DataNull: The provided data pointer is NULL.
 *         - kErrorCode_BytesZero: The number of bytes is less than or equal to 0.
 *         - kErrorCode_VectorFull: The MovableVector is full and cannot insert more elements.
 */
	s16 (*insertLast)(MovableVector *vector, void *data, u16 bytes);

	/**
 * @brief Inserts an element at the specified position in a MovableVector.
 *
 * This function inserts an element at the specified position in a MovableVector.
 * If the provided pointer to the vector is NULL, if the storage pointer of the vector
 * is NULL, if the provided data pointer is NULL, or if the number of bytes is less than
 * or equal to 0, it returns an error code. If the vector is full, it returns an error code
 * indicating that the vector is full. The position is relative to the head of the vector's storage.
 * If the specified position is greater than or equal to the current tail index, the element
 * is inserted at the end of the vector. Otherwise, the elements at positions greater than or equal
 * to the specified position are shifted to the right to make space for the new element. The tail
 * pointer is then incremented to reflect the insertion.
 *
 * @param vector A pointer to the MovableVector.
 * @param data A pointer to the data to be inserted.
 * @param bytes The number of bytes of the data to be inserted.
 * @param position The position at which to insert the element, relative to the head of the vector's storage.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The element was successfully inserted at the specified position in the vector.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 *         - kErrorCode_DataNull: The provided data pointer is NULL.
 *         - kErrorCode_BytesZero: The number of bytes is less than or equal to 0.
 *         - kErrorCode_VectorFull: The MovableVector is full and cannot insert more elements.
 */
	s16 (*insertAt)(MovableVector *vector, void *data, u16 bytes, u16 position); 

	/**
 * @brief Extracts and returns the first element from a MovableVector.
 *
 * This function extracts and returns the first element from a MovableVector.
 * If the provided pointer to the vector is NULL, if the storage pointer of the vector
 * is NULL, or if the MovableVector is empty, it returns NULL. Otherwise, it extracts
 * the first element from the vector, resets the memory node containing the element's data,
 * increments the head pointer, and returns a pointer to the extracted element's data.
 *
 * @param vector A pointer to the MovableVector.
 * @return A pointer to the data of the extracted first element from the MovableVector.
 *         If the provided pointer to the MovableVector is NULL, if the storage pointer
 *         of the MovableVector is NULL, or if the MovableVector is empty, it returns NULL.
 */
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

  /**
* @brief Extracts and returns the last element from a MovableVector.
*
* This function extracts and returns the last element from a MovableVector.
* If the provided pointer to the vector is NULL, if the storage pointer of the vector
* is NULL, if the MovableVector is empty, or if the tail index is at the beginning of
* the storage, it returns NULL. Otherwise, it extracts the last element from the vector,
* resets the memory node containing the element's data, decrements the tail pointer,
* and returns a pointer to the extracted element's data.
*
* @param vector A pointer to the MovableVector.
* @return A pointer to the data of the extracted last element from the MovableVector.
*         If the provided pointer to the MovableVector is NULL, if the storage pointer
*         of the MovableVector is NULL, if the MovableVector is empty, or if the tail index
*         is at the beginning of the storage, it returns NULL.
*/
	void* (*extractLast)(MovableVector *vector);

	/**
 * @brief Extracts and returns the element at the specified position from a MovableVector.
 *
 * This function extracts and returns the element at the specified position from a MovableVector.
 * If the provided pointer to the vector is NULL, if the storage pointer of the vector is NULL,
 * or if the MovableVector is empty, it returns NULL. If the specified position is greater than
 * or equal to the current tail index, the function extracts and returns the last element from
 * the vector. Otherwise, it extracts and returns the element at the specified position, resets
 * the memory node containing the element's data, shifts the subsequent elements to the left
 * to fill the gap, decrements the tail pointer, and returns a pointer to the extracted element's data.
 *
 * @param vector A pointer to the MovableVector.
 * @param position The position of the element to extract, relative to the head of the vector's storage.
 * @return A pointer to the data of the extracted element from the MovableVector.
 *         If the provided pointer to the MovableVector is NULL, if the storage pointer
 *         of the MovableVector is NULL, or if the MovableVector is empty, it returns NULL.
 */
	void* (*extractAt)(MovableVector *vector, u16 position);

	// Miscellaneous s16 (*concat)(Vector *vector, Vector *vector_src); 

	/**
 * @brief Concatenates two MovableVectors.
 *
 * This function concatenates the elements of two MovableVectors by appending
 * the elements of the source vector to the end of the destination vector. If either
 * of the provided pointers to the vectors is NULL, or if the storage pointer of either
 * vector is NULL, it returns an error code. Otherwise, it calculates the new capacity
 * required to accommodate all elements, resizes the destination vector accordingly,
 * copies the elements from the source vector to the destination vector, updates the tail
 * pointer of the destination vector, and returns an error code indicating success.
 *
 * @param vector A pointer to the destination MovableVector.
 * @param vector_src A pointer to the source MovableVector whose elements will be concatenated.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The concatenation operation was successful.
 *         - kErrorCode_VectorNull: Either the destination or source MovableVector pointer is NULL.
 *         - kErrorCode_NodeNull: The storage pointer of either the destination or source MovableVector is NULL.
 */
	s16 (*concat)(MovableVector *vector, MovableVector *vector_src);

	/**
 * @brief Traverses all elements of a MovableVector and applies a callback function to each element.
 *
 * This function traverses all elements of a MovableVector and applies a provided callback function
 * to each element. If the provided pointer to the vector is NULL or if the storage pointer of the vector
 * is NULL, it returns an error code. Otherwise, it iterates over the elements of the vector from the head
 * index to the tail index, and for each element, it invokes the provided callback function with a pointer
 * to the memory node containing the element's data. After traversing all elements, it returns an error code
 * indicating success.
 *
 * @param vector A pointer to the MovableVector to traverse.
 * @param callback A function pointer to the callback function to apply to each element.
 *                 The callback function should accept a pointer to a MemoryNode as its argument.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The traversal operation was successful.
 *         - kErrorCode_VectorNull: The provided pointer to the MovableVector is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the MovableVector is NULL.
 */
	s16 (*traverse)(MovableVector *vector, void (*callback)(MemoryNode *)); 

	/**
 * @brief Prints information about a MovableVector and its elements.
 *
 * This function prints information about a MovableVector and its elements to the standard output.
 * If the provided pointer to the vector is NULL, it prints a message indicating that the vector is NULL
 * and returns. Otherwise, it prints the address of the vector, the head and tail indices, the capacity,
 * and the address of the vector's operations structure. If the storage pointer of the vector is NULL,
 * it prints a message indicating that the storage is NULL and returns. Otherwise, it iterates over the
 * elements of the vector from the head index to the tail index and prints information about each element,
 * including its address, size, data address, and data content.
 *
 * @param vector A pointer to the MovableVector to print.
 */
	void (*print)(MovableVector *vector);
};

/**
 * @brief Creates a new MovableVector with the specified capacity.
 *
 * This function creates a new MovableVector with a specified capacity. The MovableVector
 * is a data structure capable of dynamic resizing, optimized for frequent insertions and
 * deletions at both ends.
 *
 * @param capacity The initial capacity of the MovableVector. Must be greater than 0.
 * @return A pointer to the newly created MovableVector, or NULL if memory allocation fails
 *         or if the specified capacity is less than or equal to 0.
 */
MovableVector* MOVABLE_VECTOR_create(u16 capacity); // Creates a new MovableVector
#endif //__ADT_MOVABLE_VECTOR_H__
