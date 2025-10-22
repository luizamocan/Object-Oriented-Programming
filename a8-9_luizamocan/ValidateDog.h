#pragma once
#include "AdminRepository.h"
#include "UserRepository.h"
#include "Dog.h"
#include "ValidationException.h"

class ValidateDog {
public:
    static void validate_add(const AdminRepository &repository , const Dog &dog);
    static void validate_delete(const AdminRepository &repository , const Dog &dog);
    static void validate_update(const AdminRepository &repository , const Dog &old_dog, const Dog &new_dog);

    static void validate_add(const UserRepository &repository , const Dog &dog);

    static bool isNumber(const string& str) ;
    static void validate_login_option(const std::string& input);
    static void validate_admin_input(const string& input);
    static void validate_user_input(const string& input);
};