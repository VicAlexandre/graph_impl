#include "quicksort.h"

void swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Edge arr[], int start, int end)
{
    int pivot = arr[end].w;
    int i = start - 1;

    for (int j = start; j <= end - 1; j++)
    {
        if (arr[j].w < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);

    return i;
}

void quick_sort(Edge arr[], int start, int end)
{
    if (end <= start)
        return;

    int pivot = partition(arr, start, end);

    quick_sort(arr, start, pivot - 1);
    quick_sort(arr, pivot + 1, end);
}