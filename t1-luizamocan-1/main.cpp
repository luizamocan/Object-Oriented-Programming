#include <iostream>
#include "UI.h"
#include "Tests.cpp"
using namespace  std;
void tests() {
    Controller controller;
    DynamicVector<Weather> array= DynamicVector<Weather>();
    controller.addWeather("New York", "Central Park"," Barometer");
    assert(array.getSizeOfDynamicVector()==0);

    controller.addWeather("Cluj", "Cetatuie"," Barometer");
    assert(array.getSizeOfDynamicVector()==0);


}

int main() {
    UI ui;
    ui.run();
    tests();
    return 0;
}