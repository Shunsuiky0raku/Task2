#include "wordlist.hpp"

// Insert a word into the list
void WordList::insert(const std::string& word) {
    WordNode* newNode = new WordNode(word);
    newNode->next = head;
    head = newNode;
}

// Check if a word exists in the list
bool WordList::contains(const std::string& text) const {
    WordNode* current = head;
    while (current) {
        if (text.find(current->word) != std::string::npos) return true;
        current = current->next;
    }
    return false;
}

// Destructor to free memory
WordList::~WordList() {
    while (head) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

