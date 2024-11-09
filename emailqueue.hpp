#ifndef emailqueue_hpp
#define emailqueue_hpp

#include "email.hpp"
 struct QueueNode {
    Email email;
    QueueNode* next;
    QueueNode(const Email& email) : email(email), next(nullptr) {}
};

class EmailQueue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    EmailQueue() : front(nullptr), rear(nullptr) {}
    void enqueue(const Email& email);
    Email dequeue();
    bool isEmpty() const;
};

#endif // emailqueue_hpp
