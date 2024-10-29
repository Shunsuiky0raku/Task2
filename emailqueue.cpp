#include "emailqueue.hpp"
#include <stdexcept>

QueueNode::QueueNode(Email email) : email(email), next(nullptr) {}

EmailQueue::EmailQueue() : front(nullptr), rear(nullptr) {}

void EmailQueue::enqueue(const Email& email) {
  QueueNode* newNode = new QueueNode(email);
  if (!rear) {
    front = rear = newNode;
    return;
  }
  rear->next = newNode;
  rear = newNode;
}
Email EmailQueue::dequeue() {
  if (!front) {
    throw std::runtime_error("Queue is empty");
  }
  Email email = front->email;
  QueueNode* temp = front;
  front = front->next;
  if (!front) {
    rear = nullptr;
  }
  delete temp;
  return email;
}

bool EmailQueue::isEmpty() {
  return front == nullptr;
}


