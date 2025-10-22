

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include "Dog.h"
#include <vector>

class UserRepository {
private:
    std::vector<Dog> adoption_dogs;
    std::string fileFormat;
    std::string fileName;
public:
    int getSize();
    std::vector<Dog> getAdoption_dogs() const;
    void addDog(Dog dog);
    bool removeDog(Dog dog);
    void updateDog(Dog dog, Dog newDog);
    int findDog(Dog dog);


    void setFileFormat(const std::string& format){fileFormat=format; }
    void setFileName(const std::string& name){fileName=name; }
    std::string getFileFormat() const{return fileFormat;}
    std::string getFileName() const {return fileName;}

};
#endif //USERREPOSITORY_H
