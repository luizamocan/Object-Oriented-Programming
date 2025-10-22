

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include "Dog.h"
#include <vector>

class UserRepository {
private:
    std::vector<Dog> adoption_dogs;
public:
    int getSize();
    std::vector<Dog> getAdoption_dogs() const;
    void addDog(Dog dog);
    bool removeDog(Dog dog);
    void updateDog(Dog dog, Dog newDog);
    int findDog(Dog dog);

};
#endif //USERREPOSITORY_H
