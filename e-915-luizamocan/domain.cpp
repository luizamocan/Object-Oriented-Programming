
#include "domain.h"
Event::Event(std::string organiser, std::string name, std::string description, std::string latitude, std::string longitude, std::string date) {
    this->organiser = organiser;
    this->name = name;
    this->description = description;
    this->latitude = latitude;
    this->longitude = longitude;
    this->date = date;
}
std::string Event::getName()const {
    return this->name;
}
std::string Event::getLatitude() const{
    return this->latitude;
}
std::string Event::getLongitude() const{
    return this->longitude;
}
std::string Event::getDate() const{
    return this->date;
}
std::string Event::getOrganiser()const {
    return organiser;
}
std::string Event::getDescription() const{
    return description;
}
std::string Event::toString() const{
    return organiser+','+name+","+description+","+latitude+","+longitude+","+date;
}
Person::Person(std::string name, std::string latitude, std::string longitude, std::string  organiser_status) {
    this->name = name;
    this->latitude = latitude;
    this->longitude = longitude;
    this->organiser_status = organiser_status;

}
std::string Person::getName() const{
    return this->name;
}
std::string Person::getLatitude() const{
    return this->latitude;
}
std::string Person::getLongitude()const {
    return this->longitude;
}
std::string  Person::getOrganiserStatus()const {
    return organiser_status;
}
std::string Person::toString() const{
    return name+","+latitude+","+longitude+","+organiser_status;
}

void Event::setDate(const std::string& date) {
    this->date = date;
}
void Event::setDescription(const std::string& description) {
    this->description = description;
}






