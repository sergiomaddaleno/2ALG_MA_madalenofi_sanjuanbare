// adt_list.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

class adt_list_s {

public:

    memory_node_s* head_;
    memory_node_s* tail_;
	u16 length_;
	u16 capacity_;


    adt_list_s(u16 capacity);
    ~adt_list_s();
    /**
 * @brief Destroys a List and frees memory associated with its elements.
 *
 * This function destroys a List and frees memory associated with its elements.
 * If the provided pointer to the list is NULL, it returns an error code indicating
 * that the list pointer is NULL. Otherwise, it iterates over the elements of the list
 * and frees memory associated with each element, including the data stored in each element.
 * After freeing memory for all elements, it frees memory for the list itself and returns
 * an error code indicating success.
 *
 * @param list A pointer to the List to destroy.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The destruction operation was successful.
 *         - kErrorCode_ListNull: The provided pointer to the List is NULL.
 */
    s16 destroy (adt_list_s* list);

    /**
 * @brief Resets a List by removing all elements and freeing associated memory.
 *
 * This function resets a List by removing all elements and freeing memory associated with each element.
 * If the provided pointer to the list is NULL, it returns an error code indicating that the list pointer
 * is NULL. Otherwise, it iterates over the elements of the list, frees memory associated with each element,
 * including the data stored in each element, and updates the length, head, and tail pointers of the list.
 * After resetting the list, it sets the length to 0 and updates the head and tail pointers to NULL, indicating
 * an empty list. Finally, it returns an error code indicating success.
 *
 * @param list A pointer to the List to reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The reset operation was successful.
 *         - kErrorCode_ListNull: The provided pointer to the List is NULL.
 */
    s16 reset (adt_list_s* list);

    /**
 * @brief Soft resets a List by removing all elements without freeing associated memory.
 *
 * This function soft resets a List by removing all elements without freeing memory associated with each element.
 * If the provided pointer to the list is NULL, it returns an error code indicating that the list pointer
 * is NULL. If the head pointer of the list is NULL, it returns an error code indicating that the storage
 * pointer of the list is NULL. Otherwise, it iterates over the elements of the list and updates the head pointer
 * to remove each element, effectively clearing the list. After soft resetting the list, it sets the length to 0
 * and updates the head and tail pointers to NULL, indicating an empty list. Finally, it returns an error code
 * indicating success.
 *
 * @param list A pointer to the List to soft reset.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The soft reset operation was successful.
 *         - kErrorCode_ListNull: The provided pointer to the List is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the List is NULL.
 */
    s16 softReset(adt_list_s* list);

    /**
 * @brief Resizes a List to the specified new size.
 *
 * This function resizes a List to the specified new size. If the provided pointer to the list is NULL,
 * it returns an error code indicating that the list pointer is NULL. If the head pointer of the list is NULL,
 * it returns an error code indicating that the storage pointer of the list is NULL. If the new size is 0,
 * it returns an error code indicating a null size. If the current capacity of the list is equal to the new size,
 * it returns an error code indicating equal capacity. If the new size is smaller than the current length of the list,
 * it trims the list to the new size by removing elements starting from the end of the list. If the new size is
 * greater than the current length of the list, it extends the list to the new size by appending NULL nodes.
 * Finally, it returns an error code indicating success.
 *
 * @param list A pointer to the List to resize.
 * @param new_size The new size to resize the list to.
 * @return An error code indicating the result of the operation.
 *         - kErrorCode_Ok: The resize operation was successful.
 *         - kErrorCode_ListNull: The provided pointer to the List is NULL.
 *         - kErrorCode_StorageNull: The storage pointer of the List is NULL.
 *         - kErrorCode_SizeNull: The new size is 0.
 *         - kErrorCode_EqualCapacity: The new size is equal to the current capacity of the list.
 *         - kErrorCode_MallocNull: Memory allocation failed while resizing the list.
 */
    s16 resize(adt_list_s* list, u16 new_size);

    /**
 * @brief Retrieves the capacity of a List.
 *
 * This function retrieves the capacity of a List, which represents the maximum number of elements
 * the list can hold without resizing its internal storage. If the provided pointer to the list is NULL,
 * it returns 0 indicating an invalid capacity. Otherwise, it returns the capacity of the list.
 *
 * @param list A pointer to the List to retrieve the capacity from.
 * @return The capacity of the List.
 *         - If the provided pointer to the List is NULL, returns 0.
 *         - Otherwise, returns the capacity of the List.
 */
    u16 capacity (const adt_list_s* list);

