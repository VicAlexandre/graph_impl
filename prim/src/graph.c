#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct node
{
    int vertex;
    int weight;
    struct node *next;
};

struct graph
{
    int num_vertices;
    AdjNode **adj_list;
};

AdjNode *create_node(int vertex, int weight)
{
    AdjNode *new_node = malloc(sizeof(AdjNode));
    if (new_node == NULL)
        return NULL;

    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

Graph *graph_init(int num_vertices)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL)
        return NULL;

    graph->num_vertices = num_vertices;
    graph->adj_list = calloc(num_vertices, sizeof(AdjNode *));
    if (graph->adj_list == NULL)
        return NULL;

    for (int i = 0; i < num_vertices; i++)
        graph->adj_list[i] = NULL;

    return graph;
}

void graph_free(Graph **graph)
{
    if (graph == NULL || *graph == NULL)
        return;

    for (int i = 0; i < (*graph)->num_vertices; i++)
    {
        AdjNode *aux = (*graph)->adj_list[i];
        while (aux)
        {
            AdjNode *next = aux->next;
            free(aux);
            aux = next;
        }
    }
    free((*graph)->adj_list);
    free(*graph);
    *graph = NULL;
}

void graph_add_arc(Graph *g, int src, int dest, int weight)
{
    if (g == NULL || src > g->num_vertices || dest > g->num_vertices || src < 1 || dest < 1)
        return;

    AdjNode *new_v = malloc(sizeof(AdjNode));
    if (!new_v)
        return;

    new_v->vertex = dest;
    new_v->weight = weight;
    new_v->next = g->adj_list[src - 1];
    g->adj_list[src - 1] = new_v;
}

void graph_add_edge(Graph *g, int src, int dest, int weight)
{
    graph_add_arc(g, src, dest, weight);
    graph_add_arc(g, dest, src, weight);
}

int graph_num_vertices(Graph *g)
{
    return g->num_vertices;
}

AdjNode *graph_adj_list(Graph *g, int v)
{
    return g->adj_list[v];
}

int graph_adj_vertex(AdjNode *n)
{
    return n->vertex;
}

int graph_adj_weight(AdjNode *n)
{
    return n->weight;
}

AdjNode *graph_adj_next(AdjNode *n)
{
    return n->next;
}