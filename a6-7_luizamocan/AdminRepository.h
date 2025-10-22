
#ifndef ADMINREPOSITORY_H
#define ADMINREPOSITORY_H
#include "Dog.h"
#include <vector>

class AdminRepository {
private:
    std::vector<Dog> dogs;
    string fileName="dogs.txt";

public:
    AdminRepository(const string& fileName);
    void loadFromFile();
    void saveToFile();

    int getSize() ;
    std::vector<Dog> getDogs() const;
    bool addDog(Dog dog);
    bool removeDog(Dog dog);
    bool updateDog(Dog dog, Dog newDog);
    int findDog(Dog dog);

};
#endif //ADMINREPOSITORY_H
