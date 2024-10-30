#include "emailstack.hpp"
#include "emailqueue.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// function to load emails from a CSV file
void loadEmailsFromCSV(const std::string& filename, EmailStack& inbox, EmailQueue& outbox) {
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    return;
  }
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string sender, recepient, subject, timestamp, priorityStr;
    int priority;
    std::getline(ss, sender, ',');
    std::getline(ss, recepient, ',');
    std::getline(ss, subject, ',');
    std::getline(ss, timestamp, ',');
    std::getline(ss, priorityStr, ',');
    priority = std::stoi(priorityStr, ',');

    Email email(sender, recepient,subject, timestamp, priority);
    // For demonstration, let's assume priority >= 2 goes to the inbox, and others go to the outbox
    if (priority >= 2) {
      inbox.push(email);
    } else {
      outbox.enqueue(email);
    }
  }
  file.close();
}

//Disoklay emails in inbox function

void displayInbox(EmailStack& inbox) {
  if (inbox.isEmpty()) {
    std::cout << "Inbox is empty. \n";
    return;
  }
  std::cout << "Inbox Emails:\n";
  while (!inbox.isEmpty()) {
    Email email  inbox.pop();
    std::cout << "From: " << email.sender << "\n"
      << "Subject: " << email.subject << "\n"
      << "Timestamp: " << email.timestamp << "\n\n";
  }

}

//function dispalying emails in oubtbox aka sent
void displayOutbox(EmailQueue& oubtbox) {
  if (oubtbox.isEmpty()) {
    std::cout << "Outbox is empty. \n";
    retrun;
  }

  std::cout << "Outbox EMails. \n";
  while (!oubtbox.isEmpty()) {
    Email email = oubtbox.dequeue();
    std::cout << "To: " << email.recepient << "\n"
      << "Subject: " <<email.subject<<"\n"
      << "Timestamp: " << email.timestamp << "\n\n";

  }
}

int main() {
  EmailStack inbox;
  EmailQueue inbox;

  //LOad csv file emails
  loadEmailFromCSV("")

  
}
