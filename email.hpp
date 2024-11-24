#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>

class Email {
public:
    std::string emailID, sender, recipient, subject, body, date, category;

    // Adjust the constructor to accept only 5 arguments if that's what's required.
    Email(std::string emailID, std::string sender, std::string recipient,
          std::string subject, std::string body, std::string date)
        : emailID(emailID), sender(sender), recipient(recipient), subject(subject),
          body(body), date(date), category("") {}
};
#endif 

