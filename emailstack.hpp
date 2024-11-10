#ifndef emailstack_hpp
#define emailstack_hpp

#include "email.hpp"


class EmailStack {
private:
  struct Node {
    Email email;
    Node* next;
  };
  Node* top;
public:
  EmailStack() : top(nullptr) {}
  ~EmailStack();

  void push(const Email& email);
  Email pop();
  bool isEmpty() const;

  Email* getEmails(int& count) const;
};

#endif //emailstack_hpp
