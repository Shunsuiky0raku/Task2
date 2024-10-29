#include "email.hpp"

Email::Email(std::string sender, std::string recipient, std::string subject, std::string timestamp, int priority)
: sender(sender), recipient(recipient), subject(subject), timestamp(timestamp), priority(priority) {}

