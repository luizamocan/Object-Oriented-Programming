
#ifndef UI_H
#define UI_H
#include "Controller.h"

class UI {
private:
    Controller controller;
    void startUpData();
    public:
    UI();
    void addWeather();
    void showWeather();
    void run();
    static void printMenu();
    void showSensorType();
};
#endif //UI_H
