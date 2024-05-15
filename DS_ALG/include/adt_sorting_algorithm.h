
#ifndef __ADT_SORTING_ALGORITHM_H__
#define __ADT_SORTING_ALGORITHM_H__

#include "adt_memory_node.h"
#include "adt_vector.h"

/**
 * @brief Sorts a vector using the bubble sort algorithm.
 *
 * This function sorts the elements of a vector in ascending order using the
 * bubble sort algorithm. It repeatedly steps through the list, compares
 * adjacent elements and swaps them if they are in the wrong order.
 *
 * @param vector A pointer to the Vector structure to be sorted.
 * @param n The number of elements in the vector.
 */
inline void bubbleSort(Vector* vector, int n) {
    int i, j, temp;
    
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }

    printf("\n");
   
    
    int swapped = 1;
    i = 0;

    while (swapped) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (*(u8*)vector->storage_[j].data_ > *(u8*)vector->storage_[j + 1].data_) {
                temp = vector->storage_[j].data_;
                vector->storage_[j].data_ = vector->storage_[j + 1].data_;
                vector->storage_[j + 1].data_ = temp;
                swapped = 1;
            }
        }
        i++;
    }
     
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }
    printf("\n");
}

/**
 * @brief Sorts a vector using the selection sort algorithm.
 *
 * This function sorts the elements of a vector in ascending order using the
 * selection sort algorithm. It divides the list into two parts: a sorted
 * sublist of items which is built up from left to right at the front (left) of the list
 * and a sublist of the remaining unsorted items. The algorithm proceeds by
 * finding the smallest (or largest, depending on sorting order) element from the
 * unsorted sublist, swapping it with the leftmost unsorted element, and moving
 * the sublist boundaries one element to the right.
 *
 * @param vector A pointer to the Vector structure to be sorted.
 * @param n The number of elements in the vector.
 */
inline void selectionSort(Vector* vector, int n) {
    int i, j, min_idx, temp;

    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }
    printf("\n");

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (*(u8*)vector->storage_[j].data_ < *(u8*)vector->storage_[min_idx].data_) {
                min_idx = j;
            }
        }
        temp = vector->storage_[min_idx].data_;
        vector->storage_[min_idx].data_ = vector->storage_[i].data_;
        vector->storage_[i].data_ = temp;
    }

    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }
    printf("\n");
}

#endif //__ADT_SORTING_ALGORITHM_H__ vector->storage_[i].data_

