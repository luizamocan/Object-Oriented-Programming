
#include "UI.h"
#include <iostream>
#include <fstream>

#include "CSVSaver.h"
#include "CSVViewer.h"
#include "FileViewer.h"
#include "HTMLSaver.h"
#include "HTMLViewer.h"
#include "ValidateDog.h"
#include "ValidationException.h"
using namespace std;

string UI::login_option(){
  string login_ipt;

  while(true){
    cout<<"Welcome to the 'Keep calm and adopt a pet' shelter! Please choose the type: (admin/user/exit)\n ";
    cout<<">>>";
    getline(cin, login_ipt);

    try {
      ValidateDog::validate_login_option(login_ipt);
      break;
    } catch (ValidationException& e) {
      cout << e.get_message() << endl;
    }
  }
  return login_ipt;
}

void UI::admin_menu() {
  cout << "Choose a command by typing its corresponding number:\n"
          "1. Add a dog into the database.\n"
          "2. Remove a dog from the database.\n"
          "3. Update a dog from the database.\n"
          "4. Display all the dogs.\n"
          "5. Exit\n";
}

void UI::user_menu() {
    cout << "Choose a command by typing its corresponding number:\n"
            "1. See the dogs database\n"
            "2. See all the dogs of a given breed, having an age less than a given number\n"
            "3. See the adoption list \n"
            "4. Open the saved adoption list file \n"
            "0. Exit\n";
  }

string UI::admin_input(){
  string ipt;
  while (true) {
    cout << ">>> ";
    getline(cin, ipt);


    try {
      ValidateDog::validate_admin_input(ipt);
      break;
    } catch (ValidationException& e) {
      cout << e.get_message() << endl;
    }
  }

  return ipt;
}

string UI::user_input(){
  string ipt;
  while (true ) {
    cout << ">>> ";
    getline(cin, ipt);

    try {
      ValidateDog::validate_user_input(ipt);
      break;
    } catch (ValidationException& e) {
      cout << e.get_message() << endl;
    }
  }

  return ipt;
}

void UI::addAdmin() {
  try {
    string name;
    cout << "Please enter the name of the dog: ";
    getline(cin, name);

    string breed;
    cout << "Please enter the breed of the dog: ";
    getline(cin, breed);

    string link_to_photo;
    cout << "Please enter the link to photo: ";
    getline(cin, link_to_photo);

    string age_str;
    cout << "Please enter the age of the dog: ";
    getline(cin, age_str);

    int age_dog = std::stoi(age_str);

    Dog dog(name, breed, link_to_photo, age_dog);
    bool result = this->controller.addAdmin(dog);

    if (result) {
      cout << "Dog added successfully.\n";
    } else {
      cout << "The dog already exists in the database.\n";
    }
  }
  catch (const ValidationException& e) {
    cout << "Validation error: " << e.get_message() << "\n";
  }
  catch (const std::invalid_argument&) {
    cout << "Invalid input: Age must be a number.\n";
  }
  catch (const std::out_of_range&) {
    cout << "Invalid input: Number is too large.\n";
  }
}
void UI::removeAdmin() {
  string name;
  cout<<"Please enter the name of the dog: ";
  getline(cin, name);

  bool result=this->controller.removeAdmin(Dog(name,"a","a",0));

  if (result) {
    cout << "Dog removed successfully.\n";
  } else {
    cout << "The dog does not exist in the database.\n";
  }
}
void UI::updateAdmin() {
  try {
    string name;
    cout << "Please enter the name of the dog: ";
    getline(cin, name);

    string new_name;
    cout << "Please enter the new name of the dog: ";
    getline(cin, new_name);

    string new_breed;
    cout << "Please enter the new breed of the dog: ";
    getline(cin, new_breed);

    string new_link_to_photo;
    cout << "Please enter the new link to photo: ";
    getline(cin, new_link_to_photo);

    string new_age_str;
    cout << "Please enter the new age of the dog: ";
    getline(cin, new_age_str);

    int new_age = stoi(new_age_str);

    bool result = this->controller.updateAdmin(
        Dog(name, "", "", 0),
        Dog(new_name, new_breed, new_link_to_photo, new_age)
    );

    if (result) {
      cout << "Dog updated successfully.\n";
    } else {
      cout << "The dog does not exist in the database.\n";
    }
  }
  catch (const ValidationException& e) {
    cout << "Validation error: " << e.get_message() << "\n";
  }
  catch (const std::invalid_argument&) {
    cout << "Invalid input: Age must be a number.\n";
  }
  catch (const std::out_of_range&) {
    cout << "Invalid input: Number is too large.\n";
  }
}


void UI::displayAdmin() {
  const std::vector<Dog>& dogs = this->controller.getAdminRepository().getDogs();
  for (int i = 0; i < dogs.size(); i++) {
    cout << i + 1 << ". " << dogs[i].to_str() << endl;
  }
}

string UI::get_breed_input() {
  string breed;
  cout<<"Please enter the breed of the dog: ";
  getline(cin, breed);

  return breed;
}

