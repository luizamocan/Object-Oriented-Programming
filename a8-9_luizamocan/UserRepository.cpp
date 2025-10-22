#include "UserRepository.h"
#include <algorithm>
#include <iterator>
// Returns the number of adoption dogs in the repository (size of the DynamicArray)
int UserRepository::getSize() {
    return this->adoption_dogs.size();
}

// Returns the list of all adoption dogs in the repository
std::vector<Dog> UserRepository::getAdoption_dogs() const {
    return this->adoption_dogs;
}

// Adds a new dog to the adoption list
void UserRepository::addDog(Dog dog) {
    this->adoption_dogs.push_back(dog);
}

// Removes a dog from the adoption list
// Returns true if the dog is removed successfully, false if the dog is not found
bool UserRepository::removeDog(Dog dog) {
    auto it = std::find_if(adoption_dogs.begin(), adoption_dogs.end(), [&dog](const Dog& d) {
        return d == dog;
    });

    if (it != adoption_dogs.end()) {
        adoption_dogs.erase(it);  // Remove the dog
        return true;
    }
    return false;
}

// Updates the details of an existing dog in the adoption list
// If the dog is found, it is replaced with newDog
void UserRepository::updateDog(Dog dog, Dog newDog) {
    int position = findDog(dog);
    if (position != -1) {
        this->adoption_dogs[position] = newDog;
    }
}

// Finds a dog by comparing it with the dogs in the adoption list
// Returns the index of the dog if found, otherwise returns -1
int UserRepository::findDog(Dog dog) {
    auto it = std::find_if(adoption_dogs.begin(), adoption_dogs.end(), [&dog](const Dog& d) {
        return d == dog;
    });

    if (it != adoption_dogs.end()) {
        return std::distance(adoption_dogs.begin(), it);  // Return the index
    }
    return -1;
}