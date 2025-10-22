
#include "Controller.h"
#include <string.h>
#include <iostream>
using namespace std;

int Controller::addWeather(string location, string name, string list_sensors) {
    /*Function that add a weather location to the array of weather locations
     *check is there is another same location ,in case it throws an exception
     *otherwise adds it and returns 0
     *
     */
    Weather weather=Weather(location,name,list_sensors);
    int pos=this->repo.isUnique(weather);
    if (pos==1) {
        throw std::invalid_argument("Location already exists");

    }
    this->repo.addWeather(weather);
    return 0;
}

DynamicVector<Weather> Controller::getWeatherController() {
    return this->repo.showWeather();
}

void Controller::showSensorType(string sensor_type) {
    /*Function that search for the sensor type in the list of the sensors of each element in the array
     *prints the sensor type together with the location in which it is find
     *
     */
    DynamicVector<Weather> locations=DynamicVector<Weather>();
    DynamicVector<Weather> array=this->getWeatherController();
    for (int i=0;i<array.getSizeOfDynamicVector();i++)
        if (array[i].getListSensors().substr(0, sensor_type.length()) == sensor_type) {
            cout<<sensor_type<<" :"<<array[i].getLocation()<<endl;
           
        }


}
