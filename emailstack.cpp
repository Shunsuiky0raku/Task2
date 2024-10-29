#include "emailstack.hpp"
#include <stdexcept>

StackNode::StackNode(Email email) : email(email), next(nullptr) {}

EmailStack::EmailStack() : top(nullptr) {}

void EmailStack::push(const Email& email) {
  StackNode* newNode = new StackNode(email);
  newNode->next = top;
  top = newNode;
}
Email EmailStack::pop() {
  if (!top) {
    throw std::runtime_error("Stack is empty");
  }
  Email email = top->email;
  StackNode* temp = top;
  top = top->next;
  delete temp;
  return email;
}

bool EmailStack::isEmpty() {
  return top == nullptr;
}
