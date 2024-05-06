// adt_queue.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//logger_ops_s

#ifndef __ADT_LOGGER_H__
#define __ADT_LOGGER_H__

#include "adt_memory_node.h"
#include "adt_queue.h"


typedef struct adt_logger_s {
    adt_queue_s* storage_;
	struct logger_ops_s* ops_;
} Logger;

struct logger_ops_s {

    /**
* @brief Inserts an element with specified data and size at the end of a Queue.
*
* This function inserts an element with specified data and size at the end of a Queue.
* If the provided pointer to the Queue is NULL, it returns kErrorCode_QueueNull.
* If the capacity of the Queue is equal to its length, it returns kErrorCode_EqualCapacity.
* If the data pointer is NULL, it returns kErrorCode_DataNull.
* If the size of the data is less than or equal to 0, it returns kErrorCode_BytesZero.
* If the list is empty, it creates a new node and sets it as both the head and tail of the list.
* If the list is not empty, it creates a new node and sets it as the tail of the Queue.
*
* @param queue A pointer to the Queue to which the element will be inserted.
* @param data A pointer to the data of the element to be inserted.
* @param bytes The size of the data.
* @return An error code indicating the status of the operation.
*         - kErrorCode_QueueNull: If the provided pointer to the Queue is NULL.
*         - kErrorCode_EqualCapacity: If the capacity of the List is equal to its length.
*         - kErrorCode_DataNull: If the provided data pointer is NULL.
*         - kErrorCode_BytesZero: If the size of the data is less than or equal to 0.
*         - kErrorCode_Ok: If the element is successfully inserted.
*/

    s16(*write)(Logger* queue, char* text);

    /**
* @brief Extracts and returns the data of the first element in a Queue.
*
* This function extracts and returns the data of the first element in a Queue.
* If the provided pointer to the Queue is NULL, it returns NULL.
* If the Queue is empty, it returns NULL.
* If the head pointer of the Queue is NULL, it returns NULL.
* It frees the memory of the first element and updates the head pointer of the Queue.
*
* @param Queue A pointer to the Queue from which the first element's data will be extracted.
* @return A pointer to the data of the first element if extraction is successful, otherwise NULL.
*/

    void* (*flush)(Logger* queue);

    /**
* @brief Retrieves the data of the last element in a Queue.
*
* This function retrieves the data of the last element in a Queue. If the provided pointer to the Queue is NULL,
* it returns NULL indicating an invalid Queue. If the head pointer of the Queue is NULL, it returns NULL indicating
* an empty Queue. If the length of the Queue is 0, it returns NULL indicating that the Queue has no elements.
* Otherwise, it returns the data of the last element in the Queue.
*
* @param queue A pointer to the Queue to retrieve the last element's data from.
* @return A pointer to the data of the last element in the Queue.
*         - If the provided pointer to the Queue is NULL, returns NULL.
*         - If the Queue is empty, returns NULL.
*         - If the Queue has no elements, returns NULL.
*         - Otherwise, returns a pointer to the data of the last element in the Queue.
*/

   

    s16(*destroy)(Logger* queue);

    /**
* @brief Resets a Queue by removing all elements and freeing associated memory.
*
* This function resets a Queue by removing all elements and freeing memory associated with each element.
* If the provided pointer to the Queue is NULL, it returns an error code indicating that the Queue pointer
* is NULL. Otherwise, it iterates over the elements of the Queue, frees memory associated with each element,
* including the data stored in each element, and updates the length, head, and tail pointers of the Queue.
* After resetting the Queue, it sets the length to 0 and updates the head and tail pointers to NULL, indicating
* an empty Queue. Finally, it returns an error code indicating success.
*
* @param Queue A pointer to the Queue to reset.
* @return An error code indicating the result of the operation.
*         - kErrorCode_Ok: The reset operation was successful.
*         - kErrorCode_ListNull: The provided pointer to the Queue is NULL.
*/

    s16(*reset)(Logger* queue);

    /**
* @brief Resizes a Queue to the specified new size.
*
* This function resizes a Queue to the specified new size. If the provided pointer to the Queue is NULL,
* it returns an error code indicating that the list pointer is NULL. If the head pointer of the Queue is NULL,
* it returns an error code indicating that the storage pointer of the Queue is NULL. If the new size is 0,
* it returns an error code indicating a null size. If the current capacity of the Queue is equal to the new size,
* it returns an error code indicating equal capacity. If the new size is smaller than the current length of the Queue,
* it trims the list to the new size by removing elements starting from the end of the Queue. If the new size is
* greater than the current length of the Queue, it extends the Queue to the new size by appending NULL nodes.
* Finally, it returns an error code indicating success.
*
* @param queue A pointer to the Queue to resize.
* @param new_size The new size to resize the Queue to.
* @return An error code indicating the result of the operation.
*         - kErrorCode_Ok: The resize operation was successful.
*         - kErrorCode_QueueNull: The provided pointer to the Queue is NULL.
*         - kErrorCode_StorageNull: The storage pointer of the Queue is NULL.
*         - kErrorCode_SizeNull: The new size is 0.
*         - kErrorCode_EqualCapacity: The new size is equal to the current capacity of the Queue.
*         - kErrorCode_MallocNull: Memory allocation failed while resizing the Queue.
*/

