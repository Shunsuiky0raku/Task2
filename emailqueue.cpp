#include "emailqueue.hpp"

// Destructor to free the queue
EmailQueue::~EmailQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Enqueue email into queue
void EmailQueue::enqueue(const Email& email) {
    Node* newNode = new Node{email, nullptr};
    if (rear != nullptr) {
        rear->next = newNode;
    } else {
        front = newNode;
    }
    rear = newNode;
}

// Dequeue email from queue
Email EmailQueue::dequeue() {
    if (isEmpty()) return {}; // Return empty email if queue is empty
    
    Node* node = front;
    Email email = node->email;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete node;
    return email;
}

// Check if queue is empty
bool EmailQueue::isEmpty() const {
    return front == nullptr;
}

// Retrieve all emails as an array
Email* EmailQueue::getEmails(int& count) const {
    count = 0;
    Node* current = front;

    // Count number of emails
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    Email* emails = new Email[count];
    current = front;
    int index = 0;

    // Store emails in array
    while (current != nullptr) {
        emails[index++] = current->email;
        current = current->next;
    }

    return emails;
}

