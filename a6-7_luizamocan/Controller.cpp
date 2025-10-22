#include "Controller.h"

#include "ValidateDog.h"

// Returns the AdminRepository instance associated with the controller
AdminRepository Controller::getAdminRepository() {
    return this->adminRepository;
}

// Returns the UserRepository instance associated with the controller
UserRepository Controller::getUserRepository() {
    return this->userRepository;
}

// Adds a dog to the AdminRepository
// Returns true if the dog is added successfully, otherwise false
bool Controller::addAdmin(const Dog &dog) {
    ValidateDog ::validate_add(adminRepository,dog);
    return this->adminRepository.addDog(dog);
}

// Removes a dog from both the UserRepository and AdminRepository
// Returns true if the dog is removed successfully from both repositories
bool Controller::removeAdmin(Dog dog) {
    ValidateDog ::validate_delete(adminRepository,dog);
    this->userRepository.removeDog(dog);
    return this->adminRepository.removeDog(dog);
}

// Updates the information of a dog in both the UserRepository and AdminRepository
// If the dog is found in both repositories, it is replaced with the new dog
bool Controller::updateAdmin(Dog dog, Dog new_dog) {
    ValidateDog ::validate_update(adminRepository,dog,new_dog);
    this->userRepository.updateDog(dog, new_dog);
    return this->adminRepository.updateDog(dog, new_dog);
}

// Adds a dog to the UserRepository
void Controller::add_user(Dog dog) {
    ValidateDog ::validate_add(userRepository,dog);
    return this->userRepository.addDog(dog);
}

// Removes a dog from the UserRepository
// Returns true if the dog is removed successfully, otherwise false
bool Controller::remove_user(Dog dog) {
    return this->userRepository.removeDog(dog);
}

// Generates and adds a list of predefined dogs to the AdminRepository
void Controller::generate() {
    std::vector<Dog> dogs = {
        Dog("Bella", "Golden Retriever", "https://www.zooplus.ro/ghid/wp-content/uploads/2022/07/Golden-retriever-descriere-generala.webp", 5),
        Dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7),
        Dog("Charlie", "Beagle", "https://www.zooplus.ro/ghid/wp-content/uploads/2021/07/despre-beagle.webp", 4),
        Dog("Lucy", "Bulldog", "https://image.petmd.com/files/inline-images/english-bulldog-5.jpg?VersionId=1KyTFgo4HZwpAcjf.WZ8mM_2yt6f9Zc3", 6),
        Dog("Daisy", "Poodle", "https://image.petmd.com/files/styles/978x550/public/2023-01/toy-poodle.jpg", 3),
        Dog("Rocky", "Siberian Husky", "https://consumer-cms.petfinder.com/sites/default/files/images/content/Siberian%20Husky%204.jpg", 8),
        Dog("Milo", "Dalmatian", "https://pethelpful.com/.image/w_3840,q_auto:good,c_fill,ar_4:3/MjAxMTY5NTU4ODY4ODYyNDg2/dalmatian-guide.jpg", 5),
        Dog("Bailey", "Shiba Inu", "https://www.zooplus.ro/ghid/wp-content/uploads/2023/01/shiba-inu-cu-limba-scoasa.webp", 2),
        Dog("Lola", "Cocker Spaniel", "https://www.akc.org/wp-content/uploads/2017/11/English-Cocker-Spaniel-Slide03.jpg", 6),
        Dog("Toby", "Border Collie", "https://www.bellaandduke.com/wp-content/uploads/2024/10/Border-collie-owners-dog-breed-guide-1.png", 4),
        Dog("Kara", "Golden Retriever", "https://www.megapet.ro/continut/upload/Rasa-Golden-Retriever.jpg", 7),
        Dog("Tina", "Golden Retriever", "https://bucuriacasei.ro/wp-content/uploads/2024/02/rasa-golden-retriever-scaled.webp", 3)
    };

    for (const auto& dog : dogs) {
        this->adminRepository.addDog(dog);
    }
}