#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <bits/getopt_core.h>
#include "heap.h"
#include "graph.h"

unsigned int *dijkstra(Graph *g, int src)
{
    unsigned int *dist = calloc(graph_num_vertices(g), sizeof(unsigned int));
    int *prev = calloc(graph_num_vertices(g), sizeof(int));

    for (int i = 0; i < graph_num_vertices(g); i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[src - 1] = 0;

    MinHeap *heap = min_heap_init(graph_num_vertices(g), dist);
    if (heap == NULL)
        return -1;

    while (!min_heap_is_empty(heap))
    {
        int u = min_heap_extract_min(heap);
        AdjNode *aux = graph_adj_list(g, u);

        while (aux)
        {
            int v = graph_adj_vertex(aux) - 1;
            int w = graph_adj_weight(aux);

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                min_heap_update_priority(heap, v, dist[v]);
            }

            aux = graph_adj_next(aux);
        }
    }
    min_heap_free(&heap);
    return dist;
}

int main(int argc, char **argv)
{
    char *output_file_name = NULL, *input_file_name = NULL;
    FILE *fin = NULL, *fout = NULL;
    int c, oflag = 0, iflag = 0, starting_vertex = 1;

    while ((c = getopt(argc, argv, "ho:f:i:")) != -1)
    {
        switch (c)
        {
        case 'h':
            printf("-h\t\t: displays this help and exits\n-o <file>\t: redirects output to file\n-f <file>\t: indicates the file that contains the graph \n-i\t\t: starting vertex. default: 1\n");
            return 0;
            break;

        case 'o':
            output_file_name = optarg;
            fout = fopen(output_file_name, "w");
            oflag = 1;
            break;

        case 'f':
            input_file_name = optarg;
            fin = fopen(input_file_name, "r");
            iflag = 1;
            break;

        case 'i':
            starting_vertex = atoi(optarg);
            break;

        default:
            return 1;
            break;
        }
    }

    if (!iflag)
    {
        printf("ERROR: no input file provided\n");
        return 1;
    }

    int n, m;
    fscanf(fin, "%d %d", &n, &m);
    Graph *g = graph_init(n);

    for (int i = 0; i < m; i++)
    {
        int u, v, weight;
        fscanf(fin, "%d %d %d", &u, &v, &weight);
        graph_add_edge(g, u, v, weight);
    }

    fclose(fin);

    unsigned int *dist = dijkstra(g, starting_vertex);
    for (int i = 0; i < graph_num_vertices(g); i++)
    {
        if (dist[i] == INT_MAX)
            dist[i] = -1;
        if (oflag)
        {
            fprintf(fout, "%d:%d ", i + 1, dist[i]);
            continue;
        }
        printf("%d:%d ", i + 1, dist[i]);
    }
    printf("\n");

    if (fout)
        fclose(fout);
    free(dist);
    graph_free(&g);

    return 0;
}