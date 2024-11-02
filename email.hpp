#ifndef email_hpp
#define email_hpp

#include <string>


class Email {
public:
    std::string emailID;
    std::string sender;
    std::string recipient;
    std::string subject;
    std::string body;
    std::string date;
    std::string category;

    // Updated constructor to accept all 7 parameters
    Email(std::string emailID, std::string sender, std::string recipient, std::string subject,
          std::string body, std::string date, std::string category);
};

#endif

