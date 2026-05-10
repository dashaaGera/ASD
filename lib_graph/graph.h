#include <stdexcept>
#include <vector>
#include <iostream>
#include "../lib_list/list.h"

template <typename T>
class Graph {
private:
    int count;
    std::vector<List<int>> adjacency_list;
public:
    Graph(int n);
    ~Graph() = default;
    bool has_edge(int x1, int x2) const;
    void add_edge(int x1, int x2);
    int _count() const;
    const List<int>& adjacent(int x) const;
    void print() const;
};

template <typename T>
Graph<T>::Graph(int n) : count(n) {
    if (n <= 0) {
        throw std::logic_error("Number of vertices must be positive");
    }
    adjacency_list.resize(n + 1);
}

template <typename T>
bool Graph<T>::has_edge(int x1, int x2) const {
    if (x1 < 1 || x1 > count || x2 < 1 || x2 > count) {
        return false;
    }

    const List<int>& adj_list = adjacency_list[x1];

    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        if (*it == x2) {
            return true;
        }
    }
    return false;
}

template <typename T>
void Graph<T>::add_edge(int x1, int x2) {
    if (x1 < 1 || x1 > count ||  x2 < 1 || x2 > count) {
        throw std::logic_error("Vertex index out of range");
    }

    if (!has_edge(x1, x2)) {
        adjacency_list[x1].push_back(x2);
    }
    if (!has_edge(x2, x1)) {
        adjacency_list[x2].push_back(x1);
    }
}

template <typename T>
int Graph<T>::_count() const {
    return count;
}

template <typename T>
const List<int>& Graph<T>::adjacent(int x) const {
    if (x < 1 || x > count) {
        throw std::logic_error("Vertex index out of range");
    }
    return adjacency_list[x];
}

template <typename T>
void Graph<T>::print() const {
    for (int i = 1; i <= count; i++) {
        std::cout << "Vertex " << i << ": ";
        const List<int>& adj_list = adjacency_list[i];

        for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
            std::cout << "-> " << *it << " ";
        }
        std::cout << std::endl;
    }
}

int find_min_distance_vertex(const std::vector<int>& distances,
    const std::vector<bool>& visited, int n) {
    int min_v = -1;
    int min_distance = INT_MAX; 

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && distances[i] != -1) {
            if (min_v == -1 || distances[i] < min_distance) {
                min_distance = distances[i];
                min_v = i;
            }
        }
    }
    return min_v;
}

void print_shortest_path(const std::vector<int>& prev, int start, int end) {
    if (start == end) {
        std::cout << start;
        return;
    }
    if (prev[end] == -1) {
        std::cout << "path no exist";
        return;
    }

    std::vector<int> path;
    int current = end;
    while (current != -1) {
        path.push_back(current);
        current = prev[current];
    }

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0) {
            std::cout << " -> ";
        }
    }
}

void dijkstra(const Graph<int>& graph, int start, int end) {
    int n = graph._count(); 

    if (start < 1 || start > n ||  end < 1 || end > n) {
        std::cout << "Uncorrect numbers of vertex" << std::endl;
        return;
    }

    std::vector<int> distances(n + 1, -1);
    std::vector<int> prev(n + 1, -1);
    std::vector<bool> visited(n + 1, false);
    distances[start] = 0;

    for (int i = 0; i < n; i++) {
        //ближ не посещ вершина
        int u = find_min_distance_vertex(distances, visited, n);

        if (u == -1) {  // Нет доступных вершин
            break;
        }

        if (u == end) {  // Достигли конечной вершины
            break;
        }

        visited[u] = true;
        const List<int>& neighbors = graph.adjacent(u);  

        // Проходим по соседям 
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            int v = *it;
            if (!visited[v]) {
                //если нашли путь короче или еще неизвестен
                int new_distance = distances[u] + 1;  
                if (distances[v] == -1 || new_distance < distances[v]) {
                    distances[v] = new_distance;
                    prev[v] = u;
                }
            }
        }
    }

    std::cout << "From vertix " << start << " to vertix " << end << std::endl;
    if (distances[end] == -1) {
        std::cout << "Path no exist" << std::endl;
    }
    else {
        std::cout << "Length shortes path: " << distances[end] << std::endl;
        std::cout << "Shortes path: ";
        print_shortest_path(prev, start, end);
        std::cout << std::endl;
    }
}