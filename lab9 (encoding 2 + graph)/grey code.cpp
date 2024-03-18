#include <iostream>
#include <vector>
#include <cmath>

std::vector<bool> GAY(const std::vector<bool> &BinVec);

int main() {
    int size;
    std::cin>>size;
    int CountPow = pow(2, size);
    std::vector<std::vector<bool>> BinRaw;
    for (int i = 0; i < CountPow; i++) {
        std::vector<bool> temp(size, false);
        int number = i;
        for (int j = size - 1; j >= 0; j--) {
            if (number > 0) {
                temp[j] = (number % 2 == 1);
                number /= 2;
            }
        }
        BinRaw.emplace_back(GAY(temp));
    }
    // вывод вектора векторов bool
    for (const auto& binary_vector : BinRaw) {
        for (const auto& binary_digit : binary_vector) {
            std::cout << binary_digit;
        }
        std::cout << std::endl;
    }
    return 0;
}


std::vector<bool> GAY(const std::vector<bool> &BinVec) {
    std::vector<bool> Gray;
    for (int i = 0; i < BinVec.size(); ++i) {
        if (i == 0) {
            Gray.emplace_back(BinVec[i]);
        } else {
            if (BinVec[i - 1] == 0)
                Gray.emplace_back(BinVec[i]);
            else {
                Gray.emplace_back(!BinVec[i]);
            }
        }
    }
    return Gray;
}