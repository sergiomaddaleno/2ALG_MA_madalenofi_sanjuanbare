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

	/**
	* @brief Returns a reference to the data stored in the MemoryNode.
	*
	* This function returns a reference to the data pointer (`data_`) stored in the provided MemoryNode.
	*
	* @param node A pointer to the MemoryNode from which the data reference is requested.
	* @return A pointer to the data stored in the MemoryNode.
	*         - NULL if the input MemoryNode pointer is NULL.
	*/
	void* data(memory_node_s* node);

	/**
* @brief Sets the data and size of the MemoryNode.
*
* This function sets the data pointer (`data_`) and size of the provided MemoryNode.
*
* @param node A pointer to the MemoryNode whose data and size are to be set.
* @param src A pointer to the source data to be assigned to the MemoryNode.
* @param bytes The size of the data to be assigned to the MemoryNode.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_SrcNull if the source data pointer is NULL.
*         - kErrorCode_BytesZero if the specified size is 0.
*         - kErrorCode_Ok if the MemoryNode is successfully updated with the provided data and size.
*/
	s16 setData(memory_node_s* node, void* src, u16 bytes);

	/**
* @brief Returns the size of the data stored in the MemoryNode.
*
* This function returns the size of the data stored in the provided MemoryNode.
*
* @param node A pointer to the MemoryNode from which the data size is requested.
* @return The size of the data stored in the MemoryNode.
*         - 0 if the input MemoryNode pointer is NULL.
*/
	u16 size(memory_node_s* node);

	/**
* @brief Resets the data and size of the MemoryNode, freeing the allocated memory.
*
* This function resets the data pointer (`data_`) and size of the provided MemoryNode,
* freeing the previously allocated memory associated with the data.
*
* @param node A pointer to the MemoryNode to be reset.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_DataNull if the data pointer within the MemoryNode is NULL.
*         - kErrorCode_Ok if the MemoryNode is successfully reset, and memory is freed.
*/
	s16 reset(memory_node_s* node);

	/**
   * @brief Softly resets the data and size of the MemoryNode without freeing memory.
   *
   * This function softly resets the data pointer (`data_`) and size of the provided MemoryNode
   * without freeing the allocated memory. It sets the data pointer to NULL and the size to 0.
   *
   * @param node A pointer to the MemoryNode to be softly reset.
   * @return An error code indicating the result of the operation.
   *         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
   *         - kErrorCode_DataNull if the data pointer within the MemoryNode is NULL.
   *         - kErrorCode_Ok if the MemoryNode is successfully softly reset.
   */
	s16 softReset(memory_node_s* node);

	/**
 * @brief Frees the memory associated with the MemoryNode.
 *
 * This function frees the memory associated with the provided MemoryNode, including
 * the data pointer (`data_`) and the MemoryNode itself.
 *
 * @param node A pointer to the MemoryNode to be freed.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
 *         - kErrorCode_Ok if the MemoryNode and its associated memory are successfully freed.
 */
	s16 free(memory_node_s* node);

	/**
* @brief Softly frees the MemoryNode without freeing memory associated with the data.
*
* This function softly frees the provided MemoryNode without freeing the memory
* associated with the data pointer (`data_`). It only frees the MemoryNode itself.
*
* @param node A pointer to the MemoryNode to be softly freed.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_Ok if the MemoryNode is successfully softly freed.
*/
	s16 softFree(memory_node_s* node);

	/**
* @brief Sets all bytes of the data in the MemoryNode to the specified value.
*
* This function sets all bytes of the data stored in the provided MemoryNode to the specified value.
*
* @param node A pointer to the MemoryNode whose data is to be set.
* @param value The value to set all bytes of the data.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_DataNull if the data pointer within the MemoryNode is NULL.
*         - kErrorCode_Ok if the MemoryNode data is successfully set to the specified value.
*/
	s16 memSet(memory_node_s* node, u8 value);

	/**
   * @brief Copies data from the source to the MemoryNode and updates its size.
   *
   * This function copies data from the source to the provided MemoryNode and updates its size accordingly.
   *
   * @param node A pointer to the MemoryNode to which data is to be copied.
   * @param src A pointer to the source data to be copied to the MemoryNode.
   * @param bytes The size of the data to be copied.
   * @return An error code indicating the result of the operation.
   *         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
   *         - kErrorCode_SrcNull if the source data pointer is NULL.
   *         - kErrorCode_BytesZero if the specified size is 0.
   *         - kErrorCode_MallocNull if memory allocation for the copied data fails.
   *         - kErrorCode_Ok if the data is successfully copied to the MemoryNode.
   */
	s16 memCopy(memory_node_s* node, void* src, u16 bytes);

	/**
* @brief Concatenates data from the source to the MemoryNode and updates its size.
*
* This function concatenates data from the source to the provided MemoryNode and updates its size accordingly.
*
* @param node A pointer to the MemoryNode to which data is to be concatenated.
* @param src A pointer to the source data to be concatenated to the MemoryNode.
* @param bytes The size of the data to be concatenated.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_DataNull if the data pointer within the MemoryNode is NULL.
*         - kErrorCode_SizeNull if the size of the MemoryNode is 0.
*         - kErrorCode_MallocNull if memory allocation for the concatenated data fails.
*         - kErrorCode_Ok if the data is successfully concatenated to the MemoryNode.
*/
	s16 memConcat(memory_node_s* node, void* src, u16 bytes);

	/**
* @brief Applies a bitwise mask to all bytes of the data in the MemoryNode.
*
* This function applies a bitwise mask to all bytes of the data stored in the provided MemoryNode.
*
* @param node A pointer to the MemoryNode whose data is to be masked.
* @param mask The bitwise mask to be applied to each byte of the data.
* @return An error code indicating the result of the operation.
*         - kErrorCode_NodeNull if the input MemoryNode pointer is NULL.
*         - kErrorCode_DataNull if the data pointer within the MemoryNode is NULL.
*         - kErrorCode_SizeNull if the size of the MemoryNode is 0.
*         - kErrorCode_Ok if the bitwise mask is successfully applied to the MemoryNode data.
*/
	s16 memMask(memory_node_s* node, u8 mask);

	/**
* @brief Prints information about the MemoryNode.
*
* This function prints information about the provided MemoryNode, including its address, size, data address, and data content.
* If the MemoryNode or its data pointer is NULL, corresponding messages are printed.
*
* @param node A pointer to the MemoryNode to be printed.
*/
	void print(memory_node_s* node);

	/**
 * @brief Retrieves the next memory node in the list.
 *
 * This function returns the next node in the memory node list. If the provided node
 * is `NULL`, it returns `NULL`.
 *
 * @param node A pointer to the current MemoryNode structure.
 * @return A pointer to the next MemoryNode structure, or `NULL` if the current node is `NULL`.
 */
	memory_node_s* next(memory_node_s* node);

	/**
 * @brief Retrieves the previous memory node in the list.
 *
 * This function returns the previous node in the memory node list. If the provided node
 * is `NULL`, it returns `NULL`.
 *
 * @param node A pointer to the current MemoryNode structure.
 * @return A pointer to the previous MemoryNode structure, or `NULL` if the current node is `NULL`.
 */
	memory_node_s* previous(memory_node_s* node);

	/**
 * @brief Sets the next memory node for the given node.
 *
 * This function sets the next node in the memory node list for the provided node.
 * If the provided node or the next node is `NULL`, it does nothing.
 *
 * @param node A pointer to the current MemoryNode structure.
 * @param next_node A pointer to the next MemoryNode structure to be set.
 */
	void setNext(memory_node_s* node, memory_node_s* next_node);

	/**
 * @brief Sets the previous memory node for the given node.
 *
 * This function sets the previous node in the memory node list for the provided node.
 * If the provided node or the previous node is `NULL`, it does nothing.
 *
 * @param node A pointer to the current MemoryNode structure.
 * @param previous_node A pointer to the previous MemoryNode structure to be set.
 */
	void setPrevious(memory_node_s* node, memory_node_s* previous_node);

	//static memory_node_s* MEMNODE_create();
};

