/*
 * Typedefs and prototypes for heap.c
 */

#ifndef PRIM_HEAP_H
#define PRIM_HEAP_H

typedef struct heap MinHeap;
typedef struct heap_node HeapNode;

///@brief Returns an empty fixed-size heap with size n.
///@param size
///@param distances
///@return The initialized new heap with size n.
///@warning If the size is less than or equal to 0 or if the allocation fails
///, the function returns NULL.
MinHeap *min_heap_init(int size, unsigned int *distances);

/// @brief Returns 1 if the heap is empty, 0 otherwise.
/// @param heap
/// @return 1 if the heap is empty, 0 otherwise.
int min_heap_is_empty(MinHeap *heap);

/// @brief Returns 1 if the heap is full, 0 otherwise.
/// @param heap
/// @return 1 if the heap is full, 0 otherwise.
int min_heap_is_full(MinHeap *heap);

/// @brief Frees the memory allocated for the heap.
/// @param heap
void min_heap_free(MinHeap **heap);

void min_heap_insert(MinHeap *heap, int vertex, int value);

/// @brief Extracts the heap's root, calls heapify and returns the root's value.
/// @param heap
/// @return The heap's root vertex value, which maps to a vertex in the graph.
/// @note If the heap is empty or NULL, the function returns -1.
int min_heap_extract_min(MinHeap *heap);

/// @brief Updates the weight of a vertex in the heap.
/// @param heap
/// @param vertex
/// @param new_value
/// @note If the heap is NULL, the function returns without doing anything.
void min_heap_update_priority(MinHeap *heap, int vertex, int new_value);

#endif
