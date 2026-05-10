#include "../lib_graph/graph.h"
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {

    Graph<int> graph(9);

    graph.add_edge(1, 2);
    graph.add_edge(1, 5);
    graph.add_edge(2, 3);
    graph.add_edge(2, 6);
    graph.add_edge(3, 4);
    graph.add_edge(6, 7);
    graph.add_edge(5, 7);
    graph.add_edge(8, 9);

    graph.print();

    std::cout << "Edge 1-2 consist?: " << graph.has_edge(1, 2) << std::endl;
    std::cout << "Edge 2-1 consist?: " << graph.has_edge(2, 1) << std::endl;

    dijkstra(graph, 4, 1);
    dijkstra(graph, 8, 2);

}