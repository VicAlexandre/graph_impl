/*
 * Typedefs and prototypes for graph.c
 */

#ifndef PRIM_GRAPH_H
#define PRIM_GRAPH_H

typedef struct node AdjNode;

typedef struct graph Graph;

/// @brief Creates a graph with num_vertices vertices
/// @param num_vertices The number of vertices in the graph
/// @return The initialized graph
Graph *graph_init(int num_vertices);

/// @brief Frees the memory allocated for the graph
/// @param graph The graph to be freed
void graph_free(Graph **graph);

/// @brief Adds an edge uv to G
/// @param graph The graph G to add the edge to
/// @param src The u vertex
/// @param dest The v vertex
/// @param weight The weight of the edge
void graph_add_edge(Graph *graph, int src, int dest, int weight);

/// @brief Adds an arc uv to G
/// @param g The graph G to add the arc to
/// @param src The u vertex (source)
/// @param dest The v vertex (destination)
/// @param weight The weight of the arc
void graph_add_arc(Graph *g, int src, int dest, int weight);

/// @brief Returns |V| of a graph G
/// @param g
/// @return The number of vertices of G
int graph_num_vertices(Graph *g);

/// @brief Returns the adjacency list of a vertex v
/// @param g The graph G
/// @param v The vertex
/// @return The adjacency list N+(V)
AdjNode *graph_adj_list(Graph *g, int v);

/// @brief Returns the adjacency list of a vertex v
/// @param g The graph G
/// @param v The vertex
/// @return The adjacency list N-(V)
int graph_adj_vertex(AdjNode *n);

/// @brief Returns the weight of an edge uv
/// @param n The adjacency list node
/// @return The weight w(u,v) of the edge uv
int graph_adj_weight(AdjNode *n);

/// @brief Returns the next node in the adjacency list
/// @param n The adjacency list node
/// @return The next node in the adjacency list
AdjNode *graph_adj_next(AdjNode *n);

#endif