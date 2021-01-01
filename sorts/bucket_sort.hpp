#pragma once
#include <vector>
#include <algorithm>

void BucketSort(std::vector<int> &counts, int size) {
    int max = counts[0];
    int min = counts[0];
    for (int i = 0; i < size; i++) {
        if(counts[i] < min) {
            min = counts[i];
        }
        if (counts[i] > max) {
            max = counts[i];
        }
    }
    double length = (max - min);
    std::vector<std::vector<int>> buckets (size);
    for (int i = 0; i < size; ++i) {
        int bucketnum = ((counts[i] - min) / length) * size;
        if (bucketnum >= size) {
            bucketnum = size - 1;
        }
        buckets[bucketnum].push_back(counts[i]);
    }
    for (auto &bucket: buckets) {
        std::sort(bucket.begin(), bucket.end());
    }
    int index = 0;
    for (auto &bucket: buckets) {
        for (auto &value: bucket) {
            counts[index] = value;
            index++;
        }
    }
}