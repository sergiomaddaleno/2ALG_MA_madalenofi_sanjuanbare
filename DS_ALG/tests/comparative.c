// comparative.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// File for comparative of ADTs

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EDK_MemoryManager/edk_memory_manager.h"
#include "EDK_MemoryManager/edk_platform_types.h"
#include "common_def.h"
#include "adt_vector.h"
#include "adt_list.h"

#include "./../tests/test_base.c"
#include "adt_dll_list.h"
#include "adt_sorting_algorithm.h"

void* data[250];
Vector* vector_1 = NULL;
//Vector* vector_2 = NULL;
//List* list_1 = NULL;
//List* list_2 = NULL;
//DLL_List* list_dll_1 = NULL;
//DLL_List* list_dll_2 = NULL;

void TESTBASE_generateDataForComparative() {
	//TODO some stuff
	
	
	vector_1 = VECTOR_create(250);
	//vector_1 = VECTOR_create(250);
	//vector_1 = LIST_create(10);
	//list_2 = LIST_create(250);
	//list_dll_1 = DLL_LIST_create(250);
	//list_dll_2 = DLL_LIST_create(250);
	
	for (s16 i = 0; i < 250; i++) {
		data[i] = MM->malloc(sizeof(u8));
		*((u8*)data[i]) = rand();
		//printf("%d\n", *((u8*)data[i]));

		vector_1->ops_->insertLast(vector_1, data[i], sizeof(u8));

		//printf("%d\n", *((u8*) (vector_1->storage_[i].data_)));
	}


}

void calculateTimeForFunction() {
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	double elapsed_time = 0.0f;
	u32 repetitions = 1;

	///////////////////////////////////////////////////////////////////////
	// Frequency: ticks per second
	QueryPerformanceFrequency(&frequency);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// Meassurement time
	// start timer
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 rep = 0; rep < repetitions; ++rep) {
		//TODO execute function
		//printf("%d\n", vector_1->storage_[rep].data_);
		selectionSort(vector_1, 250);
		//list_1->ops_->insertFirst(list_1,data[rep],strlen(data[rep])+1);
		 //for extracts;
	}

	for (u32 rep = 0; rep < 250; ++rep) {
		MM->free(data[rep]);
	}
	//list_1->ops_->reset(list_1);
	//list_1->ops_->destroy(list_1);
	// stop timer
	QueryPerformanceCounter(&time_end);
	///////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////
	// compute the elapsed time in microseconds
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	printf("Elapsed time: %f ms\n", elapsed_time);
	///////////////////////////////////////////////////////////////////////
	// compute the average time
	double average_time = elapsed_time / repetitions;
	printf("Average time: %f ms\n", average_time);
	///////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
	srand(time(NULL));
	TESTBASE_generateDataForComparative();
	calculateTimeForFunction();
	MM->status();
	printf("Press ENTER to continue\n");
	getchar();
	MM->destroy();
	return 0;
}
