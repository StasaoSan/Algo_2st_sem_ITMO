#include <iostream>
#include <vector>

class Graph {
private:
    int64_t N, M;
    struct Bridge {
        int64_t a, b, c;
    };
    std::vector<Bridge> Data;

public:
    Graph(int64_t numVertices, int64_t numEdges);
    void AddEdge(int64_t src, int64_t dest, int64_t weight);
    int64_t Kruskal();
    static bool compareBridges(const Bridge &Bridge1, const Bridge &Bridge2);
};

Graph::Graph(int64_t numVertices, int64_t numEdges) : N(numVertices), M(numEdges) {
    Data.resize(numEdges);
}

void Graph::AddEdge(int64_t src, int64_t dest, int64_t weight) {
    static int64_t i = 0;
    Data[i++] = {src, dest, weight};
}

int64_t findParent(std::vector<int64_t> &parent, int64_t x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void unionSets(std::vector<int64_t> &parent, int64_t x, int64_t y) {
    x = findParent(parent, x);
    y = findParent(parent, y);
    if (x != y)
        parent[y] = x;
}

bool Graph::compareBridges(const Bridge &Bridge1, const Bridge &Bridge2) {
    return Bridge1.c < Bridge2.c;
}

int64_t Graph::Kruskal() {
    sort(Data.begin(), Data.end(), compareBridges);

    std::vector<int64_t> parent(N + 1);
    for (int64_t i = 1; i <= N; ++i)
        parent[i] = i;

    int64_t minDays = 0;
    for (const Bridge &bridge : Data) {
        if (findParent(parent, bridge.a) != findParent(parent, bridge.b)) {
            unionSets(parent, bridge.a, bridge.b);
            minDays += bridge.c;
        }
    }

    return minDays;
}

int main() {
    int64_t numVertices, numEdges;
    std::cin >> numVertices >> numEdges;
    Graph g(numVertices, numEdges);

    for (int64_t i = 0; i < numEdges; ++i) {
        int64_t Vert1, Vert2, weight;
        std::cin >> Vert1 >> Vert2 >> weight;
        g.AddEdge(Vert1, Vert2, weight);
    }

    std::cout << g.Kruskal() << std::endl;
}
