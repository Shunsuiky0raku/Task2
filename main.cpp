#include "emaillist.hpp"
#include <iostream>

int main() {
    EmailList emailList;

    emailList.loadPriorityWords("priority_words.txt");
  //    emailList.loadSpamWords("SpamIndicator.txt");
    emailList.loadEmailsFromCSV("email.csv");

    int choice;
    do {
        std::cout << "\n1. View Inbox\n2. View Outbox\n3. View Priority Emails\n4. View Spam Emails\n5. Search Emails\n6.Exit\nChoose an option: ";
        std::cin >> choice;

        if (choice == 1) emailList.displayInbox();
        else if (choice == 2) emailList.displayOutbox();
        else if (choice == 3) emailList.displayPriorityEmails();
        else if (choice == 4) emailList.displaySpamEmails();
        else if (choice == 5) {
          std::cout << "Enter keyword to search: ";
            std::string keyword;
            std::cin >> keyword;
            emailList.searchEmails(keyword);
        }
        else if (choice != 6) std::cout << "Invalid choice. Try again.\n";

    } while (choice != 6);

    std::cout << "Exiting the program.\n";
    return 0;
}

