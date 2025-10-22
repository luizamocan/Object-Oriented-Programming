#include "Dog.h"
#include <string>
#include <sstream>

// Constructor that initializes a Dog object with a given name, breed, link to photo, and age
Dog::Dog(string name, string breed, string link_to_photo, int age) {
    this->name = std::move(name);
    this->breed = std::move(breed);
    this->link_to_photo = std::move(link_to_photo);
    this->age = age;
}

// Default constructor that initializes a Dog object with default values
Dog::Dog() {
    this->name = "";
    this->breed = "";
    this->link_to_photo = "";
    this->age = 0;
}

// Getter for the dog's name
string Dog::getName() const  {
    return name;
}

// Getter for the dog's breed
string Dog::getBreed() const {
    return breed;
}

// Getter for the dog's link to photo
string Dog::getLinkToPhoto() const {
    return link_to_photo;
}

// Getter for the dog's age
int Dog::getAge() const {
    return age;
}

// Converts the Dog object to a string representation, useful for displaying information
string Dog::to_str() const {
    ostringstream output;
    output << "Name: " << this->name << " \n";
    output << "Breed: " << this->breed << "\n";
    output << "Link to Photo: " << this->link_to_photo << "\n";
    output << "Age: " << this->age << "\n";

    return output.str();
}

// Assignment operator overload, allows copying values from another Dog object
Dog &Dog::operator=(const Dog &other) {
    if (this == &other) // Prevent self-assignment
        return *this;

    this->name = other.name;
    this->breed = other.breed;
    this->link_to_photo = other.link_to_photo;
    this->age = other.age;
    return *this;
}

// Equality operator overload, checks if two Dog objects are equal by comparing their attributes
bool Dog::operator==(const Dog& other) const {
    return this->name == other.name &&
           this->breed == other.breed &&
           this->age == other.age &&
           this->link_to_photo == other.link_to_photo;
}

ostream& operator<<(ostream& out, const Dog& dog) {
    out<<dog.name<<","<<dog.breed<<","<<dog.link_to_photo<<","<<dog.age<<"\n";
    return out;
}

istream& operator>>(istream& in, Dog& dog) {
    string line;
    if (!getline(in, line)) return in;

    stringstream ss(line);
    string ageStr;

    getline(ss,dog.name,',');
    getline(ss,dog.breed,',');
    getline(ss,dog.link_to_photo,',');
    getline(ss,ageStr);
    dog.age = stoi(ageStr);
    return in;

}