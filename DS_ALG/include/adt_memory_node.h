// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "EDK_MemoryManager/edk_platform_types.h"

// Memory Node type
typedef struct memory_node_s {
  void *data_;
  u16 size_;
  //MemoryNode* next_;
  struct memory_node_ops_s *ops_;
} MemoryNode;

// Memory Node's API Declarations
struct memory_node_ops_s {

  /**
 * @brief Returns a reference to the data stored in the MemoryNode.
 *
 * This function returns a reference to the data pointer (`data_`) stored in the provided MemoryNode.
 *
 * @param node A pointer to the MemoryNode from which the data reference is requested.
 * @return A pointer to the data stored in the MemoryNode.
 *         - NULL if the input MemoryNode pointer is NULL.
 */
  void*(*data) (MemoryNode *node);

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
  s16(*setData) (MemoryNode *node, void *src, u16 bytes);

  /**
 * @brief Returns the size of the data stored in the MemoryNode.
 *
 * This function returns the size of the data stored in the provided MemoryNode.
 *
 * @param node A pointer to the MemoryNode from which the data size is requested.
 * @return The size of the data stored in the MemoryNode.
 *         - 0 if the input MemoryNode pointer is NULL.
 */
  u16(*size) (MemoryNode *node);

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
  s16(*reset) (MemoryNode *node);		

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
  s16(*softReset) (MemoryNode *node);	

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
  s16(*free) (MemoryNode *node);	

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
  s16(*softFree) (MemoryNode *node);

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
  s16(*memSet) (MemoryNode *node, u8 value);

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
  s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);

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
  s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);

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
  s16(*memMask) (MemoryNode *node, u8 mask);

  /**
 * @brief Prints information about the MemoryNode.
 *
 * This function prints information about the provided MemoryNode, including its address, size, data address, and data content.
 * If the MemoryNode or its data pointer is NULL, corresponding messages are printed.
 *
 * @param node A pointer to the MemoryNode to be printed.
 */
  void(*print) (MemoryNode *node);
};

/**
 * @brief Creates a new MemoryNode and initializes it.
 *
 * This function allocates memory for a new MemoryNode using the memory manager (MM),
 * and initializes the MemoryNode using MEMNODE_initWithoutCheck.
 *
 * @return A pointer to the newly created MemoryNode.
 *         - NULL if there is not enough memory available.
 */
MemoryNode* MEMNODE_create();

/**
 * @brief Creates a new MemoryNode and assigns its pointer to the provided reference.
 *
 * This function creates a new MemoryNode using MEMNODE_create and assigns its pointer to the
 * MemoryNode pointer referenced by the input parameter 'node'.
 *
 * @param node A pointer to a MemoryNode pointer where the created MemoryNode's pointer will be assigned.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_NodeNull if the input node pointer is NULL.
 *         - kErrorCode_Memory if there is not enough memory available.
 *         - kErrorCode_Ok if the MemoryNode is successfully created and its pointer is assigned to the reference.
 */
s16 MEMNODE_createFromRef(MemoryNode **node);

/**
 * @brief Initializes a MemoryNode with default values.
 *
 * This function initializes the provided MemoryNode by setting its data pointer to NULL,
 * its size to 0, and assigning the default MemoryNode operations.
 *
 * @param node A pointer to the MemoryNode to be initialized.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_NodeNull if the input node pointer is NULL.
 *         - kErrorCode_Ok if the MemoryNode is successfully initialized.
 */
s16 MEMNODE_createLite(MemoryNode *node); // Creates a memory node without memory allocation

#endif // __ADT_MEMORY_NODE_H__