    s16(*resize)(Logger* queue, u16 new_size);

    /**
* @brief Retrieves the capacity of a Queue.
*
* This function retrieves the capacity of a Queue, which represents the maximum number of elements
* the list can hold without resizing its internal storage. If the provided pointer to the queue is NULL,
* it returns 0 indicating an invalid capacity. Otherwise, it returns the capacity of the queue.
*
* @param queue A pointer to the Queue to retrieve the capacity from.
* @return The capacity of the Queue.
*         - If the provided pointer to the Queue is NULL, returns 0.
*         - Otherwise, returns the capacity of the Queue.
*/

    u16(*capacity)(const Logger* queue);

    /**
* @brief Retrieves the length of a Queue.
*
* This function retrieves the length of a Queue, which represents the number of elements
* currently stored in the queue. If the provided pointer to the queue is NULL,
* it returns 0 indicating an empty queue. Otherwise, it returns the length of the queue.
*
* @param queue A pointer to the Queue to retrieve the length from.
* @return The length of the Queue.
*         - If the provided pointer to the Queue is NULL, returns 0.
*         - Otherwise, returns the length of the Queue.
*/

    u16(*length)(const Logger* queue);

    /**
 * @brief Checks if a Queue is empty.
 *
 * This function checks if a Queue is empty by examining its length. If the provided pointer to the Queue is NULL,
 * it returns 0 indicating that the list is not empty. Otherwise, it returns 1 if the Queue is empty,
 * and 0 otherwise.
 *
 * @param queue A pointer to the Queue to check for emptiness.
 * @return A boolean value indicating whether the Queue is empty or not.
 *         - If the provided pointer to the Queue is NULL, returns 0 (false).
 *         - If the Queue is empty, returns 1 (true).
 *         - Otherwise, returns 0 (false).
 */

    s16(*isEmpty)(const Logger* queue);

    /**
* @brief Checks if a Queue is full.
*
* This function checks if a Queue is full by comparing its current length with its capacity.
* If the provided pointer to the queue is NULL, it returns 0 indicating that the list is not full.
* Otherwise, it returns 1 if the queue is full (i.e., its length is equal to its capacity), and 0 otherwise.
*
* @param queue A pointer to the Queue to check for fullness.
* @return A boolean value indicating whether the Queue is full or not.
*         - If the provided pointer to the Queue is NULL, returns 0 (false).
*         - If the Queue is full, returns 1 (true).
*         - Otherwise, returns 0 (false).
*/

    s16(*isFull)(const Logger* queue);
   
    /**
 * @brief Concatenates the elements of two Queues.
 *
 * This function concatenates the elements of the source Queue (`queue_src`) onto the end of the destination Vector (`Queue`).
 * The destination Queue is resized if needed to accommodate the additional elements.
 *
 * @param queue A pointer to the destination Queue.
 * @param queue_src A pointer to the source Vector whose elements will be concatenated onto the destination Queue.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_QueueNull if either the destination queue or the source Queue pointer is NULL.
 *         - kErrorCode_NodeNull if either the destination queue's internal storage or the source Vector's internal storage pointer is NULL.
 *         - kErrorCode_Ok if the concatenation is successful and the destination Vector is updated accordingly.
 */
    s16(*concat)(Logger* queue, const Logger* queue_src);
   
    /**
* @brief Prints information about a Queue and its elements.
*
* This function prints information about a Queue and its elements.
* It checks if the Queue is NULL. If the Queue is NULL, it prints a message indicating a NULL Queue and returns.
* Otherwise, it prints information about the Queue, including its address, length, capacity, first and last addresses, and whether it is empty.
* If the Queue is not empty, it iterates through the Queue and prints information about each element, including its address, size, data address, data content, and next address.
*
* @param queue A pointer to the Queue to be printed.
*/

    void (*print)(Logger* queue);
};

/**
 * @brief Creates a new Queue with the specified capacity.
 *
 * This function creates a new Queue with the specified capacity.
 * It allocates memory for the Queue structure and initializes its fields, including length, capacity, head, tail, and operations.
 * If the specified capacity is less than or equal to 0, it returns NULL.
 * If memory allocation for the Queue structure fails, it returns NULL.
 *
 * @param capacity The capacity of the Queue to be created.
 * @return A pointer to the newly created Queue, or NULL if the capacity is invalid or memory allocation fails.
 */

Logger* Logger_create(u16 capacity);

#endif //__ADT_LOGGER_H__
