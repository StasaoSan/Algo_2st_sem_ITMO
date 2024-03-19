#include <iostream>
#include <vector>

class Graph {
    int count;
    std::vector<std::vector<int>> Data;
public:
    Graph(int n);
    void AddEdge(int u, int v);
    bool Kun(int v, std::vector<int> &mt, std::vector<bool> &used);
    int getMaxTiles();
};

Graph::Graph(int count) {
    this->count = count;
    Data = std::vector<std::vector<int>>(count, std::vector<int>());
}

void Graph::AddEdge(int Vert1, int Vert2) {
    Data[Vert1].push_back(Vert2);
    Data[Vert2].push_back(Vert1);
}

bool Graph::Kun(int v, std::vector<int> &mt, std::vector<bool> &used) {
    if (used[v]) return false;
    used[v] = true;
    for (int u : Data[v]) {
        if (mt[u] == -1 || Kun(mt[u], mt, used)) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

int Graph::getMaxTiles() {
    std::vector<int> mt(count, -1);
    std::vector<bool> used;

    int MaxCell = 0;
    for (int i = 0; i < count; ++i) {
        used.assign(count, false);
        if (Kun(i, mt, used)) {
            ++MaxCell;
        }
    }

    return MaxCell;
}

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<bool>> board(n, std::vector<bool>(m, false));

    for (int i = 0; i < q; ++i) {
        int row, col;
        std::cin >> row >> col;
        board[row - 1][col - 1] = true;
    }

    Graph g(n * m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!board[i][j] && (i + j) % 2 == 0) {
                int dx[] = {-1, 1, 0, 0};
                int dy[] = {0, 0, -1, 1};

                for (int k = 0; k < 4; ++k) {
                    int iNeib = i + dx[k];
                    int jNeib = j + dy[k];

                    if (iNeib >= 0 && iNeib < n && jNeib >= 0 && jNeib < m && !board[iNeib][jNeib]) {
                        g.AddEdge(i * m + j, iNeib * m + jNeib);
                    }
                }
            }
        }
    }

    std::cout << g.getMaxTiles() << std::endl;

    return 0;
}