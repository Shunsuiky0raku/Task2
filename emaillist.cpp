#include "emaillist.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
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
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] != '#') {  // Skip comments and empty lines
            spamKeywords.insert(line);
            std::cout << "Loaded spam keyword: " << line << std::endl;  // Debug output
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
    
    // Extract only the domain from the sender's email
    size_t atPos = email.sender.find('@');
    std::string senderDomain = (atPos != std::string::npos) ? email.sender.substr(atPos + 1) : "";

    // Check if the sender's domain is in the suspicious domains
    if (suspiciousDomains.contains(senderDomain)) {
        std::cout << "Spam detected based on suspicious domain: " << email.sender << std::endl;
        return true;
    }

    // Check if the combined subject and body contain any spam keywords
    if (spamKeywords.contains(combinedText)) {
        std::cout << "Spam detected based on keyword in content: " << combinedText << std::endl;
        return true;
    }

    return false;
}
void EmailList::searchEmails(const std::string& keyword) const {
    bool found = false;
    int count = 0;

    // Search in inbox
    Email* inboxEmails = inbox.getEmails(count);
    for (int i = 0; i < count; i++) {
        if (inboxEmails[i].emailID.find(keyword) != std::string::npos ||
            inboxEmails[i].sender.find(keyword) != std::string::npos ||
            inboxEmails[i].recipient.find(keyword) != std::string::npos ||
            inboxEmails[i].subject.find(keyword) != std::string::npos ||
            inboxEmails[i].body.find(keyword) != std::string::npos ||
            inboxEmails[i].date.find(keyword) != std::string::npos ||
            inboxEmails[i].category.find(keyword) != std::string::npos) {

            std::cout << "Email ID: " << inboxEmails[i].emailID << "\n"
                      << "Sender: " << inboxEmails[i].sender << "\n"
                      << "Recipient: " << inboxEmails[i].recipient << "\n"
                      << "Subject: " << inboxEmails[i].subject << "\n"
                      << "Body: " << inboxEmails[i].body << "\n"
                      << "Date: " << inboxEmails[i].date << "\n"
                      << "Category: " << inboxEmails[i].category << "\n"
                      << "-----------------------------------\n";
            found = true;
        }
    }
    delete[] inboxEmails;

    if (!found) {
        std::cout << "No emails found for the keyword: " << keyword << "\n";
    }
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

        if (isSpam(email)) {
            std::cout << "Email marked as spam: " << email.subject << std::endl;
            spamEmails.push(email);
            continue;  // Skip further processing for spam emails
        }
        // Sort emails into inbox, outbox, or priority stacks
        if (email.recipient == "john.smith@example.com") inbox.push(email);
        else if (email.sender == "john.smith@example.com") outbox.enqueue(email);
        
        int priority = determinePriority(email.subject + " " + email.body);
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
