
#ifndef __ADT_SORTING_ALGORITHM_H__
#define __ADT_SORTING_ALGORITHM_H__

#include "adt_memory_node.h"
#include "adt_vector.h"


inline void bubbleSort(Vector* vector, int n) {
    int i, j, temp;
    
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }

    printf("\n");
   
    
    int swapped = 1; // 1 representa verdadero, 0 representa falso
    i = 0;

    while (swapped) {
        swapped = 0; // Establecer a falso al comienzo de cada iteración
        for (int j = 0; j < n - i - 1; j++) {
            if (*(u8*)vector->storage_[j].data_ > *(u8*)vector->storage_[j + 1].data_) {
                temp = vector->storage_[j].data_;
                vector->storage_[j].data_ = vector->storage_[j + 1].data_;
                vector->storage_[j + 1].data_ = temp;
                swapped = 1; // Se ha realizado un intercambio, por lo tanto, continuamos ordenando
            }
        }
        i++;
    }
     
    for (i = 0; i < n - 1; i++) {
        printf("%d, ", *((u8*)(vector->storage_[i].data_)));
    }
    printf("\n");
}

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

