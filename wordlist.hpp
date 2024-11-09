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
    WordNode* head;
public:
    WordList() : head(nullptr) {}
    void insert(const std::string& word);
    bool contains(const std::string& text) const;
    ~WordList();
};

#endif // WORDLIST_HPP

