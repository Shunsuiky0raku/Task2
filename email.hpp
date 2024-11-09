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

// Constructor with parameters
    Email(std::string emailID, std::string sender, std::string recipient,
          std::string subject, std::string body, std::string date, std::string category)
        : emailID(emailID), sender(sender), recipient(recipient), subject(subject),
          body(body), date(date), category(category) {}

    // Default constructor
    Email() : emailID(""), sender(""), recipient(""), subject(""),
              body(""), date(""), category("") {}
};

#endif // email_hpp


