#include <iostream>
#include <vector>

enum Color {WHITE, GRAY, BLACK};

class Graph {
    int count;
    std::vector<std::vector<int>> Data;
    std::vector<Color> color;

public:
    Graph(int n);
    void AddEdge(int u, int v);
    bool HasCycle();
    bool DFS(int u, int parent);
};

Graph::Graph(int count) {
    this->count = count;
    Data = std::vector<std::vector<int>>(count, std::vector<int>());
    Data.reserve(count);
    color = std::vector<Color>(count , WHITE);
}

void Graph::AddEdge(int Vert1, int Vert2) {
    Data[Vert1].push_back(Vert2);
    Data[Vert2].push_back(Vert1);
}

bool Graph::HasCycle() {
    for (int u = 0; u < count; u++) {
        if (color[u] == WHITE) {
            if (DFS(u, -1)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::DFS(int u, int parent) {
    color[u] = GRAY;
    for (int v : Data[u]) {
        if (color[v] == WHITE) {
            if (DFS(v, u)) {
                return true;
            }
        } else if (v != parent) {
            return true;
        }
    }
    color[u] = BLACK;
    return false;
}

int main() {
    int Vert, Edge;
    std::cin >> Vert >> Edge;

    Graph g(Vert);
    for (int i = 0; i < Edge; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        v1--; v2--;
        g.AddEdge(v1, v2);
    }

    if (g.HasCycle()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}