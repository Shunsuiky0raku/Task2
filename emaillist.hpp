#ifndef emaillist_hpp
#define emaillist_hpp
#include "emailstack.hpp"
#include "emailqueue.hpp"
#include "wordlist.hpp"
#include <string>

class EmailList {
private:
    EmailStack inbox, highPriority, mediumPriority, lowPriority, spamEmails;
    EmailQueue outbox;
    WordList highPriorityWords, mediumPriorityWords, lowPriorityWords, spamWords;
    WordList spamKeywords;
    WordList urgentPhrases;
    WordList specialCharacters;
    WordList suspiciousDomains;
public:
    void loadPriorityWords(const std::string& filePath);
    void loadSpamWords(const std::string& filePath); 
    int determinePriority(const std::string& text);
    bool isSpam(const Email& email);  
    void loadEmailsFromCSV(const std::string& filename);
    void displayPriorityEmails();
    void displayInbox();
    void displayOutbox();
    void displaySpamEmails(); 
    // Add display helper methods
    void displayStack(const std::string& title, EmailStack& stack);
    void displayQueue(const std::string& title, EmailQueue& queue);
};

#endif //emaillist_hpp
