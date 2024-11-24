#ifndef EMAILLIST_HPP
#define EMAILLIST_HPP

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
    void searchEmails(const std::string& keyword) const;
    void displayPriorityEmails();
    void displayInbox();
    void displayOutbox();
    void displaySpamEmails();
    void displayStack(const std::string& title, EmailStack& stack);
    void displayQueue(const std::string& title, EmailQueue& queue);
    int determineSpamLevel(const std::string& text);

    // Newly Added Declarations
    void insertEmail(int id, const std::string& sender, const std::string& subject,
                     const std::string& body, int priority, const std::string& date);
    void displayList(const std::string& title, Email* head) const;

    ~EmailList() {
        deleteList(highPriorityHead);
        deleteList(mediumPriorityHead);
        deleteList(lowPriorityHead);
    }

private:
    void deleteList(Email* head);
};

#endif // EMAILLIST_HPP

