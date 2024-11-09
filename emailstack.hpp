#ifndef emailstack_hpp
#define emailstack_hpp

#include "email.hpp"

struct StackNode {
  Email email;
  StackNode* next;
  StackNode(const Email& email) : email(email), next(nullptr) {}
};

class EmailStack {
private:
  StackNode* top;
public:
  EmailStack() : top(nullptr) {}
  void push(const Email& email);
  Email pop();
  bool isEmpty() const;
};

#endif //emailstack_hpp
