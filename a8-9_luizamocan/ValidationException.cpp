#include "ValidationException.h"

ValidationException::ValidationException(std::string _message) : message(_message) {}

std::string ValidationException::get_message() const {
    return message;
}
