#include <array>
#include <iostream>
#include <random>
#include <cstdint>

#include "Header.hpp"

void displayList(const int a[], const int size)
{
    int i = 0;

    for (i = 0; i < size; ++i) {
        std::cout << a[i] << std::endl;
    }
}

int maximum(const int a[], const int size)
{
    int maxVal = 0;
    int maxIdx = 0;
    int i = 0;

    for (i = 0; i < size; ++i) {
        if (a[i] > maxVal)
        {
            maxVal = a[i];
            maxIdx = i;
        }

    }
    return maxIdx;
}

void swapValue(int a[], const int idx0, const int idx1)
{
    int temp = a[idx0];

    a[idx0] = a[idx1];
    a[idx1] = temp;
}

void bubbleSort(int a[], int size)
{
    int i = 0;
    int maxIdx = 0;

    for (i = 0; i < size; ++i) {

        maxIdx = maximum(a, size - i);
        swapValue(a, maxIdx, size - i - 1);
    }
}
