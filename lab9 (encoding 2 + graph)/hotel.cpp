#include <iostream>
#include <vector>
#include <queue>

class Graph{
private:
    std::vector<std::vector<int>> Data;
    std::vector<int> Dist;
public:
    Graph(int NumVert);
    void AddEdge(int Vert1, int Vert2);
    void BFS(int Start, int End);
};

int main() {
    int numVertices, numEdges;
    std::cin >> numVertices >> numEdges;
    Graph g(numVertices);
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        std::cin >> src >> dest;
        src--; dest--;
        g.AddEdge(src, dest);
    }
    int Start, End;
    std::cin>>Start>>End;
    g.BFS(Start-1, End-1);
    return 0;
}


Graph::Graph(int count){
    Data = std::vector<std::vector<int>>(count, std::vector<int>());
    Data.reserve(count);
    Dist = std::vector<int>(count, INT_MAX);
}

void Graph::AddEdge(int Vert1, int Vert2){
    Data[Vert1].emplace_back(Vert2);
    Data[Vert2].emplace_back(Vert1);
}

void Graph::BFS(int Start, int End) {
    std::queue<std::pair<int, int>> Queue;
    Queue.push(std::make_pair(Start, 0));
    Dist[Start] = 0;
    while (!Queue.empty()){
        int i = Queue.front().first;
        int d = Queue.front().second;
        Queue.pop();
        
        for(const auto &it: Data[i]) {
            if (Dist[it] == INT_MAX){
                Dist[it] = d + 1;
                Queue.push(std::make_pair(it, d+1));
            }
        }
    }
    if (Dist[End] != INT_MAX) {
        std::cout << Dist[End] << "\n";
    }
    else{
        std::cout<<"-1";
    }
}