/**
 * @brief Creates a memory node from a reference pointer.
 *
 * This function creates a new memory node and assigns it to the pointer passed by reference.
 * If the provided reference pointer is `NULL`, it returns an error code indicating a null node.
 * If memory allocation fails, it returns an error code indicating insufficient memory.
 *
 * @param node A pointer to a pointer to a MemoryNode structure.
 * @return An error code indicating the status of the operation. Possible values are:
 *         - kErrorCode_Ok: Operation successful.
 *         - kErrorCode_NodeNull: The provided reference pointer is NULL.
 *         - kErrorCode_Memory: Memory allocation failed.
 */
s16 MEMNODE_createFromRef(memory_node_s** node);


/**
 * @brief Initializes a memory node with default values.
 *
 * This function initializes the given memory node with default values:
 * - Sets the data pointer to NULL.
 * - Sets the size to 0.
 * - Sets the operations pointer to point to the default memory node operations.
 * - Sets the next and previous pointers to NULL.
 *
 * @param node A pointer to the MemoryNode structure to be initialized.
 * @return An error code indicating the status of the operation. Possible values are:
 *         - kErrorCode_Ok: Operation successful.
 *         - kErrorCode_NodeNull: The provided node pointer is NULL.
 */
s16 MEMNODE_createLite(memory_node_s* node);

#endif // __ADT_MEMORY_NODE_H__
