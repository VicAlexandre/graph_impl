#include "union_find.h"
#include <stdlib.h>

void make_set(int x, int *parent, int *rank)
{
    parent[x] = x;
    rank[x] = 0;
}

int find(int x, int *parent)
{
    if (parent[x] != x)
        parent[x] = find(parent[x], parent);
    return parent[x];
}

void join(int x, int y, int *parent, int *rank)
{
    if (rank[x] >= rank[y])
    {
        parent[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }
    else
        parent[x] = y;
}