#ifndef emailqueue_hpp
#define emailqueue_hpp

#include "email.hpp"

class QueueNode {
  public:
    Email email;
    QueueNode* next;

    QueueNode(Email email);
};

class EmailQueue {
  private:
    QueueNode* front;
    QueueNode* rear;

  public:
    EmailQueue();
    void enqueue(const Email& email);
    Email dequeue();
    bool isEmpty();
};

#endif



