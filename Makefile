make:
	cd dijkstra && make comp_to_root && cd .. && cd prim && make comp_to_root && cd .. && cd kruskal && make comp_to_root && cd .. && cd bellman-ford && make comp_to_root

clean:
	rm dj pr kr bf