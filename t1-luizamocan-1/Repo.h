
#ifndef REPO_H
#define REPO_H
#include "DynamicArray.h"
#include "Weather.h"

class Repo {
private:
    DynamicVector<Weather> weather;
    public:
    void addWeather( const Weather& weather);
    DynamicVector<Weather> showWeather();
    int isUnique(Weather& weather);
};
#endif //REPO_H
