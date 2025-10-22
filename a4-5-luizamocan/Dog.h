
#ifndef DOG_H
#define DOG_H
#include <string>
using namespace std;

class Dog{
public:
    Dog(string name, string breed, string link_to_photo, int age);

    Dog();
private:
    string name;
    string breed;
    string link_to_photo;
    int age;
public:
    //GETTERS
    string getName() const;
    string getBreed() const;
     string getLinkToPhoto() const;
    int getAge() const;

    string to_str() const;
    Dog& operator=(const Dog& other);
    bool operator==(const Dog& other) const;
    ~Dog()=default;

    friend ostream& operator<<(ostream& out, const Dog& dog);
    friend istream& operator>>(istream& in, Dog& dog);
};
#endif //DOG_H