string UI::get_response_input() {
  string response;
  while (true) {
    getline(cin, response);
    if (response !="yes" && response !="no") {
      cout << "Invalid input.";
    }
    else
      break;
  }
  return response;
}
void UI::adopt_dogs() {
  std::vector<Dog> dogs = this->controller.getAdminRepository().getDogs();
  int size = dogs.size();

  if (size == 0) {
    cout << "There is no dog.\n";
    return;
  }

  int index = 0;
  while (true) {
    const Dog& current_dog = dogs[index];

    cout << current_dog.to_str();

    if (this->controller.getUserRepository().findDog(current_dog) != -1) {
      cout << "(Already adopted)\n";
    }

    string photo_str = "start " + current_dog.getLinkToPhoto();
    system(photo_str.c_str());

    cout << "Do you want to adopt this dog? (yes/no)" << endl;
    string response = get_response_input();

    if (response == "yes" && this->controller.getUserRepository().findDog(current_dog) == -1) {
      this->controller.add_user(current_dog);
      cout << "Dog adopted successfully!" << endl;
    } else if (response == "yes") {
      cout << "You already adopted this dog." << endl;
    }

    cout << "Do you want to continue? (yes/no)\n";
    string sec_response = get_response_input();
    if (sec_response == "no") {
      break;
    }

    index = (index + 1) % size;
  }
}


void UI::filter_and_adopt_dogs() {
  string breed = get_breed_input();
  string age_input;
  int max_age;

  while (true) {
    cout << "Please enter the maximum age of the dog: ";
    getline(cin, age_input);

    if (!ValidateDog::isNumber(age_input)) {
      cout << "Invalid input. Please try again.\n";
    } else {
      max_age = stoi(age_input);
      if (max_age < 0)
        cout << "Invalid input. Please enter a non-negative integer.\n";
      else
        break;
    }
  }

  int index = 0;
  bool found = false;

  while (index < this->controller.getAdminRepository().getSize()) {
    Dog current_dog = this->controller.getAdminRepository().getDogs()[index];

    bool matches_breed = (breed.empty() || current_dog.getBreed() == breed);
    bool matches_age = current_dog.getAge() < max_age;

    if (matches_breed && matches_age) {
      found = true;
      cout << current_dog.to_str();

      string photo_str = "start " + current_dog.getLinkToPhoto();
      system(photo_str.c_str());

      cout << "Do you want to adopt this dog? (yes/no)\n";
      string response = get_response_input();

      if (response == "yes" && this->controller.getUserRepository().findDog(current_dog) == -1) {
        this->controller.add_user(current_dog);
        cout << "Dog adopted successfully!\n";
      } else if (response == "yes") {
        cout << "You already adopted this dog.\n";
      }

      cout << "Do you want to continue? (yes/no)\n";
      string sec_response = get_response_input();
      if (sec_response == "no") {
        break;
      }
    }

    index++;

    if (index == this->controller.getAdminRepository().getSize()) {
      index = 0;
      if (!found) {
        cout << "No dogs match your criteria.\n";
        break;
      }
      found = false;
    }
  }
}


void UI::display_user() {
  const std::vector<Dog>& dogs = this->controller.getUserRepository().getAdoption_dogs();
  if (dogs.empty()) {
    cout << "There are no dogs in the adoption list.\n";
  } else {
    for (int i = 0; i < dogs.size(); i++) {
      cout << i + 1 << ". " << dogs[i].to_str() << endl;
    }
  }
}

void UI::choose_file_format() {
  string format;
  while (true) {
    cout << "Please choose the file format to save the adoption list(csv/html):\n";
    getline(cin, format);
    if (format == "csv" || format == "html") {
      break;
    }
    else {
      cout<<"Invalid input.\n";
    }
  }
  string filename;
  cout << "Please enter the name of the file (without extension):\n";
  getline(cin, filename);

  this->file_format=format;
  this->file_name=filename;
}
void UI::save_adoption_list(const std::string& format) {
  const std::vector<Dog>& adopted_dogs = this->controller.getUserRepository().getAdoption_dogs();
  if (adopted_dogs.empty()) {
    cout << "There are no dogs in the adoption list.\n";
    return;
  }
  FileSaver* saver=nullptr;
  string filename=this->file_name+'.'+format;

  if (format == "csv") {
    saver=new CSVSaver();

  }
  else if (format == "html") {
    saver=new HTMLSaver();
  }
  saver->save(adopted_dogs, filename);
  cout<<"Adoption list saved to "<<filename<<endl;
  delete saver;
}
void UI::view_adoption_list() {
  const std::string filename=this->file_name+'.'+this->file_format;
  FileViewer* viewer=nullptr;
  if (this->file_format=="csv") {
    viewer=new CSVViewer();
  }
  else if (this->file_format=="html") {
    viewer=new HTMLViewer();
  }
  else{
    cout<<"Unsupported file format.\n";
    return;
  }
  viewer->view(filename);
  delete viewer;
}



void UI::start() {
  while (true) {
    try {
      string option = login_option();

      if (option == "admin") {
        while (true) {
          try {
            admin_menu();
            string ipt = admin_input();

            if (ipt == "1")
              addAdmin();
            else if (ipt == "2")
              removeAdmin();
            else if (ipt == "3")
              updateAdmin();
            else if (ipt == "4")
              displayAdmin();
            else
              break;
          }
          catch (const ValidationException& e) {
            cout << "Validation error: " << e.get_message() << "\n";
          }
        }
      }
      else if (option == "user") {
        choose_file_format();
        while (true) {
          try {
            user_menu();
            string input = user_input();

            if (input == "1")
              adopt_dogs();
            else if (input == "2")
              filter_and_adopt_dogs();
            else if (input == "3")
              display_user();
            else if (input == "4") {
              view_adoption_list();
            }
            else if (input == "0") {
              save_adoption_list(this->file_format);
              break;
            }

          }
          catch (const ValidationException& e) {
            cout << "Validation error: " << e.get_message() << "\n";
          }
        }
      }
      else
        break;
    }
    catch (const ValidationException& e) {
      cout << "Validation error: " << e.get_message() << "\n";
    }
  }
}





