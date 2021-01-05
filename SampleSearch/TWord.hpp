#pragma once
#include <string>

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