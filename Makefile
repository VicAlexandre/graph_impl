make:
	cd dijkstra && make && cd .. && cd prim && make && cd .. && cd kruskal && make

clean:
	cd dijkstra && make clean && cd .. && cd prim && make clean && cd .. && cd kruskal && make clean