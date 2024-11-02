#ifndef email_hpp
#define email_hpp

#include <string>

class Email {
  public:
    std::string sender;
    std::string recipient;
    std::string subject;
    std::string timestamp;
    int priority;

    //constructor
    Email(std::string sender, std::string recipient, std::string subject, std::string timestamp, int priority);
};

#endif
