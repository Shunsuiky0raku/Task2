#include "emaillist.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
void EmailList::loadPriorityWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open priority words file!" << std::endl;
        return;
    }

    std::string line;
    WordList* currentList = nullptr;

    while (std::getline(file, line)) {
        if (line == "# High Priority") currentList = &highPriorityWords;
        else if (line == "# Medium Priority") currentList = &mediumPriorityWords;
        else if (line == "# Low Priority") currentList = &lowPriorityWords;
        else if (!line.empty() && currentList) currentList->insert(line);
    }
}

void EmailList::loadSpamWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open spam words file!" << std::endl;
        return;
    }

    std::string line;
    WordList* currentList = nullptr;

    while (std::getline(file, line)) {
      if (line == "# Keywords") currentList = &spamKeywords;
      else if (line == "# Urgent Phrases") currentList = &urgentPhrases;
       else if (line == "# Special Characters") currentList = &specialCharacters;
        else if (line == "# Suspicious Domains") currentList = &suspiciousDomains;
        else if (!line.empty() && currentList) {
            currentList->insert(line);
        }
    }
}

int EmailList::determinePriority(const std::string& text) {
    if (highPriorityWords.contains(text)) return 1;
    if (mediumPriorityWords.contains(text)) return 2;
    if (lowPriorityWords.contains(text)) return 3;
    return 3;
}

bool EmailList::isSpam(const Email& email) {
    std::string combinedText = email.subject + " " + email.body;
    
    // Check if the sender is from a suspicious domain
    if (suspiciousDomains.contains(email.sender)) {
        return true;
    }
    
    // Check for keywords, urgent phrases, or special characters in the subject and body
    if (spamKeywords.contains(combinedText) || urgentPhrases.contains(combinedText) || specialCharacters.contains(combinedText)) {
        return true;
    }

    return false;
}
void EmailList::loadEmailsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Email email;
        std::getline(ss, email.emailID, ',');
        std::getline(ss, email.sender, ',');
        std::getline(ss, email.recipient, ',');
        std::getline(ss, email.subject, ',');
        std::getline(ss, email.body, ',');
        std::getline(ss, email.date, ',');
        std::getline(ss, email.category, ',');

        int priority = determinePriority(email.subject + " " + email.body);

        // Check if email is spam
        if (isSpam(email)) {
            spamEmails.push(email);
            continue;
        }

        // Sort emails into inbox, outbox, or priority stacks
        if (email.recipient == "john.smith@example.com") inbox.push(email);
        else if (email.sender == "john.smith@example.com") outbox.enqueue(email);

        if (priority == 1) highPriority.push(email);
        else if (priority == 2) mediumPriority.push(email);
        else lowPriority.push(email);
    }
}

void EmailList::displayPriorityEmails() {
    displayStack("High Priority Emails", highPriority);
    displayStack("Medium Priority Emails", mediumPriority);
    displayStack("Low Priority Emails", lowPriority);
}

void EmailList::displaySpamEmails() {
    displayStack("Spam Emails", spamEmails);
}

void EmailList::displayInbox() { displayStack("Inbox", inbox); }
void EmailList::displayOutbox() { displayQueue("Outbox", outbox); }

void EmailList::displayStack(const std::string& title, EmailStack& stack) {
    std::cout << "\n" << title << ":\n";
    while (!stack.isEmpty()) {
        Email email = stack.pop();
        std::cout << "Sender: " << email.sender << ", Subject: " << email.subject << "Body: " << email.body << ", Date: " << email.date << "\n";
    }
}

void EmailList::displayQueue(const std::string& title, EmailQueue& queue) {
    std::cout << "\n" << title << ":\n";
    while (!queue.isEmpty()) {
        Email email = queue.dequeue();
        std::cout << "Recipient: " << email.recipient << ", Subject: " << email.subject << "Body: " << email.body << ", Date: " << email.date << "\n";
    }
}
