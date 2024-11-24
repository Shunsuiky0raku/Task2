#ifndef WORDLIST_HPP
#define WORDLIST_HPP
#include <string>
class WordList {
private:
    std::string words[100];
    int wordCount;

public:
    WordList() : wordCount(0) {}
    void insert(const std::string& word);
    int getSize() const;
    std::string get(int index) const;
    bool contains(const std::string& text) const;
};

#endif 

