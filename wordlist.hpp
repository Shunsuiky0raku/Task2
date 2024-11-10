#ifndef WORDLIST_HPP
#define WORDLIST_HPP

#include <string>

struct WordNode {
    std::string word;
    WordNode* next;
    WordNode(const std::string& w) : word(w), next(nullptr) {}
};

class WordList {
private:
    std::string words[100];  // Array for storing up to 100 keywords
    int wordCount;

public:
    WordList() : wordCount(0) {}

    void insert(const std::string& word);
    int getSize() const;
    std::string get(int index) const;

    // New method to check if a word is contained in the list
    bool contains(const std::string& text) const;
};
#endif // WORDLIST_HPP

