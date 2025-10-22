

#ifndef DOMAIN_H
#define DOMAIN_H
#include <iostream>
class Event {
    private:
    std::string organiser;
    std::string name;
    std::string description;
    std::string latitude;
    std::string longitude;
    std::string date;
    public:
    Event(std::string organiser, std::string name, std::string description,std::string latitude,std::string longitude,std::string date);
    std::string getOrganiser() const;
    std::string getName()const;
    std::string getDescription()const;
    std::string getLatitude()const;
    std::string getLongitude()const;
    std::string getDate()const;
    std::string toString()const;
    void setDescription(const std::string& description);
    void setDate(const std::string& date);

};
class Person {
private:
    std::string name;
    std::string latitude;
    std::string longitude;
    std::string  organiser_status;
    public:
    Person(std::string name, std::string latitude, std::string longitude, std::string organiser_status);
    std::string getName() const;
    std::string getLatitude() const;
    std::string getLongitude() const;
    std::string getOrganiserStatus() const;
    std::string toString() const;

};
#endif //DOMAIN_H
