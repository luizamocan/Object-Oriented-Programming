#include "AdminRepository.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
AdminRepository::AdminRepository(const string &fileName) :fileName(fileName){
    loadFromFile();
}

void AdminRepository::loadFromFile() {
    ifstream file(fileName);
    Dog dog;
    while (file >> dog) {
        dogs.push_back(dog);
    }
    file.close();

}
void AdminRepository::saveToFile() {
    ofstream file(fileName);
    for (const Dog& dog : dogs) {
        file<<dog;
    }
    file.close();
}


// Returns the number of dogs stored in the repository (size of the DynamicArray)
int AdminRepository::getSize() {
    return dogs.size();
}

// Returns the list of all dogs in the repository
 std::vector<Dog> AdminRepository::getDogs() const {
    return this->dogs;
}

// Adds a new dog to the repository if it doesn't already exist
// Returns true if the dog is added successfully, false if the dog already exists
bool AdminRepository::addDog(Dog dog) {
    if (findDog(dog) != -1) {
        return false;
    }
    this->dogs.push_back(dog);
    saveToFile();
    return true;
}

// Removes an existing dog from the repository
// Returns true if the dog is removed successfully, false if the dog is not found
bool AdminRepository::removeDog(Dog dog) {
    auto it = std::find_if(dogs.begin(), dogs.end(), [&dog](const Dog& d) {
        return d.getName() == dog.getName();
    });

    if (it != dogs.end()) {
        dogs.erase(it);  // Remove the found dog
        saveToFile();
        return true;
    }
    return false;
}

// Updates the information of an existing dog in the repository
// Returns true if the dog is updated successfully, false if the dog is not found
bool AdminRepository::updateDog(Dog dog, Dog newDog) {
    int position = findDog(dog);
    if (position == -1) {
        return false;
    }
    this->dogs[position]=newDog;
    saveToFile();
    return true;
}

// Finds a dog by name and returns its position in the repository
// Returns the index of the dog if found, otherwise returns -1
int AdminRepository::findDog(Dog dog) {
    auto it = std::find_if(dogs.begin(), dogs.end(), [&dog](const Dog& d) {
        return d.getName() == dog.getName();
    });

    if (it != dogs.end()) {
        return std::distance(dogs.begin(), it);  // Return the index
    }
    return -1;
}
Dog AdminRepository::find(const Dog& d) const {
    for (const auto& dog : this->dogs) {
        if (dog.getName() == d.getName()) {
            return dog;
        }
    }
    throw std::runtime_error("Dog not found.");
}

Dog AdminRepository::findByName(const std::string& name) const {
    for (const auto& dog : dogs) {
        if (dog.getName() == name)
            return dog;
    }
    throw std::runtime_error("Dog not found.");
}
