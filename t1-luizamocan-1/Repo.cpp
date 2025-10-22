
#include "Repo.h"
DynamicVector<Weather> Repo::showWeather() {
    return this->weather;
}

int Repo::isUnique(Weather &weather) {
    DynamicVector<Weather> array=this->weather;
    for (int i=0;i<array.getSizeOfDynamicVector();i++)
        if (array[i].getLocation()==weather.getLocation() && array[i].getName()==weather.getName())
            return 1;
    return 0;
}

void Repo::addWeather(const Weather &weather) {
    this->weather.addElementInDynamicVector(weather);
}

