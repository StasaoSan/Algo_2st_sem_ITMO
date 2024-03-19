#include <iostream>
#include <vector>
#include "queue"
enum Color {WHITE, GRAY, BLACK};

class Graph {
    int count;
    std::vector<std::vector<int>> Data;
    std::vector<bool> visited;
public:
    Graph(int n);
    void AddEdge(int u, int v);
    bool HasHamiltonianCycle();
    bool DFS(int u, int n);
    int FatherNode();
};

Graph::Graph(int count) {
    this->count = count;
    Data = std::vector<std::vector<int>>(count, std::vector<int>());
    Data.reserve(count);
    visited = std::vector<bool>(count, false);
}

void Graph::AddEdge(int Vert1, int Vert2) {
    Data[Vert1].push_back(Vert2);
    Data[Vert2].push_back(Vert1);
}

bool Graph::DFS(int v, int count) {
    if (visited[v]) {
        return false;
    }
    visited[v] = true;
    if (visited == std::vector<bool>(count, true)) {
        return true;
    }
    for (int u : Data[v]) {
        if (DFS(u, count)) {
            return true;
        }
    }
    visited[v] = false;
    return false;
}

bool Graph::HasHamiltonianCycle() {
    if (DFS(FatherNode(), count)){
        return true;
    }
    return false;
}

int Graph::FatherNode() {
    int start = 0;
    std::queue<int> q;
    std::vector<bool> visited(Data.size(), false);
    std::vector<int> dist(Data.size(), 0);
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : Data[v]) {
            if (!visited[u]) {
                visited[u] = true;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }

    int AnsVer = start;
    for (int i = 0; i < Data.size(); i++) {
        if (dist[i] > dist[AnsVer]) {
            AnsVer = i;
        }
    }
    return AnsVer;
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
    if (g.HasHamiltonianCycle()) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}