#pragma once

#include <string>
#include <vector>
#include "TWord.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

std::vector<unsigned long long> ZFunction(const std::vector<TWord> &text) {
    unsigned long long left = 0;
    unsigned long long right = 0;
    std::vector<unsigned long long> z_function(text.size());
    for (unsigned long long i = 1; i < text.size(); i++) {
        if (i <= right) {
            z_function[i] = std::min(z_function[i-left], right - i + 1);
        }
        while ((z_function[i] + i < text.size()) && (text[z_function[i]].Word == text[z_function[i] + i].Word)) {
            ++z_function[i];
        }
        if (i + z_function[i] - 1 > right) {
            left = i;
            right = z_function[i] + i - 1;
        }
    }
    return z_function;
}

void z_blocks_search() {
    std::vector<TWord> text;
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
            text.push_back(current_word);
            if (line_number == 0) {
                pattern_size++;
            }
            word_number++;
        }
        if (line_number == 0) {
            std::string sentinel = "$";
            TWord current_word(sentinel, word_number, line_number);
            text.push_back(current_word);
        }
        line_number++;
        word_number = 1;
    }
    std::vector<unsigned long long> result = ZFunction(text);
    for (unsigned long long i = pattern_size + 1; i < result.size(); i++) {
        if (result[i] == pattern_size) {
            std::cout << text[i].StringId << ", " << text[i].WordId << "\n";
        }
    }
}