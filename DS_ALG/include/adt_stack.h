// adt_stack.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__

#include "adt_memory_node.h"
#include "adt_vector.h"

typedef struct adt_stack_s {
	Vector* storage_;
	struct stack_ops_s* ops_;
} Stack;

struct stack_ops_s {

	/**
* @brief Inserts an element with the specified data and size at the end of the Stack.
*
* This function inserts an element with the provided data and size at the end of the given Stack.
*
* @param stack A pointer to the Stack in which the element is to be inserted.
* @param data A pointer to the data of the element to be inserted.
* @param bytes The size of the data to be inserted.
* @return An error code indicating the result of the operation.
*         - kErrorCode_StackNull if the input Stack pointer is NULL.
*         - kErrorCode_StorageNull if the internal storage pointer within the Stack is NULL.
*         - kErrorCode_DataNull if the input data pointer is NULL.
*         - kErrorCode_BytesZero if the specified size is less than or equal to 0.
*         - kErrorCode_StackFull if the Stack is already at full capacity.
*         - kErrorCode_Ok if the insertion operation is successful.
*/

	s16(*push)(Stack* stack, void* data, u16 size);

	/**
* @brief Extracts and returns the data of the last element from the Stack.
*
* This function extracts and returns the data of the last element in the given Stack.
* The tail index is decremented to exclude the extracted element.
*
* @param stack A pointer to the Stack from which the last element is to be extracted.
* @return A pointer to the data of the extracted last element.
*         - NULL if the input Stack pointer is NULL.
*         - NULL if the internal storage pointer within the Stack is NULL.
*         - NULL if the data pointer of the last element is NULL.
*         - NULL if the Stack is empty.
*         - NULL if the tail index is less than or equal to 0.
*/

	void* (*pop)(Stack* stack);

	/**
 * @brief Retrieves a pointer to the last element in the Stack.
 *
 * This function returns a pointer to the data of the last element in the given Stack.
 *
 * @param stack A pointer to the Stack for which the last element is to be retrieved.
 * @return A pointer to the data of the last element.
 *         - NULL if the input Vector pointer is NULL or if the internal storage is NULL.
 */

	void* (*top)(Stack* stack);

	/**
 * @brief Resets a Stack by invoking the reset operation on each element in its internal storage.
 *
 * This function resets each element in the Stack's internal storage using the reset operation
 * provided by the corresponding MemoryNode. The Stack's tail position is then set to 0,
 * indicating an empty state.
 *
 * @param vector A pointer to the Stack to be reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_StackNull if the input Stack pointer is NULL.
 *         - kErrorCode_StorageNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_Ok if the reset operation is successful.
 */

	s16(*reset)(Stack* stack);

	// State queries
	/**
 * @brief Retrieves the capacity of the stack.
 *
 * This function returns the capacity of the given stack, indicating the maximum number of
 * elements it can hold without resizing.
 *
 * @param stack A pointer to the Vector for which the capacity is to be retrieved.
 * @return The capacity of the Stack.
 *         - Return 0, if stack = NULL.
 */

	u16 (*capacity)(Stack* stack);

	/**
 * @brief Resizes the stack to the specified new size.
 *
 * This function resizes the stack's internal storage to the new size.
 * If the new size is smaller than the current size, it truncates the stack.
 * If the new size is larger, it allocates new memory and copies existing elements.
 *
 * @param stack A pointer to the stack to be resized.
 * @param new_size The new size to which the stack should be resized.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_StackNull if the input Vector pointer is NULL.
 *         - kErrorCode_NodeNull if the internal storage pointer within the Vector is NULL.
 *         - kErrorCode_SizeNull if the new size is 0.
 *         - kErrorCode_Ok if the resizing operation is successful.
 */

	s16 (*resize)(Stack* stack, u16 new_size);

	/**
* @brief Retrieves the current length of the stack.
*
* This function returns the number of elements in the given stack, which is calculated as
* the difference between the tail and head indices.
*
* @param stack A pointer to the stack for which the length is to be retrieved.
* @return The current length of the stack.
*         - Return 0, if vector = NULL.
*/

	s16 (*length)(Stack* stack);

	/**
 * @brief Checks if the given stack is empty.
 *
 * This function determines whether the provided stack is empty by comparing its head and tail indices.
 *
 * @param stack A pointer to the stack to be checked for emptiness.
 * @return True if the stack is empty, False otherwise.
 *         - False if the input stack pointer is NULL.
 */

	boolean (*isEmpty)(Stack* stack);

	/**
 * @brief Checks if the given stack is full.
 *
 * This function determines whether the provided stack is full by comparing its tail index with its capacity.
 *
 * @param stack A pointer to the stack to be checked for fullness.
 * @return True if the stack is full, False otherwise.
 *         - False if the input stack pointer is NULL.
 */

	boolean (*isFull)(Stack* stack);

	/**
* @brief Concatenates the elements of two Stack.
*
* This function concatenates the elements of the source Stack (`Stack_Src`) onto the end of the destination Vector (`Queue`).
* The destination Queue is resized if needed to accommodate the additional elements.
*
* @param Stack A pointer to the destination Stack.
* @param stack_src A pointer to the source Stack whose elements will be concatenated onto the destination Stack.
* @return An error code indicating the result of the operation.
*         - kErrorCode_StackNull if either the destination stack or the source stack pointer is NULL.
*         - kErrorCode_NodeNull if either the destination stack's internal storage or the source stack's internal storage pointer is NULL.
*         - kErrorCode_Ok if the concatenation is successful and the destination stack is updated accordingly.
*/
	s16 (*concat)(Stack* stack, Stack* stack_src);
	
	/**
* @brief Destroys a stack and frees its allocated memory, including internal storage and elements.
*
* This function deallocates memory associated with the stack structure, its internal storage,
* and any allocated memory for individual elements within the storage.
*
* @param stack A pointer to the stack to be destroyed.
* @return An error code indicating the result of the operation.
*         - kErrorCode_stackNull if the input stack pointer is NULL.
*         - kErrorCode_NodeNull if the internal storage pointer within the stack is NULL.
*         - kErrorCode_Ok if the destruction operation is successful.
*/

	s16 (*destroy)(Stack* stack);

	/**
* @brief stacks information about the stack and its elements to the standard output.
*
* This function prints detailed information about the given stack, including its address, head, tail, capacity, and
* information about each element in its internal storage (if not NULL).
*
* @param stack A pointer to the stack whose information is to be printed.
*/

	void (*print)(Stack* stack);
};

/**
 * @brief Creates a new Stack instance with the specified capacity.
 *
 * This function allocates memory for a Stack structure and its internal storage.
 * The internal storage is initialized with MemoryNode instances using MEMNODE_createLite.
 *
 * @param capacity The desired capacity of the Stack.
 * @return A pointer to the newly created Stack, or NULL if memory allocation fails
 *         or if the specified capacity is less than or equal to 0.
 */

Stack* STACK_create(u16 capacity);

#endif //__ADT_STACK_H__
