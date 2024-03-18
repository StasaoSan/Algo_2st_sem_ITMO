#include <iostream>
#include <vector>

void IsOneRoom(std::vector<std::vector<char>> &Data, int &Count, const int &i, const int &j);

int main() {
    int Height, Width, Count = 0;
    std::vector<std::vector<char>> Data;
    std::cin >> Height >> Width;
    char sim;
    for (int i = 0; i < Height; ++i) {
        std::vector<char> TempVec;
        for (int j = 0; j < Width; ++j) {
            std::cin >> sim;
            TempVec.emplace_back(sim);
        }
        Data.emplace_back(TempVec);
    }
    for (int i = 0; i < Data.size(); ++i) {
        for (int j = 0; j < Data[i].size(); ++j) {
            if (Data[i][j] == '.') {
                IsOneRoom(Data, Count, i, j);
                Count++;
            }
        }
    }
    std::cout << Count;
    return 0;
}

void IsOneRoom(std::vector<std::vector<char>> &Data, int &Count, const int &i, const int &j) {
    Data[i][j] = '#';
    if (i > 0 && Data[i + 1][j] == '.') {
        IsOneRoom(Data, Count, i + 1, j);
    }
    if (i < Data.size() - 1 && Data[i - 1][j] == '.') {
        IsOneRoom(Data, Count, i - 1, j);
    }
    if (j > 0 && Data[i][j + 1] == '.') {
        IsOneRoom(Data, Count, i, j + 1);
    }
    if (j < Data[0].size() - 1 && Data[i][j - 1] == '.') {
        IsOneRoom(Data, Count, i, j - 1);
    }
    return;
}