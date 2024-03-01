// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "adt_memory_node.h"

typedef struct adt_vector_s {
	u16 head_;
	u16 tail_; // Corresponds to the first free place of the vector
	u16 capacity_;
	MemoryNode *storage_;
	struct vector_ops_s *ops_;
} Vector;

struct vector_ops_s {

	/**
 * @brief Destroys a Vector and frees its allocated memory, including internal storage and elements.
 *
 * This function deallocates memory associated with the Vector structure, its internal storage,
 * and any allocated memory for individual elements within the storage.
 *
 * @param vector A pointer to the Vector to be destroyed.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_NodeNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_Ok if the destruction operation is successful.
 */
	s16 (*destroy)(Vector *vector);	// Destroys the vector and its data

	/**
 * @brief Performs a soft reset on a Vector by clearing data and sizes in its internal storage.
 *
 * This function resets each element in the Vector's internal storage by setting the data pointer
 * to NULL and the size to 0. The Vector's tail position is then set to 0, indicating an empty state.
 *
 * @param vector A pointer to the Vector to be soft-reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_Ok if the soft-reset operation is successful.
 */
  s16 (*softReset)(Vector *vector);

	/**
 * @brief Resets a Vector by invoking the reset operation on each element in its internal storage.
 *
 * This function resets each element in the Vector's internal storage using the reset operation
 * provided by the corresponding MemoryNode. The Vector's tail position is then set to 0,
 * indicating an empty state.
 *
 * @param vector A pointer to the Vector to be reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_Ok if the reset operation is successful.
 */
  s16 (*reset)(Vector *vector);

	/**
 * @brief Resizes the Vector to the specified new size.
 *
 * This function resizes the Vector's internal storage to the new size.
 * If the new size is smaller than the current size, it truncates the Vector.
 * If the new size is larger, it allocates new memory and copies existing elements.
 *
 * @param vector A pointer to the Vector to be resized.
 * @param new_size The new size to which the Vector should be resized.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_NodeNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_SizeNull if the new size is 0.
 *         - kErrorCode_Ok if the resizing operation is successful.
 */
	s16 (*resize)(Vector *vector, u16 new_size);

	// State queries
	/**
 * @brief Retrieves the capacity of the Vector.
 *
 * This function returns the capacity of the given Vector, indicating the maximum number of
 * elements it can hold without resizing.
 *
 * @param vector A pointer to the Vector for which the capacity is to be retrieved.
 * @return The capacity of the Vector.
 *         - Return 0, if vector = NULL.
 */
	u16 (*capacity)(Vector *vector);	

	/**
 * @brief Retrieves the current length of the Vector.
 *
 * This function returns the number of elements in the given Vector, which is calculated as
 * the difference between the tail and head indices.
 *
 * @param vector A pointer to the Vector for which the length is to be retrieved.
 * @return The current length of the Vector.
 *         - Return 0, if vector = NULL.
 */
	u16 (*length)(Vector *vector);

	/**
 * @brief Checks if the given Vector is empty.
 *
 * This function determines whether the provided Vector is empty by comparing its head and tail indices.
 *
 * @param vector A pointer to the Vector to be checked for emptiness.
 * @return True if the Vector is empty, False otherwise.
 *         - False if the input Vector pointer is NULL.
 */
	boolean (*isEmpty)(Vector *vector);

	/**
 * @brief Checks if the given Vector is full.
 *
 * This function determines whether the provided Vector is full by comparing its tail index with its capacity.
 *
 * @param vector A pointer to the Vector to be checked for fullness.
 * @return True if the Vector is full, False otherwise.
 *         - False if the input Vector pointer is NULL.
 */
	boolean (*isFull)(Vector *vector);

	// Data queries
	/**
 * @brief Retrieves a pointer to the first element in the Vector.
 *
 * This function returns a pointer to the data of the first element in the given Vector.
 *
 * @param vector A pointer to the Vector for which the first element is to be retrieved.
 * @return A pointer to the data of the first element.
 *         - NULL if the input Vector pointer is NULL or if the internal storage is NULL.
 */
	void* (*first)(Vector *vector); 

	/**
 * @brief Retrieves a pointer to the last element in the Vector.
 *
 * This function returns a pointer to the data of the last element in the given Vector.
 *
 * @param vector A pointer to the Vector for which the last element is to be retrieved.
 * @return A pointer to the data of the last element.
 *         - NULL if the input Vector pointer is NULL or if the internal storage is NULL.
 */
	void* (*last)(Vector *vector); 

	/**
 * @brief Retrieves a pointer to the element at the specified position in the Vector.
 *
 * This function returns a pointer to the data of the element at the specified position in the given Vector.
 *
 * @param vector A pointer to the Vector for which the element is to be retrieved.
 * @param position The position of the element to be retrieved.
 * @return A pointer to the data of the element at the specified position.
 *         - NULL if the input Vector pointer is NULL or if the internal storage is NULL.
 */
	void* (*at)(Vector *vector, u16 position);

