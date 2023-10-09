/*
 * Typedefs and prototypes for graph.c
 */

#ifndef KRUSKAL_GRAPH_H
#define KRUSKAL_GRAPH_H

/// @brief Edge uv with u,v in G(V) and weight w
typedef struct edge
{
    int u;
    int v;
    int w;
} Edge;

/// @brief Graph G=(V,E) represented as a list of edges
typedef struct graph Graph;

/// @brief Creates a graph with n vertices and m edges
/// @param n The number of vertices in the graph
/// @param m The number of edges in the graph
/// @return A pointer to the newly created graph
Graph *graph_init(int n, int m);

/// @brief Frees the memory allocated for a graph
/// @param g The graph to free
void graph_free(Graph **g);

/// @brief Adds an edge uv to G
/// @param g The graph G to add the edge to
/// @param src The u vertex
/// @param dest The v vertex
/// @param weight The weight of the edge
void graph_add_edge(Graph *g, int src, int dest, int weight);

/// @brief Returns |V| of a graph G
/// @param g
/// @return The number of vertices of G
int graph_num_vertices(Graph *g);

/// @brief Returns |E| of a graph G
/// @param g
/// @return The number of edges of G
int graph_num_edges(Graph *g);

/// @brief Returns the list of edges of G
/// @param g
/// @return The list of edges of G
Edge *graph_get_edges(Graph *g);

#endif