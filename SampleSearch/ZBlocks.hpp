#pragma once

#include <string>
#include <vector>

struct TWord {
    std::string Word;
    unsigned long long WordId;
    unsigned long long StringId;
    TWord(std::string word): Word(word), WordId(0), StringId(0) {}
    TWord(std::string word, unsigned long long word_id, unsigned long long string_id): Word(word), WordId(word_id), StringId(string_id) {}
    TWord(): Word(""), WordId(0), StringId(0) {}  
};

void WordToLower(std::string &word) {
    for (size_t i = 0; i < word.size(); i++) {
        word[i] = std::tolower(word[i]);
    }
}

bool operator == (const TWord &left_value, const TWord &right_value) {
    if (left_value.Word == right_value.Word) {
        return true;
    }
    return false;
}

bool operator != (const TWord &left_value, const TWord &right_value) {
    return !(left_value == right_value);
}

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