	// Insertion
	/**
 * @brief Inserts an element with the specified data and size at the beginning of the Vector.
 *
 * This function inserts an element with the provided data and size at the beginning of the given Vector.
 * Existing elements are shifted to make space for the new element.
 *
 * @param vector A pointer to the Vector in which the element is to be inserted.
 * @param data A pointer to the data of the element to be inserted.
 * @param bytes The size of the data to be inserted.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_DataNull if the input data pointer is NULL.
 *         - kErrorCode_BytesZero if the specified size is less than or equal to 0.
 *         - kErrorCode_VectorFull if the Vector is already at full capacity.
 *         - kErrorCode_Ok if the insertion operation is successful.
 */
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes); 

	/**
 * @brief Inserts an element with the specified data and size at the end of the Vector.
 *
 * This function inserts an element with the provided data and size at the end of the given Vector.
 *
 * @param vector A pointer to the Vector in which the element is to be inserted.
 * @param data A pointer to the data of the element to be inserted.
 * @param bytes The size of the data to be inserted.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_DataNull if the input data pointer is NULL.
 *         - kErrorCode_BytesZero if the specified size is less than or equal to 0.
 *         - kErrorCode_VectorFull if the Vector is already at full capacity.
 *         - kErrorCode_Ok if the insertion operation is successful.
 */
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes); 

	/**
 * @brief Inserts an element with the specified data and size at the specified position in the Vector.
 *
 * This function inserts an element with the provided data and size at the specified position in the given Vector.
 * Existing elements are shifted to make space for the new element.
 *
 * @param vector A pointer to the Vector in which the element is to be inserted.
 * @param data A pointer to the data of the element to be inserted.
 * @param bytes The size of the data to be inserted.
 * @param position The position at which the element is to be inserted.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_DataNull if the input data pointer is NULL.
 *         - kErrorCode_BytesZero if the specified size is less than or equal to 0.
 *         - kErrorCode_VectorFull if the Vector is already at full capacity.
 *         - kErrorCode_Ok if the insertion operation is successful.
 */
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position); 

	// Extraction
	/**
 * @brief Extracts and returns the data of the first element from the Vector.
 *
 * This function extracts and returns the data of the first element in the given Vector.
 * The remaining elements are shifted to fill the gap left by the extracted element.
 *
 * @param vector A pointer to the Vector from which the first element is to be extracted.
 * @return A pointer to the data of the extracted first element.
 *         - NULL if the input Vector pointer is NULL or if the internal storage is NULL.
 *         - NULL if the Vector is empty.
 */
	void* (*extractFirst)(Vector *vector);

  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(Vector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);
  */

 /**
 * @brief Extracts and returns the data of the last element from the Vector.
 *
 * This function extracts and returns the data of the last element in the given Vector.
 * The tail index is decremented to exclude the extracted element.
 *
 * @param vector A pointer to the Vector from which the last element is to be extracted.
 * @return A pointer to the data of the extracted last element.
 *         - NULL if the input Vector pointer is NULL.
 *         - NULL if the internal storage pointer within the Vector is NULL.
 *         - NULL if the data pointer of the last element is NULL.
 *         - NULL if the Vector is empty.
 *         - NULL if the tail index is less than or equal to 0.
 */
	void* (*extractLast)(Vector *vector);

	/**
 * @brief Extracts and returns the data of the element at the specified position from the Vector.
 *
 * This function extracts and returns the data of the element at the specified position in the given Vector.
 * The remaining elements are shifted to fill the gap left by the extracted element.
 *
 * @param vector A pointer to the Vector from which the element is to be extracted.
 * @param position The position of the element to be extracted.
 * @return A pointer to the data of the extracted element.
 *         - NULL if the input Vector pointer is NULL.
 *         - NULL if the internal storage pointer within the Vector is NULL.
 *         - NULL if the data pointer of the element at the specified position is NULL.
 *         - NULL if the Vector is empty.
 *         - NULL if the specified position exceeds the current tail index.
 */ 
	void* (*extractAt)(Vector *vector, u16 position);

	// Miscellaneous
	/**
 * @brief Concatenates the elements of two Vectors.
 *
 * This function concatenates the elements of the source Vector (`vector_src`) onto the end of the destination Vector (`vector`).
 * The destination Vector is resized if needed to accommodate the additional elements.
 *
 * @param vector A pointer to the destination Vector.
 * @param vector_src A pointer to the source Vector whose elements will be concatenated onto the destination Vector.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if either the destination Vector or the source Vector pointer is NULL.
 *         - kErrorCode_NodeNull if either the destination Vector's internal storage or the source Vector's internal storage pointer is NULL.
 *         - kErrorCode_Ok if the concatenation is successful and the destination Vector is updated accordingly.
 */
	s16 (*concat)(Vector *vector, Vector *vector_src); 

	/**
 * @brief Traverses the elements in the Vector and applies a callback function to each element.
 *
 * This function traverses the elements in the given Vector within the range [head, tail) and applies
 * a callback function to each element. The callback function is expected to take a MemoryNode pointer as its argument.
 *
 * @param vector A pointer to the Vector to be traversed.
 * @param callback A function pointer to the callback function to be applied to each element.
 *                 The callback function should take a MemoryNode pointer as its argument.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_VectorNull if the input Vector pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_Ok if the traversal and callback application are successful.
 */
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *)); 

	/**
 * @brief Prints information about the Vector and its elements to the standard output.
 *
 * This function prints detailed information about the given Vector, including its address, head, tail, capacity, and
 * information about each element in its internal storage (if not NULL).
 *
 * @param vector A pointer to the Vector whose information is to be printed.
 */
	void (*print)(Vector *vector);
};

/**
 * @brief Creates a new Vector instance with the specified capacity.
 *
 * This function allocates memory for a Vector structure and its internal storage.
 * The internal storage is initialized with MemoryNode instances using MEMNODE_createLite.
 *
 * @param capacity The desired capacity of the Vector.
 * @return A pointer to the newly created Vector, or NULL if memory allocation fails
 *         or if the specified capacity is less than or equal to 0.
 */
Vector* VECTOR_create(u16 capacity); // Creates a new vector

#endif //__ADT_VECTOR_H__
