#include "wordlist.hpp"
// Insert a word into the list
void WordList::insert(const std::string& word) {
    // Only add non-empty keywords
    if (!word.empty() && wordCount < 100) {
        words[wordCount++] = word;
    }
}

// Get the size of the list
int WordList::getSize() const {
    return wordCount;
}

// Get a word at a specific index
std::string WordList::get(int index) const {
    if (index >= 0 && index < wordCount) {
        return words[index];
    }
    return "";
}

// Check if a word is contained in the list
bool WordList::contains(const std::string& text) const {
    for (int i = 0; i < wordCount; i++) {
        if (words[i] == text) {
            return true;
        }
    }
    return false;
}
