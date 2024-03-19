#include <iostream>
#include <vector>

class Graph {
private:
    int N, M;
    struct Bridge {
        int a, b, c;
    };
    std::vector<Bridge> Data;

public:
    Graph(int numVertices, int numEdges);
    void AddEdge(int src, int dest, int weight);
    int Kruskal();
    static bool compareBridges(const Bridge &Bridge1, const Bridge &Bridge2);
};

Graph::Graph(int numVertices, int numEdges) : N(numVertices), M(numEdges) {
    Data.resize(numEdges);
}

void Graph::AddEdge(int src, int dest, int weight) {
    static int i = 0;
    Data[i++] = {src, dest, weight};
}

int findParent(std::vector<int> &parent, int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void unionSets(std::vector<int> &parent, int x, int y) {
    x = findParent(parent, x);
    y = findParent(parent, y);
    if (x != y)
        parent[y] = x;
}

bool Graph::compareBridges(const Bridge &Bridge1, const Bridge &Bridge2) {
    return Bridge1.c < Bridge2.c;
}

int Graph::Kruskal() {
    sort(Data.begin(), Data.end(), compareBridges);

    std::vector<int> parent(N + 1);
    for (int i = 1; i <= N; ++i)
        parent[i] = i;

    int minDays = 0;
    for (const Bridge &bridge : Data) {
        if (findParent(parent, bridge.a) != findParent(parent, bridge.b)) {
            unionSets(parent, bridge.a, bridge.b);
            minDays += bridge.c;
        }
    }

    return minDays;
}

int main() {
    int numVertices, numEdges;
    std::cin >> numVertices >> numEdges;
    Graph g(numVertices, numEdges);

    for (int i = 0; i < numEdges; ++i) {
        int Vert1, Vert2, weight;
        std::cin >> Vert1 >> Vert2 >> weight;
        g.AddEdge(Vert1, Vert2, weight);
    }

    std::cout << g.Kruskal() << std::endl;
}