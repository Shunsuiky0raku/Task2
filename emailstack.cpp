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
    if (isEmpty()) return {}; 
    
    Node* node = top;
    Email email = node->email;
    top = top->next;
    delete node;
    return email;
}

bool EmailStack::isEmpty() const {
    return top == nullptr;
}

Email* EmailStack::getEmails(int& count) const {
    count = 0;
    Node* current = top;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    Email* emails = new Email[count];
    current = top;
    int index = 0;

    while (current != nullptr) {
        emails[index++] = current->email;
        current = current->next;
    }

    return emails;
}

