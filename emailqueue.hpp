#ifndef EMAILQUEUE_HPP
#define EMAILQUEUE_HPP

#include "email.hpp"

class EmailQueue {
private:
    struct Node {
        Email email;
        Node* next;
    };
    Node* front;
    Node* rear;

public:
    EmailQueue() : front(nullptr), rear(nullptr) {}
    ~EmailQueue();

    void enqueue(const Email& email);
    bool isEmpty() const;
    Email dequeue();

    Email* getEmails(int& count) const;
};

#endif 
