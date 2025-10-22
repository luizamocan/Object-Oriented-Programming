
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Dog.h"
#include "AdminRepository.h"
#include "UserRepository.h"

class Controller {
private:
    AdminRepository adminRepository;
    UserRepository userRepository;
public:
    Controller():adminRepository("dogs.txt"){}
    AdminRepository getAdminRepository();
    UserRepository getUserRepository();
    bool addAdmin(const Dog &dog);
    bool removeAdmin( const Dog& dog);
    bool updateAdmin(Dog dog, Dog new_dog);

    bool addAdminRaw(const Dog& dog){return adminRepository.addDog(dog);}
    bool removeAdminRaw(const Dog& dog){return adminRepository.removeDog(dog);}
    bool updateAdminRaw(const Dog& oldDog, const Dog& newDog){return adminRepository.updateDog(oldDog,newDog);}

    void add_user(Dog dog);
    bool remove_user(Dog dog);
    void generate();

};
#endif //CONTROLLER_H
