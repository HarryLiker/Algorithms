#include <iostream>
#include <string>
#include <sstream>
#include "ZBlocks.hpp"

int main() {
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