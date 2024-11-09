#include "emailstack.hpp"
#include <stdexcept>


void EmailStack::push(const Email& email) {
  StackNode* newNode = new StackNode(email);
  newNode->next = top;
  top = newNode;
}


Email EmailStack::pop() {
  if (!top) throw std::runtime_error("Stack is empty");
  StackNode* temp = top;
  Email email = top->email;
  top = top->next;
  delete temp;
  return email;
}

bool EmailStack::isEmpty() const {
  return top == nullptr;
}
