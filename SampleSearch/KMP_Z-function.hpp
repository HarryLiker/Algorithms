#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include "TWord.hpp"
#include "ZBlocks.hpp"

std::vector<unsigned long long> StrongPrefix(const std::vector<TWord> &pattern) {
    std::vector<unsigned long long> pattern_z_function = ZFunction(pattern);
    unsigned long long pattern_size = pattern.size();
    std::vector<unsigned long long> result(pattern_size);
    for (unsigned long long i = pattern_size - 1; i > 0; i--) {
        result[i+pattern_z_function[i]-1] = pattern_z_function[i];
    }
    return result;
}

std::vector<unsigned long long> KMPByZFunction(const std::vector<TWord> &pattern, const std::vector<TWord> &text) {
    std::vector<unsigned long long> pattern_prefix_function = StrongPrefix(pattern);
    std::vector<unsigned long long> result;
    unsigned long long pattern_size = pattern.size();
    unsigned long long text_size = text.size();
    unsigned long long i = 0;
    if (pattern.size() > text.size()) {
        return result;
    }
    while (i < text_size - pattern_size + 1) {
        unsigned long long j = 0;
        while (j < pattern_size && pattern[j] == text[i+j]) {
            ++j;
        }
        if (j == pattern_size) {
            result.push_back(i);
        } else {
            if (j > 0 && j > pattern_prefix_function[j-1]) {
                i = i + j - pattern_prefix_function[j-1] - 1;
            }
        }
        ++i;
    }
    return result;
}

void kmp_z_search() {
    std::vector<TWord> text;
    std::vector<TWord> pattern;
    unsigned long long pattern_size = 0;
    unsigned long long line_number = 0;
    unsigned long long word_number = 1;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::string word;
        std::stringstream temp_string(input);
        while (temp_string >> word) {
            WordToLower(word);
            TWord current_word(word, word_number, line_number);
            if (line_number == 0) {
                pattern.push_back(current_word);
                pattern_size++;
            } else {
                text.push_back(current_word);
            }
            word_number++;
        }
        line_number++;
        word_number = 1;
    }
    std::vector<unsigned long long> result = KMPByZFunction(pattern, text);
    for (unsigned long long i = 0; i < result.size(); i++) {
        std::cout << text[result[i]].StringId << ", " << text[result[i]].WordId << "\n";
    }
}