    /**
 * @brief Retrieves the length of a List.
 *
 * This function retrieves the length of a List, which represents the number of elements
 * currently stored in the list. If the provided pointer to the list is NULL,
 * it returns 0 indicating an empty list. Otherwise, it returns the length of the list.
 *
 * @param list A pointer to the List to retrieve the length from.
 * @return The length of the List.
 *         - If the provided pointer to the List is NULL, returns 0.
 *         - Otherwise, returns the length of the List.
 */
    u16 length (const adt_list_s* list);

    /**
 * @brief Checks if a List is empty.
 *
 * This function checks if a List is empty by examining its length. If the provided pointer to the list is NULL,
 * it returns 0 indicating that the list is not empty. Otherwise, it returns 1 if the list is empty,
 * and 0 otherwise.
 *
 * @param list A pointer to the List to check for emptiness.
 * @return A boolean value indicating whether the List is empty or not.
 *         - If the provided pointer to the List is NULL, returns 0 (false).
 *         - If the List is empty, returns 1 (true).
 *         - Otherwise, returns 0 (false).
 */
    s16 isEmpty (const adt_list_s* list);

    /**
 * @brief Checks if a List is full.
 *
 * This function checks if a List is full by comparing its current length with its capacity.
 * If the provided pointer to the list is NULL, it returns 0 indicating that the list is not full.
 * Otherwise, it returns 1 if the list is full (i.e., its length is equal to its capacity), and 0 otherwise.
 *
 * @param list A pointer to the List to check for fullness.
 * @return A boolean value indicating whether the List is full or not.
 *         - If the provided pointer to the List is NULL, returns 0 (false).
 *         - If the List is full, returns 1 (true).
 *         - Otherwise, returns 0 (false).
 */
    s16 isFull (const adt_list_s* list);

    /**
 * @brief Retrieves the data of the first element in a List.
 *
 * This function retrieves the data of the first element in a List. If the provided pointer to the list is NULL,
 * it returns NULL indicating an invalid list. If the head pointer of the list is NULL, it returns NULL indicating
 * an empty list. Otherwise, it returns the data of the first element in the list.
 *
 * @param list A pointer to the List to retrieve the first element's data from.
 * @return A pointer to the data of the first element in the List.
 *         - If the provided pointer to the List is NULL, returns NULL.
 *         - If the List is empty, returns NULL.
 *         - Otherwise, returns a pointer to the data of the first element in the List.
 */
    void* first(const adt_list_s* list);

    /**
 * @brief Retrieves the data of the last element in a List.
 *
 * This function retrieves the data of the last element in a List. If the provided pointer to the list is NULL,
 * it returns NULL indicating an invalid list. If the head pointer of the list is NULL, it returns NULL indicating
 * an empty list. If the length of the list is 0, it returns NULL indicating that the list has no elements.
 * Otherwise, it returns the data of the last element in the list.
 *
 * @param list A pointer to the List to retrieve the last element's data from.
 * @return A pointer to the data of the last element in the List.
 *         - If the provided pointer to the List is NULL, returns NULL.
 *         - If the List is empty, returns NULL.
 *         - If the List has no elements, returns NULL.
 *         - Otherwise, returns a pointer to the data of the last element in the List.
 */
    void* last (const adt_list_s* list);

    /**
 * @brief Retrieves the data of the element at a specified position in a List.
 *
 * This function retrieves the data of the element at a specified position in a List.
 * If the provided pointer to the list is NULL, it returns NULL indicating an invalid list.
 * If the head pointer of the list is NULL, it returns NULL indicating an empty list.
 * If the specified position is out of bounds (i.e., greater than or equal to the length of the list),
 * it returns NULL. Otherwise, it returns the data of the element at the specified position in the list.
 *
 * @param list A pointer to the List to retrieve the element's data from.
 * @param position The position of the element in the List.
 * @return A pointer to the data of the element at the specified position in the List.
 *         - If the provided pointer to the List is NULL, returns NULL.
 *         - If the List is empty, returns NULL.
 *         - If the specified position is out of bounds, returns NULL.
 *         - Otherwise, returns a pointer to the data of the element at the specified position in the List.
 */
    void* at (const adt_list_s* list, u16 position);

