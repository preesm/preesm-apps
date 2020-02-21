/*
 ============================================================================
 Name        : medianFilter.h
 Author      : kdesnos
 Version     : 1.0
 Copyright   : CeCILL-C, IETR, INSA Rennes
 Description : Application of a 3x3 median filter to an image.
 ============================================================================
 */

#include "medianFilter.h"
#include <algorithm>

template <class T>
static T min(T x, T y) {
    return x < y ? x : y;
}

template <class T>
static T max(T x, T y) {
    return x < y ? y : x;
}

void quickSortPartition(int startIdx, int endIdx, int *pivotIdx,
                        unsigned char *values) {
    auto swapIdx = startIdx;
    std::swap((*(values + (*pivotIdx))), (*(values + endIdx)));
    for (auto idx = startIdx; idx < endIdx; idx++) {
        if (values[idx] <= values[endIdx]) {
            std::swap((*(values + swapIdx)), (*(values + idx)));
            swapIdx++;
        }
    }
    std::swap((*(values + swapIdx)), (*(values + endIdx)));
    (*pivotIdx) = swapIdx;
}

void quickSort(int startIdx, int endIdx, unsigned char *values) {
    if (startIdx < endIdx) {
        auto pivotIdx = startIdx;
        quickSortPartition(startIdx, endIdx, &pivotIdx, values);
        quickSort(startIdx, pivotIdx - 1, values);
        quickSort(pivotIdx + 1, endIdx, values);
    }
}

void medianFilter(int height, int width, unsigned char *rawDisparity, unsigned char *filteredDisparity) {
    // Process pixels one by one
    for (auto j = 1; j < height - 1; ++j) {
        for (auto i = 0; i < width; ++i) {
            unsigned char pixels[9];
            // output pixel is the median of a 3x3 window
            // Get the 9 pixels
            for (auto l = -1; l <= 1; ++l) {
                const auto y = min(max(j + l, 0), height - 1);
                for (auto k = -1; k <= 1; ++k) {
                    const auto x = min(max(i + k, 0), width - 1);
                    pixels[(l + 1) * 3 + k + 1] = rawDisparity[y * width + x];
                }
            }
            // Sort the 9 values
            quickSort(0, 8, pixels);
            filteredDisparity[(j - 1) * width + i] = pixels[9 / 2];
        }

    }
}
