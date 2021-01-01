#pragma once
#include <vector>
#include <algorithm>

/*
void Bucket_sort(std::vector<int> &counts, int size) {
    for (int i = 1; i < size; i++) {
        int current_value = counts[i];
        int j = i - 1;
        while (j >= 0 && counts[j] > current_value) {
            counts[j+1] = counts[j];
            j--;
        }
        counts[j+1] = current_value;
    }
}
*/

void CreateBuckets(std::vector<int> &counts, int size) {
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