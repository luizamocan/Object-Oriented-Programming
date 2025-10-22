/*
#include <cassert>
#include <string>
#include "Dog.h"
#include "Tests_coverage.h"
#include "AdminRepository.h"
#include "DynamicArray.h"
#include "UserRepository.h"
#include "Controller.h"
#include "UI.h"
using namespace std;

void test_constructor_and_getters() {
    Dog d("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);

    assert(d.getName() == "Rex");
    assert(d.getBreed() == "German Shepherd");
    assert(d.getLinkToPhoto() == "http://photo.com/rex.jpg");
    assert(d.getAge() == 5);
}

void test_default_constructor() {
    Dog d;

    assert(d.getName() == "");
    assert(d.getBreed() == "");
    assert(d.getLinkToPhoto() == "");
    assert(d.getAge() == 0);
}

void test_assignment_operator() {
    Dog d1("Max", "Labrador", "http://photo.com/max.jpg", 3);
    Dog d2;

    d2 = d1;

    assert(d2.getName() == "Max");
    assert(d2.getBreed() == "Labrador");
    assert(d2.getLinkToPhoto() == "http://photo.com/max.jpg");
    assert(d2.getAge() == 3);

    // Test self-assignment
    d1 = d1;
    assert(d1.getName() == "Max");
    assert(d1.getBreed() == "Labrador");
    assert(d1.getLinkToPhoto() == "http://photo.com/max.jpg");
    assert(d1.getAge() == 3);
}

void test_equality_operator() {
    Dog d1("Luna", "Husky", "http://photo.com/luna.jpg", 4);
    Dog d2("Luna", "Husky", "http://photo.com/luna.jpg", 4);
    Dog d3("Luna", "Husky", "http://photo.com/luna.jpg", 5); // different age
    Dog d4("Luna", "Husky", "http://photo.com/luna.jpg", 4); // identical to d1, but newly created

    assert(d1 == d2);  // Same values
    assert(!(d1 == d3));  // Different age
    assert(d1 == d4);  // Same values, different instance
}

void test_to_str() {
    Dog d("Bolt", "Dalmatian", "http://photo.com/bolt.jpg", 2);
    string str = d.to_str();

    assert(str.find("Name: Bolt") != string::npos);
    assert(str.find("Breed: Dalmatian") != string::npos);
    assert(str.find("Link to Photo: http://photo.com/bolt.jpg") != string::npos);
    assert(str.find("Age: 2") != string::npos);
}
void test_getSize_AdminRepo() {
    AdminRepository repo;
    Dog dog1("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dog2("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog1);
    repo.addDog(dog2);

    assert(repo.getSize() == 2);
}

void test_addDog_AdminRepo() {
    AdminRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);

    assert(repo.addDog(dog) == true);
    assert(repo.addDog(dog) == false);
}

void test_removeDog_AdminRepo() {
    AdminRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    repo.addDog(dog);
    assert(repo.removeDog(dog) == true);
    assert(repo.removeDog(dog) == false);
}

void test_updateDog_AdminRepo() {
    AdminRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog newDog("Rex", "German Shepherd", "http://photo.com/rex_updated.jpg", 6);

    repo.addDog(dog);

    // Test updating an existing dog
    assert(repo.updateDog(dog, newDog) == true);
    // Test updating a dog that is not in the repository
    Dog notInRepo("Max", "Labrador", "http://photo.com/max.jpg", 3);
    assert(repo.updateDog(notInRepo, newDog) == false);
}

void test_findDog_AdminRepo() {
    AdminRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dogNotFound("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog);

    // Test finding a dog that exists
    assert(repo.findDog(dog) != -1);
    // Test finding a dog that doesn't exist
    assert(repo.findDog(dogNotFound) == -1);
}

void test_getDogs_AdminRepo() {
    AdminRepository repo;
    Dog dog1("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dog2("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog1);
    repo.addDog(dog2);

    DynamicArray<Dog> dogs = repo.getDogs();

    assert(dogs.getSize() == 2);
    assert(dogs.get_element(0).getName() == "Rex");
    assert(dogs.get_element(1).getName() == "Max");
}

void test_constructor_and_getSize_DA() {
    DynamicArray<int> arr;

    assert(arr.getSize() == 0);

    arr.add(10);
    assert(arr.getSize() == 1);

    arr.add(20);
    assert(arr.getSize() == 2);
}

void test_add_DA() {
    DynamicArray<int> arr;


    arr.add(10);
    assert(arr.get_element(0) == 10);

    arr.add(20);
    assert(arr.get_element(1) == 20);
}

void test_remove_DA() {
    DynamicArray<int> arr;
    arr.add(10);
    arr.add(20);
    arr.add(30);


    arr.remove(0);
    assert(arr.getSize() == 2);
    assert(arr.get_element(0) == 20);
    assert(arr.get_element(1) == 30);

    arr.remove(1);
    assert(arr.getSize() == 1);
    assert(arr.get_element(0) == 20);


    arr.remove(0);
    assert(arr.getSize() == 0);
}

void test_update_DA() {
    DynamicArray<int> arr;
    arr.add(10);
    arr.add(20);

    arr.update(0, 100);
    assert(arr.get_element(0) == 100);

    arr.update(1, 200);
    assert(arr.get_element(1) == 200);
}

void test_resize_DA() {
    DynamicArray<int> arr;

    for (int i = 0; i < 15; ++i) {
        arr.add(i);
    }

    assert(arr.getSize() == 15);
    assert(arr.get_element(0) == 0);
    assert(arr.get_element(14) == 14);
}

void test_copy_constructor_DA() {
    DynamicArray<int> arr;
    arr.add(10);
    arr.add(20);

    DynamicArray<int> arrCopy = arr;

    assert(arrCopy.getSize() == arr.getSize());
    assert(arrCopy.get_element(0) == arr.get_element(0));
    assert(arrCopy.get_element(1) == arr.get_element(1));
}

void test_assignment_operator_DA() {
    DynamicArray<int> arr;
    arr.add(10);
    arr.add(20);

    DynamicArray<int> arrCopy;
    arrCopy = arr;

    assert(arrCopy.getSize() == arr.getSize());
    assert(arrCopy.get_element(0) == arr.get_element(0));
    assert(arrCopy.get_element(1) == arr.get_element(1));
}

void test_getSize_UserRepo() {
    UserRepository repo;
    Dog dog1("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dog2("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog1);
    repo.addDog(dog2);

    assert(repo.getSize() == 2);
}

void test_addDog_UserRepo() {
    UserRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);

    repo.addDog(dog);
    assert(repo.getSize() == 1);
    assert(repo.getAdoption_dogs().get_element(0).getName() == "Rex");
}

void test_removeDog_UserRepo() {
    UserRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);

    repo.addDog(dog);

    assert(repo.removeDog(dog) == true);
    assert(repo.removeDog(dog) == false);
}

void test_updateDog_UserRepo() {
    UserRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog newDog("Rex", "German Shepherd", "http://photo.com/rex_updated.jpg", 6);

    repo.addDog(dog);

    repo.updateDog(dog, newDog);
    assert(repo.getAdoption_dogs().get_element(0).getLinkToPhoto() == "http://photo.com/rex_updated.jpg");

    Dog notInRepo("Max", "Labrador", "http://photo.com/max.jpg", 3);
    repo.updateDog(notInRepo, newDog);
    assert(repo.getSize() == 1);
}

void test_findDog_UserRepo() {
    UserRepository repo;
    Dog dog("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dogNotFound("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog);

    assert(repo.findDog(dog) != -1);
    assert(repo.findDog(dogNotFound) == -1);
}

void test_getAdoption_dogs_UserRepo() {
    UserRepository repo;
    Dog dog1("Rex", "German Shepherd", "http://photo.com/rex.jpg", 5);
    Dog dog2("Max", "Labrador", "http://photo.com/max.jpg", 3);

    repo.addDog(dog1);
    repo.addDog(dog2);

    DynamicArray<Dog> dogs = repo.getAdoption_dogs();

    assert(dogs.getSize() == 2);
    assert(dogs.get_element(0).getName() == "Rex");
    assert(dogs.get_element(1).getName() == "Max");
}

void test_getAdminRepository_Controller() {
    Controller controller;

    AdminRepository adminRepo = controller.getAdminRepository();
    assert(adminRepo.getSize() == 0);
}

void test_getUserRepository_Controller() {
    Controller controller;

    UserRepository userRepo = controller.getUserRepository();
    assert(userRepo.getSize() == 0);
}

void test_addAdmin_Controller() {
    Controller controller;
    Dog dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7);

    assert(controller.addAdmin(dog) == true);
    assert(controller.getAdminRepository().getSize() == 1);
}

void test_removeAdmin_Controller() {
    Controller controller;
    Dog dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7);
    controller.addAdmin(dog);


    assert(controller.removeAdmin(dog) == true);
    assert(controller.getAdminRepository().getSize() == 0);
    assert(controller.getUserRepository().getSize() == 0);
}

void test_updateAdmin_Controller() {
    Controller controller;
    Dog dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7);
    Dog updatedDog("Max", "German Shepherd", "https://new-link.com/max.jpg", 8);

    controller.addAdmin(dog);

    assert(controller.updateAdmin(dog, updatedDog) == true);
    assert(controller.getAdminRepository().getDogs().get_element(0).getAge() == 8);
}

void test_add_user_Controller() {
    Controller controller;
    Dog dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7);

    controller.add_user(dog);
    assert(controller.getUserRepository().getSize() == 1);
}

void test_remove_user_Controller() {
    Controller controller;
    Dog dog("Max", "German Shepherd", "https://cdn.britannica.com/79/232779-050-6B0411D7/German-Shepherd-dog-Alsatian.jpg", 7);
    controller.add_user(dog);


    assert(controller.remove_user(dog) == true);
    assert(controller.getUserRepository().getSize() == 0);
}

void test_generate() {
    Controller controller;
    controller.generate();
    assert(controller.getAdminRepository().getDogs().get_element(0).getName() == "Bella");

}

void test_isNumber() {
    UI ui;

    assert(ui.isNumber("123") == true);
    assert(ui.isNumber("0") == true);
    assert(ui.isNumber("999999") == true);


    assert(ui.isNumber("abc") == false);
    assert(ui.isNumber("12a3") == false);
    assert(ui.isNumber("!") == false);
}

void run_all_tests() {
    test_constructor_and_getters();
    test_default_constructor();
    test_assignment_operator();
    test_equality_operator();
    test_to_str();

    test_getSize_AdminRepo();
    test_addDog_AdminRepo();
    test_removeDog_AdminRepo();
    test_updateDog_AdminRepo();
    test_findDog_AdminRepo();
    test_getDogs_AdminRepo();

    test_constructor_and_getSize_DA();
    test_assignment_operator_DA();
    test_copy_constructor_DA();
    test_resize_DA();
    test_update_DA();
    test_remove_DA();
    test_add_DA();

    test_getSize_UserRepo();
    test_addDog_UserRepo();
    test_updateDog_UserRepo();
    test_findDog_UserRepo();
    test_removeDog_UserRepo();
    test_getAdoption_dogs_UserRepo();

    test_add_user_Controller();
    test_remove_user_Controller();
    test_addAdmin_Controller();
    test_removeAdmin_Controller();
    test_updateAdmin_Controller();
    test_getAdminRepository_Controller();
    test_getUserRepository_Controller();
    test_generate();

    test_isNumber();
}
*/