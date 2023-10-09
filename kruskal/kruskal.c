/*
 * Kruskal's algorithm for finding the minimum spanning tree of a graph
 * Input: a graph G = (V, E) and a source vertex s
 * Output: the MSP of G or it's cost
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "union_find.h"
#include "graph.h"
#include "quicksort.h"

int kruskal(Graph *g, Edge *msp, int s)
{
    int parent[graph_num_vertices(g)];
    int rank[graph_num_vertices(g)];
    Edge *edges = graph_get_edges(g);
    int msp_cnt = 0, msp_cost = 0;

    quick_sort(edges, 0, graph_num_edges(g) - 1);

    for (int i = 0; i < graph_num_vertices(g); i++)
        make_set(i, parent, rank);

    for (int i = 0; i < graph_num_edges(g); i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(u, parent) != find(v, parent))
        {
            msp[msp_cnt++] = edges[i];
            msp_cost += edges[i].w;
            join(find(u, parent), find(v, parent), parent, rank);
        }
    }

    return msp_cost;
}

int main(int argc, char **argv)
{
    char *output_file_name = NULL, *input_file_name = NULL;
    FILE *fin = NULL, *fout = NULL;
    int c, oflag = 0, sflag = 0, starting_vertex = 1;

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

    Edge msp[n - 1];
    int msp_cost = kruskal(g, msp, starting_vertex);

    graph_free(&g);

    if (oflag)
    {
        if (sflag)
        {
            for (int i = 0; i < m; i++)
            {
                fprintf(fout, "(%d:%d) ", msp[i].u + 1, msp[i].v + 1);
                fclose(fout);
            }
        }
        else
            fprintf(fout, "%u\n", msp_cost);
        return 0;
    }
    if (sflag)
    {
        for (int i = 0; i < n - 1; i++)
            printf("(%d,%d) ", msp[i].u + 1, msp[i].v + 1);

        printf("\n");
    }
    else
        printf("%u\n", msp_cost);

    return 0;
}