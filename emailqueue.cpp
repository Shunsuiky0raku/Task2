#include "emailqueue.hpp"
#include <stdexcept>
void EmailQueue::enqueue(const Email& email) {
    QueueNode* newNode = new QueueNode(email);
    if (!rear) front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

Email EmailQueue::dequeue() {
    if (!front) throw std::runtime_error("Queue is empty");
    QueueNode* temp = front;
    Email email = front->email;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return email;
}

bool EmailQueue::isEmpty() const {
    return front == nullptr;
}
