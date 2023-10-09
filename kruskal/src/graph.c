#include <stdlib.h>
#include "graph.h"

struct graph
{
    int n;
    int m;
    Edge *edges;
};

Graph *graph_init(int n, int m)
{
    Graph *g = malloc(sizeof(Graph));
    if (g == NULL)
        return NULL;

    g->n = n;
    g->m = 0;
    g->edges = calloc(m, sizeof(Edge));
    return g;
}

void graph_free(Graph **g)
{
    free((*g)->edges);
    free(*g);
    *g = NULL;
}

void graph_add_edge(Graph *g, int src, int dest, int weight)
{
    g->edges[g->m].u = src;
    g->edges[g->m].v = dest;
    g->edges[g->m].w = weight;
    g->m++;
}

int graph_num_vertices(Graph *g)
{
    return g->n;
}

int graph_num_edges(Graph *g)
{
    return g->m;
}

Edge *graph_get_edges(Graph *g)
{
    return g->edges;
}