#ifndef emailstack_hpp
#define emailstack_hpp

#include "email.hpp"

class StackNode {
  public:
    Email email;
    StackNode* next;

    StackNode(Email email);

};

class EmailStack {
  private:
    StackNode* top;

  public:
    EmailStack();
    void push(const Email& email);
    Email pop();
    bool isEmpty();

};

#endif 