    /**
 * @brief Inserts a new element at the beginning of a List.
 *
 * This function inserts a new element containing the provided data at the beginning of a List.
 * If the provided pointer to the List is NULL, it returns an error code `kErrorCode_ListNull`.
 * If the List is already full (i.e., its length is equal to its capacity), it returns an error code `kErrorCode_EqualCapacity`.
 * If the provided data pointer is NULL, it returns an error code `kErrorCode_DataNull`.
 * If the size of the data is less than or equal to 0, it returns an error code `kErrorCode_BytesZero`.
 * If memory allocation for the new element fails, it returns an error code `kErrorCode_MallocNull`.
 * Otherwise, it inserts the new element at the beginning of the List and updates the List's metadata accordingly.
 *
 * @param list A pointer to the List to insert the new element into.
 * @param data A pointer to the data to be inserted into the new element.
 * @param bytes The size of the data in bytes.
 * @return An error code indicating the status of the operation.
 *         - Returns `kErrorCode_ListNull` if the provided pointer to the List is NULL.
 *         - Returns `kErrorCode_EqualCapacity` if the List is full.
 *         - Returns `kErrorCode_DataNull` if the provided data pointer is NULL.
 *         - Returns `kErrorCode_BytesZero` if the size of the data is less than or equal to 0.
 *         - Returns `kErrorCode_MallocNull` if memory allocation for the new element fails.
 *         - Returns `kErrorCode_Ok` if the insertion operation is successful.
 */
    s16 insertFirst (adt_list_s* list, void* data, u16 bytes);

    /**
 * @brief Inserts an element with specified data and size at the end of a List.
 *
 * This function inserts an element with specified data and size at the end of a List.
 * If the provided pointer to the list is NULL, it returns kErrorCode_ListNull.
 * If the capacity of the list is equal to its length, it returns kErrorCode_EqualCapacity.
 * If the data pointer is NULL, it returns kErrorCode_DataNull.
 * If the size of the data is less than or equal to 0, it returns kErrorCode_BytesZero.
 * If the list is empty, it creates a new node and sets it as both the head and tail of the list.
 * If the list is not empty, it creates a new node and sets it as the tail of the list.
 *
 * @param list A pointer to the List to which the element will be inserted.
 * @param data A pointer to the data of the element to be inserted.
 * @param bytes The size of the data.
 * @return An error code indicating the status of the operation.
 *         - kErrorCode_ListNull: If the provided pointer to the List is NULL.
 *         - kErrorCode_EqualCapacity: If the capacity of the List is equal to its length.
 *         - kErrorCode_DataNull: If the provided data pointer is NULL.
 *         - kErrorCode_BytesZero: If the size of the data is less than or equal to 0.
 *         - kErrorCode_Ok: If the element is successfully inserted.
 */
    s16 insertLast (adt_list_s* list, void* data, u16 bytes);

    /**
 * @brief Inserts an element with specified data and size at a specified position in a List.
 *
 * This function inserts an element with specified data and size at the specified position in a List.
 * If the provided pointer to the list is NULL, it returns kErrorCode_ListNull.
 * If the capacity of the list is equal to its length, it returns kErrorCode_EqualCapacity.
 * If the data pointer is NULL, it returns kErrorCode_DataNull.
 * If the size of the data is less than or equal to 0, it returns kErrorCode_BytesZero.
 * If the specified position is greater than the length of the list, it inserts the element at the end.
 * If memory allocation fails during node creation, it returns kErrorCode_MallocNull.
 *
 * @param list A pointer to the List to which the element will be inserted.
 * @param data A pointer to the data of the element to be inserted.
 * @param bytes The size of the data.
 * @param position The position at which the element will be inserted.
 * @return An error code indicating the status of the operation.
 *         - kErrorCode_ListNull: If the provided pointer to the List is NULL.
 *         - kErrorCode_EqualCapacity: If the capacity of the List is equal to its length.
 *         - kErrorCode_DataNull: If the provided data pointer is NULL.
 *         - kErrorCode_BytesZero: If the size of the data is less than or equal to 0.
 *         - kErrorCode_MallocNull: If memory allocation fails during node creation.
 *         - kErrorCode_Ok: If the element is successfully inserted.
 */
    s16 insertAt (adt_list_s* list, void* data, u16 bytes, u16 position);

