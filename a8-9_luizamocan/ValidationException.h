#pragma once
#include <string>

class ValidationException {
private:
    std::string message;
public:
    explicit ValidationException(std::string _message);
    std::string get_message() const;
};