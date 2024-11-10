#include "emailstack.hpp"

// Destructor to free the stack
EmailStack::~EmailStack() {
    while (!isEmpty()) {
        pop();
    }
}

// Push email onto stack
void EmailStack::push(const Email& email) {
    Node* newNode = new Node{email, top};
    top = newNode;
}

// Pop email from stack
Email EmailStack::pop() {
    if (isEmpty()) return {}; // Return empty email if stack is empty
    
    Node* node = top;
    Email email = node->email;
    top = top->next;
    delete node;
    return email;
}

// Check if stack is empty
bool EmailStack::isEmpty() const {
    return top == nullptr;
}

// Retrieve all emails as an array
Email* EmailStack::getEmails(int& count) const {
    count = 0;
    Node* current = top;

    // Count number of emails
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    Email* emails = new Email[count];
    current = top;
    int index = 0;

    // Store emails in array
    while (current != nullptr) {
        emails[index++] = current->email;
        current = current->next;
    }

    return emails;
}

