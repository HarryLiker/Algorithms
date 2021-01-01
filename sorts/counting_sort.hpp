#pragma once
#include <vector>

void CountingSort(std::vector<int> &counts, int max) {
    int number_counts[max+1];
    for (int i = 0; i <= max; i++) {
        number_counts[i] = 0;
    }
    for (int i = 0; i < counts.size(); i++) {
        number_counts[counts[i]] += 1;
    }
    for (int i = 1; i <= max; i++) {
        number_counts[i] += number_counts[i-1];
    }
    std::vector<int> result(counts.size());
    for (int i = counts.size() - 1; i >= 0; i--) {
        number_counts[counts[i]] -= 1;
        result[number_counts[counts[i]]] = counts[i];
    }
    for (int i = 0; i < counts.size(); i++) {
        counts[i] = result[i];
    }
}