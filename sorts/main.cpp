#include <iostream>
#include <vector>
#include "counting_sort.hpp"
#include "radix_sort.hpp"
#include "bucket_sort.hpp"

using namespace std;

int main() {
    std::vector<int> counts;
    int number;
    while (std::cin >> number) {
        counts.push_back(number);
    }
    int max = -1;
    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > max) {
            max = counts[i];
        }
    }
    // CountingSort(counts, max);
    // RadixSort(counts, counts.size());  
    BucketSort(counts, counts.size());
    for (int i = 0; i < counts.size(); i++) {
        std::cout << counts[i] << " ";
    }
}
