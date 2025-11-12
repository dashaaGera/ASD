#include <gtest/gtest.h>
#include "../lib_algorithms_for_DSU/algorithms_for_DSU.h"
TEST(TestCountIslands, count_islands_work_correctly_in_array_of_zeros) {
    int n = 3;
    int** arr = new int* [n];
    for (int i=0; i < n; i++) {
        arr[i] = new int[n];
        for (int j=0; j < n; j++) {
            arr[i][j] = 0;
        }
    }
    EXPECT_EQ(count_islands(arr, n,n), 0);

    for (int i = 0; i < n; i++) 
        delete[] arr[i];
    delete[] arr;
}

TEST(TestCountIslands, count_islands_work_correctly_in_array_of_ones) {
    int n = 3;
    int** arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            arr[i][j] = 1;
        }
    }
    EXPECT_EQ(count_islands(arr, n,n), 1);

    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}

TEST(TestCountIslands, count_islands_work_correctly_in_any_array) {
    int m = 5;
    int n = 7;
    int** arr = new int* [n];

    arr[0] = new int[n] {1, 1, 0, 0, 0, 1, 1};
    arr[1] = new int[n] {1, 0, 0, 0, 0, 1, 0};
    arr[2] = new int[n] {0, 1, 1, 0, 1, 0, 0};
    arr[3] = new int[n] {0, 0, 1, 1, 0, 0, 0};
    arr[4] = new int[n] {0, 0, 1, 0, 0, 0, 1};


    EXPECT_EQ(count_islands(arr, m,n), 5);

    for (int i = 0; i < m; i++) delete[] arr[i];
    delete[] arr;
}