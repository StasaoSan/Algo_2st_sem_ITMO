#include <iostream>
#include <vector>
#include <queue>

class Graph {
private:
    int64_t N, M;
    struct Edge {
        int64_t src, dest, capacity;
    };
    std::vector<Edge> Data;
    std::vector<std::vector<int64_t>> adj;
    std::vector<std::vector<int64_t>> capacity;

public:
    Graph(int64_t numVertices, int64_t numEdges);
    void AddEdge(int64_t src, int64_t dest, int64_t weight);
    int64_t MaxFlow(int64_t source, int64_t sink);
};

Graph::Graph(int64_t numVertices, int64_t numEdges) : N(numVertices), M(numEdges) {
    Data.resize(numEdges);
    adj.resize(N + 1);
    capacity.resize(N + 1, std::vector<int64_t>(N + 1, 0));
}

void Graph::AddEdge(int64_t src, int64_t dest, int64_t weight) {
    static int64_t i = 0;
    Data[i++] = {src, dest, weight};
    adj[src].push_back(dest);
    adj[dest].push_back(src);
    capacity[src][dest] += weight;
}

int64_t bfs(std::vector<int64_t> &parent, int64_t source, int64_t sink, const std::vector<std::vector<int64_t>> &adj, const std::vector<std::vector<int64_t>> &capacity) {
    std::fill(parent.begin(), parent.end(), -1);
    parent[source] = source;

    std::queue<std::pair<int64_t, int64_t>> q;
    q.push({source, INT64_MAX});

    while (!q.empty()) {
        int64_t node = q.front().first;
        int64_t flow = q.front().second;
        q.pop();

        for (int64_t next : adj[node]) {
            if (parent[next] == -1 && capacity[node][next] > 0) {
                parent[next] = node;
                int64_t new_flow = std::min(flow, capacity[node][next]);

                if (next == sink)
                    return new_flow;

                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int64_t Graph::MaxFlow(int64_t source, int64_t sink) {
    int64_t flow = 0;
    std::vector<int64_t> parent(N + 1);
    int64_t new_flow;

    while (new_flow = bfs(parent, source, sink, adj, capacity)) {
        flow += new_flow;
        int64_t node = sink;
        while (node != source) {
            int64_t prev = parent[node];
            capacity[prev][node] -= new_flow;
            capacity[node][prev] += new_flow;
            node = prev;
        }
    }

    return flow;
}

int main() {
    int64_t numVertices, numEdges;
    std::cin >> numVertices >> numEdges;
    Graph g(numVertices, numEdges);


    for (int64_t i = 0; i < numEdges; ++i) {
        int64_t src, dest, weight;
        std::cin >> src >> dest >> weight;
        g.AddEdge(src, dest, weight);
    }

    int64_t source = 1;
    int64_t sink = numVertices;

    std::cout << g.MaxFlow(source, sink) << std::endl;

    return 0;
}