#include "email.hpp"

Email::Email(std::string emailID, std::string sender, std::string recipient, std::string subject,
             std::string body, std::string date, std::string category)
    : emailID(emailID), sender(sender), recipient(recipient), subject(subject),
      body(body), date(date), category(category) {}
