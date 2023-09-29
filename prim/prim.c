#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <bits/getopt_core.h>
#include "heap.h"
#include "graph.h"

unsigned int prim(Graph *g, unsigned int *msp, int src)
{
    unsigned int msp_cost = 0;
    unsigned int cost[graph_num_vertices(g)];
    int prev[graph_num_vertices(g)];

    for (int i = 0; i < graph_num_vertices(g); i++)
    {
        msp[i] = 0;
        cost[i] = INT_MAX;
        prev[i] = -1;
    }

    cost[src - 1] = 0;

    MinHeap *heap = min_heap_init(graph_num_vertices(g), cost);
    if (heap == NULL)
        return -1;

    while (!min_heap_is_empty(heap))
    {
        unsigned int u = min_heap_extract_min(heap);
        AdjNode *aux = graph_adj_list(g, u);

        msp[u] = prev[u];
        msp_cost += cost[u];

        while (aux)
        {
            int v = graph_adj_vertex(aux) - 1;
            int w = graph_adj_weight(aux);

            if (!msp[v] && cost[v] > w)
            {
                prev[v] = u;
                cost[v] = w;
                min_heap_update_priority(heap, v, cost[v]);
            }

            aux = graph_adj_next(aux);
        }
    }
    min_heap_free(&heap);
    return msp_cost;
}

int main(int argc, char **argv)
{
    char *output_file_name = NULL, *input_file_name = NULL;
    FILE *fin = NULL, *fout = NULL;
    int c, oflag = 0, iflag = 0, sflag = 0, starting_vertex = 1;

    while ((c = getopt(argc, argv, "sho:f:i:")) != -1)
    {
        switch (c)
        {
        case 'h':
            printf("-h\t\t: displays this help and exits\n-o <file>\t: redirects output to file\n-f <file>\t: indicates the file that contains the graph \n-s\t\t: prints all edges of the resultant MSP instead of it's cost\n-i\t\t: starting vertex. default: 1\n");
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

        case 's':
            sflag = 1;
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

    unsigned int msp[n];
    unsigned int msp_cost = prim(g, msp, starting_vertex);

    graph_free(&g);

    if (oflag)
    {
        if (sflag)
        {
            for (int i = 0; i < n; i++)
            {
                fprintf(fout, "(%d:%d) ", i + 1, msp[i]);
                fclose(fout);
            }
        }
        else
            fprintf(fout, "%u\n", msp_cost);
        return 0;
    }
    if (sflag)
    {
        for (int i = 0; i < n; i++)
        {
            if (msp[i] == -1)
                continue;
            printf("(%d,%d) ", i + 1, msp[i] + 1);
        }
        printf("\n");
    }
    else
        printf("%u\n", msp_cost);

    return 0;
}