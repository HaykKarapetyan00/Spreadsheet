#include "SpreadSheet.h"
#include <iostream>

int main() {
    SpreadSheet ob(5, 5);

    std::cout << "Enter values for the spreadsheet:" << std::endl;
    for (size_t i = 0; i < ob.row(); ++i) {
        for (size_t j = 0; j < ob.col(); ++j) {
            std::cin >> ob[i][j];
        }
    }

    std::cout << ob << std::endl;

    ob.resizeRow(7);
    ob.resizeCol(13);

    for (size_t i = 0; i < ob.row(); ++i) {
        for (size_t j = 0; j < ob.col(); ++j) {
            if (ob[i][j] == "") {
                continue;
            }
            size_t z = (i + j) % 4;

            switch (z) {
                case 0: {
                    ob[i][j] = std::to_string(i * j);
                    break;
                }
                case 1: {
                    ob[i][j] = std::to_string(i + j);
                    break;
                }
                case 2: {
                    ob[i][j] = std::to_string(i * 1.2 / j);
                    break;
                }
                case 3: {
                    std::vector<int> vec;
                    for (size_t k = 0; k < i; ++k) {
                        vec.push_back(j);
                    }
                    ob[i][j] = vec;
                    break;
                }
            }
        }
    }
    
    std::cout << ob << std::endl;

    ob.resize(11, 13);

    std::cout << ob << std::endl;

    ob.mirrorH();
    ob.mirrorV();

    std::cout << ob << std::endl;

    std::initializer_list<size_t> rows = {1, 5, 7, 8, 9};
    std::initializer_list<size_t> cols = {0, 2, 3, 4, 8, 10, 12};

    SpreadSheet ob2 = ob.slice(rows, cols);

    std::cout << ob2 << std::endl;

    ob.mirrorD();
    ob2.mirrorD();

    std::cout << std::boolalpha << (ob2 == ob.slice(cols, rows)) << std::endl;

    std::vector<int> v1 = ob[8][7];
    std::vector<int> v2 = ob2[4][2];

    std::cout << std::boolalpha << v1.empty() << std::endl;
    std::cout << std::boolalpha << v2.empty() << std::endl;

    std::cout << std::boolalpha << (v1 == v2) << std::endl;

    return 0;
}
