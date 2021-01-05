#pragma once

#include <vector> 

#include "TWord.hpp"
#include <iostream>
#include <sstream>

std::vector<unsigned long long> PrefixFunction(const std::vector<TWord> &text) {
    std::vector<unsigned long long> prefix_vector(text.size());
    for (unsigned long long i = 1; i < text.size(); i++) {
        prefix_vector[i] = prefix_vector[i-1];
        while (prefix_vector[i] > 0 && text[i] != text[prefix_vector[i]]) {
            prefix_vector[i] = prefix_vector[prefix_vector[i]-1];
        }
        if (text[i] == text[prefix_vector[i]]) {
            ++prefix_vector[i];
        }
    }
    return prefix_vector;
}

std::vector<unsigned long long> KMP(const std::vector<TWord> &pattern, const std::vector<TWord> &text) {
    std::vector<unsigned long long> pattern_prefix_function = PrefixFunction(pattern);
    unsigned long long pattern_size = pattern.size();
    unsigned long long text_size = text.size();
    unsigned long long i = 0;
    std::vector<unsigned long long> result;
    if (pattern_size > text_size) {
        return result;
    }
    while (i < text_size - pattern_size + 1 ) {
        unsigned long long j = 0;
        while (j < pattern_size && pattern[j] == text[i+j]) {
            ++j;
        }
        if (j == pattern_size) {
            result.push_back(i);
        } else {
            if (j > 0 && j > pattern_prefix_function[j-1]) {
                i = i + j - pattern_prefix_function[j -1] - 1;
            }
        }
        ++i;
    }
    return result;
}

void kmp_search() {
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
    std::vector<unsigned long long> result = KMP(pattern, text);
    for (unsigned long long i = 0; i < result.size(); i++) {
        std::cout << text[result[i]].StringId << ", " << text[result[i]].WordId << "\n";
    }
}