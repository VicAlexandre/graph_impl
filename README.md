# Graph algorithms implementations
Implementations of four graph algorithms: Dijkstra's shortest path, Prim's and Kruskal's minimum spanning tree and ??? for the course
COMP369 - Teoria dos Grafos (Graph theory).

### Input file format
The input file format is as follows:
```
<vertex_count> <edge_count>
<edge_1_start> <edge_1_end> <edge_1_weight>
<edge_2_start> <edge_2_end> <edge_2_weight>
...
<edge_n_start> <edge_n_end> <edge_n_weight>
```

### Done:
- [x] Dijkstra's shortest path
- [x] Prim's minimum spanning tree

### To do:
- [ ] Kruskal's minimum spanning tree
- [ ] ???
- [ ] Heap optimization using a second array to store the heap indexes of each vertex

## Algorithms' usage

### Dijkstra's Shortest Path
To build and run:
```bash
cd dijkstra
make
./dijkstra <options>
```
Options:
```bash
-h              : displays this help and exits
-o <file>       : redirects output to file
-f <file>       : indicates the file that contains the graph 
-i              : starting vertex. default: 1
```
### Prim's Minimum Spanning Tree
To build and run:
```bash
cd prim
make
./prim <options>
```
Options:
```bash
-h              : displays this help and exits
-o <file>       : redirects output to file
-f <file>       : indicates the file that contains the graph 
-s              : prints all edges of the resultant MSP instead of it's cost
-i              : starting vertex. default: 1
```
## Author

* **Victor Alexandre da R. Monteiro Miranda** - :email: varm@ic.ufal.br