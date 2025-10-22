#include "ValidateDog.h"
#include <regex>
void ValidateDog::validate_add(const AdminRepository& repository, const Dog &dog) {
    if (dog.getName().empty())
        throw ValidationException("Dog name cannot be empty");
    if (isNumber(dog.getName()))
        throw ValidationException("Dog name must be a string");

    if (dog.getBreed().empty())
        throw ValidationException("Dog breed cannot be empty");
    if (isNumber(dog.getBreed()))
        throw ValidationException("Dog breed must be a string");

    if (dog.getAge() < 0)
        throw ValidationException("Dog age cannot be negative");

    std::regex url_pattern("^(https?://).+");
    if (!std::regex_match(dog.getLinkToPhoto(), url_pattern)) {
        throw ValidationException("Dog link to photo must be a valid URL");
    }

    const auto &dogs = repository.getDogs();
    for (const auto &d : dogs) {
        if (d.getName() == dog.getName() && d.getBreed() == dog.getBreed())
            throw ValidationException("Dog name and breed cannot be same");
    }
}
void ValidateDog::validate_delete(const AdminRepository &repository, const Dog &dog) {
    const auto &dogs = repository.getDogs();
    bool found = false;
    for (const auto &d : dogs) {
        if (d.getName() == dog.getName() )
            found = true;
    }
    if (!found)
        throw ValidationException("Dog not found for removal");
}
void ValidateDog::validate_update(const AdminRepository &repository, const Dog &old_dog, const Dog &new_dog) {
    validate_delete(repository, old_dog);
    validate_add(repository, new_dog);
}

void ValidateDog::validate_add(const UserRepository &repository, const Dog &dog) {
    const auto &dogs=repository.getAdoption_dogs();
    for (const auto &d : dogs) {
        if (d.getName() == dog.getName() && d.getBreed() == dog.getBreed())
            throw ValidationException("Dog already exists in the adoption list");
    }
}

bool ValidateDog::isNumber(const string& str) {
    for (char const &c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

void ValidateDog::validate_login_option(const std::string& input) {
    if (input != "admin" && input != "user" && input != "exit") {
        throw ValidationException("Invalid input! Please enter 'admin', 'user', or 'exit'.");
    }
}

void ValidateDog::validate_admin_input(const std::string& input) {
    if (input != "1" && input != "2" && input != "3" && input != "4" && input != "5") {
        throw ValidationException("Invalid admin command!");
    }
}

void ValidateDog::validate_user_input(const std::string& input) {
    if (input != "1" && input != "2" && input != "3" && input != "0" && input != "4") {
        throw ValidationException("Invalid user command!");
    }
}
