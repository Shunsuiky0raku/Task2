#include <iostream>
#include <fstream>
#include <sstream>
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

    // Insert a word into the list
    void insert(const std::string& word) {
        WordNode* newNode = new WordNode(word);
        newNode->next = head;
        head = newNode;
    }

    // Check if a word exists in the list
    bool contains(const std::string& text) const {
        WordNode* current = head;
        while (current != nullptr) {
            if (text.find(current->word) != std::string::npos) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    ~WordList() {
        while (head != nullptr) {
            WordNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

struct Email {
    int id;
    std::string sender;
    std::string subject;
    std::string body;
    std::string date;
    Email* next;

    Email(int i, const std::string& s, const std::string& sub, const std::string& b, const std::string& d)
        : id(i), sender(s), subject(sub), body(b), date(d), next(nullptr) {}
};

class EmailList {
private:
    Email* highPriorityHead;
    Email* mediumPriorityHead;
    Email* lowPriorityHead;
    WordList highPriorityWords;
    WordList mediumPriorityWords;
    WordList lowPriorityWords;

public:
    EmailList() : highPriorityHead(nullptr), mediumPriorityHead(nullptr), lowPriorityHead(nullptr) {}

    // Load priority words from text file into respective lists
    void loadPriorityWords(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Could not open priority words file!" << std::endl;
            return;
        }

        std::string line;
        WordList* currentList = nullptr;

        while (std::getline(file, line)) {
            if (line == "# High Priority") {
                currentList = &highPriorityWords;
            }
            else if (line == "# Medium Priority") {
                currentList = &mediumPriorityWords;
            }
            else if (line == "# Low Priority") {
                currentList = &lowPriorityWords;
            }
            else if (!line.empty() && currentList != nullptr) {
                currentList->insert(line);
            }
        }
        file.close();
    }

    // Check for priority level based on words in subject or body
    int determinePriority(const std::string& text) {
        if (highPriorityWords.contains(text)) {
            return 1; // High priority
        }
        if (mediumPriorityWords.contains(text)) {
            return 2; // Medium priority
        }
        if (lowPriorityWords.contains(text)) {
            return 3; // Low priority
        }
        return 3; // Default to low priority if no matches
    }

    // Helper function to check if a string is numeric
    bool isNumeric(const std::string& str) {
        for (char const& c : str) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }

    void insertEmail(int id, const std::string& sender, const std::string& subject,
        const std::string& body, int priority, const std::string& date) {
        Email* newEmail = new Email(id, sender, subject, body, date);

        if (priority == 1) {
            newEmail->next = highPriorityHead;
            highPriorityHead = newEmail;
        }
        else if (priority == 2) {
            newEmail->next = mediumPriorityHead;
            mediumPriorityHead = newEmail;
        }
        else {
            newEmail->next = lowPriorityHead;
            lowPriorityHead = newEmail;
        }
    }

    void loadFromCSV(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Could not open the CSV file!" << std::endl;
            return;
        }

        std::string line, word;
        bool isHeader = true;  // Flag to skip the header row

        while (std::getline(file, line)) {
            std::stringstream s(line);

            if (isHeader) {  // Skip the header row
                isHeader = false;
                continue;
            }

            int id = 0;
            std::string sender, subject, body, date;
            int priority = 3; // Default to low priority

            // Parse ID safely
            std::getline(s, word, ',');
            if (isNumeric(word)) {
                try {
                    id = std::stoi(word);  // Parse ID if valid
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid ID found, skipping this line: " << line << std::endl;
                    continue;  // Skip to the next line if ID is invalid
                }
            }
            else {
                std::cerr << "Non-numeric ID found, skipping this line: " << line << std::endl;
                continue;  // Skip to the next line if ID is not numeric
            }

            std::getline(s, sender, ',');  // Parse Sender
            std::getline(s, word, ',');  // Skip Recipient
            std::getline(s, subject, ',');  // Parse Subject
            std::getline(s, body, ',');  // Parse Body
            std::getline(s, date, ',');  // Parse Date
            std::getline(s, word, ',');  // Skip Category

            // Determine priority based on keywords in subject or body
            priority = determinePriority(subject + " " + body);

            insertEmail(id, sender, subject, body, priority, date);
        }
        file.close();
    }

    void displayEmails() const {
        std::cout << "Email Management System:\n";
        std::cout << "1. View Inbox Emails\n";
        std::cout << "2. View Outbox Emails\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        std::cout << "\nHigh-Priority Emails:\n";
        displayList(highPriorityHead);
        std::cout << "\nMedium-Priority Emails:\n";
        displayList(mediumPriorityHead);
        std::cout << "\nLow-Priority Emails:\n";
        displayList(lowPriorityHead);
    }

    void displayList(Email* head) const {
        Email* current = head;
        while (current != nullptr) {
            std::cout << "ID: " << current->id << "\n";
            std::cout << "From: " << current->sender << "\n";
            std::cout << "Subject: " << current->subject << "\n";
            std::cout << "Date: " << current->date << "\n\n";
            current = current->next;
        }
    }

    ~EmailList() {
        deleteList(highPriorityHead);
        deleteList(mediumPriorityHead);
        deleteList(lowPriorityHead);
    }

    void deleteList(Email* head) {
        while (head != nullptr) {
            Email* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    EmailList emailList;

    // Load priority words from text file
    emailList.loadPriorityWords("C:\\Users\\User\\Desktop\\priority_words.txt");

    // Load emails from CSV file
    emailList.loadFromCSV("C:\\Users\\User\\Desktop\\email.csv");

    // Display sorted emails by priority level
    emailList.displayEmails();

    return 0;
}
