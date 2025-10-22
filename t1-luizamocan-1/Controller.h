

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Repo.h"
class Controller {
    private:
    Repo repo;
    public:
    int addWeather(string location, string name, string list_sensors);
    DynamicVector<Weather> getWeatherController();
    void showSensorType(string sensor_type);

};
#endif //CONTROLLER_H
