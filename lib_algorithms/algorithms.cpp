#include "../lib_algorithms/algorithms.h"

int count_islands(int** arr, size_t rows,size_t cols) {
    DSU dsu(rows * cols);
    int count_islands = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 1) {
                count_islands++;
                int current = i * cols + j;
                //right
                if (j + 1 < cols && arr[i][j + 1] == 1) {
                    int right = i * cols + (j + 1);
                    if (dsu.find(current) != dsu.find(right)) {
                        dsu.unite(current, right);
                        count_islands--;
                    }
                }

                //lower
                if (i + 1 < rows && arr[i + 1][j] == 1) {
                    int lower= (i + 1) * cols + j;
                    if (dsu.find(current) != dsu.find(lower)) {
                        dsu.unite(current, lower);
                        count_islands--;
                    }
                }
            }
        }
    }

    return count_islands;
}