    /**
 * @brief Extracts and returns the data of the first element in a List.
 *
 * This function extracts and returns the data of the first element in a List.
 * If the provided pointer to the List is NULL, it returns NULL.
 * If the List is empty, it returns NULL.
 * If the head pointer of the List is NULL, it returns NULL.
 * It frees the memory of the first element and updates the head pointer of the List.
 *
 * @param list A pointer to the List from which the first element's data will be extracted.
 * @return A pointer to the data of the first element if extraction is successful, otherwise NULL.
 */
    void* extractFirst (adt_list_s* list);

    /**
 * @brief Extracts and returns the data of the last element in a List.
 *
 * This function extracts and returns the data of the last element in a List.
 * If the provided pointer to the List is NULL, it returns NULL.
 * If the List is empty, it returns NULL.
 * If the head pointer of the List is NULL, it returns NULL.
 * It frees the memory of the last element and updates the tail pointer of the List.
 *
 * @param list A pointer to the List from which the last element's data will be extracted.
 * @return A pointer to the data of the last element if extraction is successful, otherwise NULL.
 */
    void* extractLast (adt_list_s* list);

    /**
 * @brief Extracts and returns the data of the element at the specified position in a List.
 *
 * This function extracts and returns the data of the element at the specified position in a List.
 * If the provided pointer to the List is NULL, it returns NULL.
 * If the List is empty, it returns NULL.
 * If the position is greater than or equal to the length of the List, it extracts the data of the last element.
 * If the head pointer of the List is NULL, it returns NULL.
 * It frees the memory of the extracted element and updates the pointers of the List accordingly.
 *
 * @param list A pointer to the List from which the element's data will be extracted.
 * @param position The position of the element to be extracted (0-indexed).
 * @return A pointer to the data of the extracted element if extraction is successful, otherwise NULL.
 */
    void* extractAt (adt_list_s* list, u16 position);

    /**
 * @brief Concatenates two Lists.
 *
 * This function concatenates the elements of two Lists by copying the data from each element of the source List
 * to a new element in the destination List. If either the source List or the destination List is NULL, it returns an error code.
 * It allocates memory for each new element and copies the data from the source List to the destination List.
 * If memory allocation fails, it returns an error code.
 * After concatenation, it updates the length and capacity of the destination List accordingly.
 *
 * @param list A pointer to the destination List where the elements will be concatenated.
 * @param list_src A pointer to the source List containing the elements to be concatenated.
 * @return An error code indicating the status of the concatenation operation.
 */
    s16 concat (adt_list_s* list, const adt_list_s* list_src);

    /**
 * @brief Traverses the elements of a List and applies a callback function to each element.
 *
 * This function traverses the elements of a List and applies a callback function to each element.
 * It checks if the List is NULL or if it is empty. If the List is NULL, it returns an error code indicating a NULL List.
 * If the List is empty, it returns an error code indicating an empty List.
 * Otherwise, it iterates through the List and applies the specified callback function to each element.
 * The callback function takes a MemoryNode pointer as an argument.
 * After traversing the List and applying the callback function to each element, it returns an error code indicating a successful traversal.
 *
 * @param list A pointer to the List to be traversed.
 * @param callback A function pointer to the callback function to be applied to each element of the List.
 * @return An error code indicating the status of the traversal operation.
 */
    s16  traverse (const adt_list_s* list, void (*callback)(memory_node_s*));

    /**
 * @brief Prints information about a List and its elements.
 *
 * This function prints information about a List and its elements.
 * It checks if the List is NULL. If the List is NULL, it prints a message indicating a NULL List and returns.
 * Otherwise, it prints information about the List, including its address, length, capacity, first and last addresses, and whether it is empty.
 * If the List is not empty, it iterates through the List and prints information about each element, including its address, size, data address, data content, and next address.
 *
 * @param list A pointer to the List to be printed.
 */
    void  print (adt_list_s* list);
};

/**
 * @brief Creates a new List with the specified capacity.
 *
 * This function creates a new List with the specified capacity.
 * It allocates memory for the List structure and initializes its fields, including length, capacity, head, tail, and operations.
 * If the specified capacity is less than or equal to 0, it returns NULL.
 * If memory allocation for the List structure fails, it returns NULL.
 *
 * @param capacity The capacity of the List to be created.
 * @return A pointer to the newly created List, or NULL if the capacity is invalid or memory allocation fails.
 */


#endif //__ADT_LIST_H__
