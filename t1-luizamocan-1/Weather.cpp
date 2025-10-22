
#include "Weather.h"
Weather::Weather(string location, string name, string list_sensors) {

    this->location = location;
    this->name = name;
    this->list_sensors = list_sensors;

}
string Weather::getLocation() {
    return this->location;
}
string Weather::getName() {
    return this->name;
}
string Weather::getListSensors() {
    return this->list_sensors;
}

