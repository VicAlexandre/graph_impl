#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

struct heap_node
{
    int vertex;
    int weight;
};

struct heap
{
    int current_size;
    int max_size;
    HeapNode *arr;
};

MinHeap *min_heap_init(int size, unsigned int *costs)
{
    if (size <= 0)
        return NULL;

    MinHeap *new_heap = malloc(sizeof(MinHeap));
    if (new_heap == NULL)
        return NULL;

    new_heap->arr = calloc(size, sizeof(HeapNode));
    if (new_heap->arr == NULL)
    {
        free(new_heap);
        return NULL;
    }

    new_heap->current_size = 0;
    new_heap->max_size = size;
    for (int i = 0; i < size; i++)
    {
        min_heap_insert(new_heap, i, costs[i]);
    }
    return new_heap;
}

int min_heap_is_empty(MinHeap *heap)
{
    return heap->current_size == 0;
}

int min_heap_is_full(MinHeap *heap)
{
    return heap->current_size == heap->max_size;
}

int min_heap_left_child(int i)
{
    return (i * 2) + 1;
}

int min_heap_right_child(int i)
{
    return (i * 2) + 2;
}

int min_heap_parent(int i)
{
    return (i - 1) / 2;
}

void min_heap_free(MinHeap **heap)
{
    if (*heap == NULL)
        return;

    free((*heap)->arr);
    free(*heap);

    *heap = NULL;
}

void min_heap_heapify_down(MinHeap *heap, int i)
{
    if (heap == NULL || i < 0 || i >= heap->current_size)
        return;

    int left = min_heap_left_child(i);
    int right = min_heap_right_child(i);

    int smallest = i;

    if (left < heap->current_size && heap->arr[left].weight < heap->arr[smallest].weight)
        smallest = left;

    if (right < heap->current_size && heap->arr[right].weight < heap->arr[smallest].weight)
        smallest = right;

    if (smallest != i)
    {
        HeapNode aux = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = aux;

        min_heap_heapify_down(heap, smallest);
    }
}

void min_heap_heapify_up(MinHeap *heap, int i)
{
    if (heap == NULL || i < 0 || i >= heap->current_size)
        return;

    while (i > 0 && heap->arr[min_heap_parent(i)].weight > heap->arr[i].weight)
    {
        HeapNode aux = heap->arr[i];
        heap->arr[i] = heap->arr[min_heap_parent(i)];
        heap->arr[min_heap_parent(i)] = aux;

        i = min_heap_parent(i);
    }
}

void min_heap_insert(MinHeap *heap, int vertex, int value)
{
    if (heap == NULL || min_heap_is_full(heap))
        return;

    heap->current_size++;
    heap->arr[heap->current_size - 1].weight = value;
    heap->arr[heap->current_size - 1].vertex = vertex;

    int i = heap->current_size - 1;

    while (i > 0 && heap->arr[min_heap_parent(i)].weight > heap->arr[i].weight)
    {
        HeapNode aux = heap->arr[i];
        heap->arr[i] = heap->arr[min_heap_parent(i)];
        heap->arr[min_heap_parent(i)] = aux;

        i = min_heap_parent(i);
    }
}

int min_heap_extract_min(MinHeap *heap)
{
    if (heap == NULL || min_heap_is_empty(heap))
        return -1;

    HeapNode min = heap->arr[0];
    heap->arr[0] = heap->arr[heap->current_size - 1];
    heap->current_size--;

    min_heap_heapify_down(heap, 0);

    return min.vertex;
}

void min_heap_update_priority(MinHeap *heap, int vertex, int new_value)
{
    if (heap == NULL)
        return;

    int i = 0;
    while (i < heap->current_size && heap->arr[i].vertex != vertex)
        i++;

    if (i == heap->current_size)
        return;

    heap->arr[i].weight = new_value;

    min_heap_heapify_up(heap, i);
}