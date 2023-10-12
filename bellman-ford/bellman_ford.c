#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "bf_graph.h"

void bf(Graph *g, int src, int *dist)
{
    int n = graph_num_vertices(g);
    Edge *edges = graph_get_edges(g);

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 0; j < graph_num_edges(g); j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;

            if (dist[v] != INT_MAX && dist[v] + w < dist[u])
                dist[u] = dist[v] + w;
        }
    }

    for (int i = 0; i < graph_num_edges(g); i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
        {
            printf("Graph contains negative weight cycle\n");
            exit(1);
        }

        if (dist[v] != INT_MAX && dist[v] + w < dist[u])
        {
            printf("Graph contains negative weight cycle\n");
            exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    char *output_file_name = NULL, *input_file_name = NULL;
    FILE *fin = NULL, *fout = NULL;
    int c, oflag = 0, starting_vertex = 0;

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
            break;

        case 'i':
            starting_vertex = atoi(optarg) - 1;
            break;

        default:
            return 1;
            break;
        }
    }

    int n, m;
    fscanf(fin, "%d %d", &n, &m);
    Graph *g = graph_init(n, m);

    for (int i = 0; i < m; i++)
    {
        int u, v, weight;
        fscanf(fin, "%d %d %d", &u, &v, &weight);
        graph_add_edge(g, u - 1, v - 1, weight);
    }

    fclose(fin);

    int dist[n];
    bf(g, starting_vertex, dist);

    graph_free(&g);

    for (int i = 0; i < n; i++)
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

    return 0;
}