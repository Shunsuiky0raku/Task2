#ifndef EMAIL_HPP
#define EMAIL_HPP

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

    // Default constructor
    Email() 
        : emailID(""), sender(""), recipient(""), subject(""),
          body(""), date(""), category("") {}

    // Parameterized constructor
    Email(std::string emailID, std::string sender, std::string recipient,
          std::string subject, std::string body, std::string date, std::string category);
};

#endif 

