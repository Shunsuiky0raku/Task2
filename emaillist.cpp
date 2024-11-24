#include "emaillist.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
void EmailList::loadPriorityWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open priority words file!\n";
        return;
    }

    std::string line;
    WordList* currentList = nullptr;

    while (std::getline(file, line)) {
        line.erase(line.find_last_not_of("\r\n") + 1); // Remove newlines
        if (line == "# High Priority") {
            currentList = &highPriorityWords;
            std::cout << "[DEBUG] Loading High Priority Words.\n";
        } else if (line == "# Medium Priority") {
            currentList = &mediumPriorityWords;
            std::cout << "[DEBUG] Loading Medium Priority Words.\n";
        } else if (line == "# Low Priority") {
            currentList = &lowPriorityWords;
            std::cout << "[DEBUG] Loading Low Priority Words.\n";
        } else if (!line.empty() && currentList != nullptr) {
            currentList->insert(line.c_str());
            std::cout << "[DEBUG] Inserted word: " << line << "\n";
        }
    }

    file.close();
}

// Helper function to split a string by spaces 
void splitWords(const std::string& str, std::string words[], int& wordCount) {
    wordCount = 0;
    std::string currentWord;

    for (char c : str) {
        if (c == ' ') {
            if (!currentWord.empty()) {
                words[wordCount++] = currentWord;
                currentWord.clear();
            }
        } else {
            currentWord += (c >= 'A' && c <= 'Z') ? c + 32 : c; // Convert to lowercase
        }
    }
    if (!currentWord.empty()) {
        words[wordCount++] = currentWord;
    }

    std::cout << "[DEBUG] Split into words: ";
    for (int i = 0; i < wordCount; ++i) {
        std::cout << words[i] << " ";
    }
    std::cout << "\n";
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
            std::cout << "Loaded spam keyword: " << line << std::endl;  
        }
    }
}
void EmailList::insertSpamEmail(const Email& email) {
    spamEmails.push(email); // Assuming spamEmails is a stack or queue
    std::cout << "[DEBUG] Inserted spam email: " << email.sender << ", " << email.subject << "\n";
}

int EmailList::determinePriority(const std::string& text) {
    std::string words[100]; // Array to hold words
    int wordCount = 0;

    splitWords(text, words, wordCount);

    std::cout << "\n[DEBUG] Checking priority for text: " << text << "\n";

    for (int i = 0; i < wordCount; ++i) {
        std::cout << "[DEBUG] Checking word: " << words[i] << "\n";

        if (highPriorityWords.contains(words[i].c_str())) {
            std::cout << "[DEBUG] Matched High Priority: " << words[i] << "\n";
            return 1; // High priority
        }
        if (mediumPriorityWords.contains(words[i].c_str())) {
            std::cout << "[DEBUG] Matched Medium Priority: " << words[i] << "\n";
            return 2; // Medium priority
        }
        if (lowPriorityWords.contains(words[i].c_str())) {
            std::cout << "[DEBUG] Matched Low Priority: " << words[i] << "\n";
            return 3; // Low priority
        }
    }

    std::cout << "[DEBUG] Defaulting to Low Priority.\n";
    return 3; // Default to low priority
}


std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c >= 'A' && c <= 'Z') {
            result += c + 32;
        } else {
            result += c;
        }
    }
    return result;
}
// Hardcoded spam phrases with different levels of "spamminess"
std::string highSpamWords[] = {"urgent", "action" ,"required", "free gift", "claim your reward", "limited time offer"};
std::string mediumSpamWords[] = {"exclusive", "discount", "special", "offer", "promotion", "cash", "prize"};
std::string lowSpamWords[] = {"team", "building", "event", "invitation", "sale", "social", "event"};

bool EmailList::isSpam(const Email& email) {
    std::string combinedText = email.subject + " " + email.body;
    int spamScore = 0;

    for (const auto& word : highSpamWords) {
        if (combinedText.find(word) != std::string::npos) {
            spamScore += 3;
        }
    }

    for (const auto& word : mediumSpamWords) {
        if (combinedText.find(word) != std::string::npos) {
            spamScore += 2;
        }
    }

    for (const auto& word : lowSpamWords) {
        if (combinedText.find(word) != std::string::npos) {
            spamScore += 1;
        }
    }

    if (spamScore >= 3) {
        // Check if the email is already in the spam stack
        EmailStack tempStack;
        bool isDuplicate = false;

        while (!spamEmails.isEmpty()) {
            Email existingEmail = spamEmails.pop();
            if (existingEmail.sender == email.sender &&
                existingEmail.subject == email.subject &&
                existingEmail.body == email.body &&
                existingEmail.date == email.date) {
                isDuplicate = true;
            }
            tempStack.push(existingEmail);
        }

        // Restore emails back to the spam stack
        while (!tempStack.isEmpty()) {
            spamEmails.push(tempStack.pop());
        }

        // If not duplicate, add to the spam stack
        if (!isDuplicate) {
            spamEmails.push(email);
        }

        return true;
    }

    return false;
}
void EmailList::deduplicateSpamEmails() {
    EmailStack uniqueStack;
    const int MAX_EMAILS = 1000; // Adjust based on your requirements
    std::string seen[MAX_EMAILS];
    int seenCount = 0;

    while (!spamEmails.isEmpty()) {
        Email email = spamEmails.pop();
        std::string identifier = email.sender + email.subject + email.body + email.date;

        // Check if identifier is already in the seen array
        bool isDuplicate = false;
        for (int i = 0; i < seenCount; ++i) {
            if (seen[i] == identifier) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            uniqueStack.push(email);
            seen[seenCount++] = identifier; // Add to seen array
        }
    }

    // Restore unique emails to the original stack
    while (!uniqueStack.isEmpty()) {
        spamEmails.push(uniqueStack.pop());
    }
}

void EmailList::searchEmails(const std::string& keyword) const {
    bool found = false;
    int count = 0;

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
            continue;  
        }
        
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
    deduplicateSpamEmails(); // Ensure no duplicates

    EmailStack tempStack;
    while (!spamEmails.isEmpty()) {
        Email email = spamEmails.pop();
        tempStack.push(email);

        std::cout << "Sender: " << email.sender << ", Subject: " << email.subject
                  << "Body: " << email.body << ", Date: " << email.date << "\n";
    }

    // Restore spam emails back to the stack
    while (!tempStack.isEmpty()) {
        spamEmails.push(tempStack.pop());
    }
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
