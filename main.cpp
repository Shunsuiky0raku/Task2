#include "emailstack.hpp"
#include "emailqueue.hpp"
#include "email.hpp"  // Ensure this is included to use the Email class
#include <iostream>
#include <fstream>
#include <sstream>
//DEefined target email for categorization
const std::string TARGET_EMAIL = "john.smith@example.com";
// Function to load emails from CSV with filtering based on category
void loadEmailsFromCSV(const std::string& filename, EmailStack& inbox, EmailQueue& outbox) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string emailID, sender, recipient, subject, body, date, category;

        // Read each field from the CSV line
        std::getline(ss, emailID, ',');
        std::getline(ss, sender, ',');
        std::getline(ss, recipient, ',');
        std::getline(ss, subject, ',');
        std::getline(ss, body, ',');
        std::getline(ss, date, ',');
        std::getline(ss, category, ',');

        // Only process emails with category "inbox" or "outbox"
        if (recipient == TARGET_EMAIL) {
            inbox.push(Email(emailID, sender, recipient, subject, body, date, category));
        } else if (sender == TARGET_EMAIL ) {
            outbox.enqueue(Email(emailID, sender, recipient, subject, body, date, category));
        }
    }

    file.close();
}

// Function to display emails in the inbox
void displayInbox(EmailStack& inbox) {
    if (inbox.isEmpty()) {
        std::cout << "Inbox is empty.\n";
        return;
    }

    std::cout << "Inbox Emails:\n";
    while (!inbox.isEmpty()) {
        Email email = inbox.pop();
        std::cout << "ID: " << email.emailID << "\n"
                  << "From: " << email.sender << "\n"
                  << "Subject: " << email.subject << "\n"
                  << "Date: " << email.date << "\n\n";
    }
}

// Function to display emails in the outbox
void displayOutbox(EmailQueue& outbox) {
    if (outbox.isEmpty()) {
        std::cout << "Outbox is empty.\n";
        return;
    }

    std::cout << "Outbox Emails:\n";
    while (!outbox.isEmpty()) {
        Email email = outbox.dequeue();
        std::cout << "ID: " << email.emailID << "\n"
                  << "To: " << email.recipient << "\n"
                  << "Subject: " << email.subject << "\n"
                  << "Date: " << email.date << "\n\n";
    }
}

int main() {
    EmailStack inbox;
    EmailQueue outbox;

    // Load emails from CSV file
    loadEmailsFromCSV("email.csv", inbox, outbox);

    int choice;
    do {
        std::cout << "Email Management System:\n";
        std::cout << "1. View Inbox Emails\n";
        std::cout << "2. View Outbox Emails\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayInbox(inbox);
                break;
            case 2:
                displayOutbox(outbox);
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        std::cout << std::endl;
    } while (choice != 3);

    return 0;
}

