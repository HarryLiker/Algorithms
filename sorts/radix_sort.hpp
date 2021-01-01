#pragma once
#include <vector>

void CountingSortForRadix(std::vector<unsigned long long> &counts, unsigned long long size, int position) {
    int byte; // Значение байта в числе
    int bits; // Количество бит, на которое нужно сделать сдвиг
    unsigned int bytes_vector [256];
    for (int i = 0; i < 256; i++) {
        bytes_vector[i] = 0;
    }
    unsigned long long concatenation; // Число, с которым происходит конкатенация
    std::vector<unsigned long long> sorting_vector(size);
    for (unsigned long long i = 0; i < size; i++) {
        switch (position) {
        case 1:
            concatenation = 0x00000000000000FF;
            bits = 0;
            break;
        case 2:
            concatenation = 0x000000000000FF00;
            bits = 8;
            break;
        case 3:
            concatenation = 0x0000000000FF0000;
            bits = 16;
            break;
        case 4:
            concatenation = 0x00000000FF000000;
            bits = 24;
            break;
        case 5:
            concatenation = 0x000000FF00000000;
            bits = 32;
            break;
        case 6:
            concatenation = 0x0000FF0000000000;
            bits = 40;
            break;
        case 7:
            concatenation = 0x00FF000000000000;
            bits = 48;
            break;
        case 8:
            concatenation = 0xFF00000000000000;
            bits = 56;
            break;
        default:
            break;
        }
        byte = ((counts[i] & concatenation) >> bits);
        bytes_vector[byte] += 1;
        sorting_vector[i] = counts[i];
    }
    for (int i = 1; i < 256; i++) {
        bytes_vector[i] = bytes_vector[i] + bytes_vector[i-1];
    }
    for (long long i = size-1; i >=0; i--) {
        int k = ((counts[i] & concatenation) >> bits);
        bytes_vector[k] -= 1;
        sorting_vector[bytes_vector[k]] = counts[i];
    }
    for (unsigned long long i = 0; i < size; i++) {
        counts[i] = sorting_vector[i];
    }
}

void RadixSort(std::vector<unsigned long long> &counts, unsigned long long size) {
    for (int position = 1; position < 9; position++) {
        CountingSortForRadix(counts, size, position);
    }
}