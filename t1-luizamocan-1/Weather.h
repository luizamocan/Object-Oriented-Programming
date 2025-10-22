
#ifndef WEATHER_H
#define WEATHER_H
#include <string>
using namespace std;
class Weather {
private:
    string location;
    string name;
    string list_sensors;
public:
    Weather(string location="", string name="", string list_sensors="");
    string getLocation();
    string getName();
    string getListSensors();
};
#endif //WEATHER_H
